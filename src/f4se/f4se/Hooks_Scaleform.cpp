#include "Hooks_Scaleform.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"

#include "f4se_common/f4se_version.h"

#include "ScaleformMovie.h"
#include "ScaleformValue.h"
#include "ScaleformCallbacks.h"
#include "ScaleformState.h"
#include "ScaleformLoader.h"

class BSScaleformManager;

typedef BSScaleformManager * (* _BSScaleformManager_Ctor)(BSScaleformManager * mem);
RelocAddr <_BSScaleformManager_Ctor> BSScaleformManager_Ctor(0x020A1970);
_BSScaleformManager_Ctor BSScaleformManager_Ctor_Original = nullptr;

typedef UInt32 (* _BSScaleformTint)(BSGFxShaderFXTarget * value, float * colors, float multiplier);
RelocAddr <_BSScaleformTint> BSScaleformTint(0x02083ED0);
_BSScaleformTint BSScaleformTint_Original = nullptr;

RelocAddr <uintptr_t> ScaleformInitHook_Start(0x020A2010 + 0x188);

//// plugin API
struct ScaleformPluginInfo
{
	const char	* name;
	F4SEScaleformInterface::RegisterCallback	callback;
};

typedef std::list <ScaleformPluginInfo> PluginList;
static PluginList s_plugins;

bool g_logScaleform = false;

bool RegisterScaleformPlugin(const char * name, F4SEScaleformInterface::RegisterCallback callback)
{
	// check for a name collision
	for(PluginList::iterator iter = s_plugins.begin(); iter != s_plugins.end(); ++iter)
	{
		if(!strcmp(iter->name, name))
		{
			_WARNING("scaleform plugin name collision: %s", iter->name);
			return false;
		}
	}

	ScaleformPluginInfo	info;

	info.name = name;
	info.callback = callback;

	s_plugins.push_back(info);

	return true;
}

void Hooks_Scaleform_Init()
{
	//
}

class F4SEScaleform_VisitMembers : public GFxValue::ObjectInterface::ObjVisitor
{
public:
	F4SEScaleform_VisitMembers(GFxMovieRoot * root, GFxValue * result) : m_root(root), m_result(result) { }
	virtual void Visit(const char * member, const GFxValue * value)
	{
		GFxValue str;
		m_root->CreateString(&str, member);
		m_result->PushBack(&str);
	}

	GFxMovieRoot * m_root;
	GFxValue * m_result;
};

class F4SEScaleform_GetMembers : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args* args)
	{
		if(args->numArgs >= 1)
		{
			args->movie->movieRoot->CreateArray(args->result);
			F4SEScaleform_VisitMembers dm(args->movie->movieRoot, args->result);
			args->args[0].VisitMembers(&dm);
		}
	}
};


void ScaleformInitHook_Install(GFxMovieView * view)
{
	GFxValue		root;
	GFxMovieRoot	* movieRoot = view->movieRoot;

	bool result = movieRoot->GetVariable(&root, "root");
	if(!result)
	{
		_ERROR("couldn't get root");
		return;
	}

	GFxValue	f4se;
	movieRoot->CreateObject(&f4se);

	RegisterFunction<F4SEScaleform_GetMembers>(&f4se, movieRoot, "GetMembers");
	
	GFxValue	version;
	movieRoot->CreateObject(&version);
	version.SetMember("major", &GFxValue(F4SE_VERSION_INTEGER));
	version.SetMember("minor", &GFxValue(F4SE_VERSION_INTEGER_MINOR));
	version.SetMember("beta", &GFxValue(F4SE_VERSION_INTEGER_BETA));
	version.SetMember("releaseIdx", &GFxValue(F4SE_VERSION_RELEASEIDX));
	f4se.SetMember("version", &version);

	// plugins
	GFxValue	plugins;
	movieRoot->CreateObject(&plugins);

	for(PluginList::iterator iter = s_plugins.begin(); iter != s_plugins.end(); ++iter)
	{
		GFxValue	plugin;
		movieRoot->CreateObject(&plugin);

		iter->callback(view, &plugin);

		plugins.SetMember(iter->name, &plugin);
	}

	f4se.SetMember("plugins", &plugins);

	root.SetMember("f4se", &f4se);
	
	GFxValue dispatchEvent;
	GFxValue eventArgs[3];
	movieRoot->CreateString(&eventArgs[0], "F4SE::Initialized");
	eventArgs[1] = GFxValue(true);
	eventArgs[2] = GFxValue(false);
	movieRoot->CreateObject(&dispatchEvent, "flash.events.Event", eventArgs, 3);
	movieRoot->Invoke("root.dispatchEvent", nullptr, &dispatchEvent, 1);
}

BSScaleformManager * BSScaleformManager_Ctor_Hook(BSScaleformManager * mgr)
{
	BSScaleformManager * result = BSScaleformManager_Ctor_Original(mgr);

	if(g_logScaleform)
	{
		GFxLogState * logger = (GFxLogState*)result->stateBag->GetStateAddRef(GFxState::kInterface_Log);
		logger->logger = new F4SEGFxLogger();
	}

	return result;
}

UInt32 BSScaleformTint_Hook(BSGFxShaderFXTarget * value, float * colors, float multiplier)
{
	if(value->HasMember("onApplyColorChange"))
	{
		GFxValue result;
		GFxValue args[4];
		args[0] = GFxValue(colors[0]);
		args[1] = GFxValue(colors[1]);
		args[2] = GFxValue(colors[2]); 
		args[3] = GFxValue(multiplier);
		value->Invoke("onApplyColorChange", &result, args, 4);
		if(result.IsArray() && result.GetArraySize() >= 4)
		{
			result.GetElement(0, &args[0]);
			result.GetElement(1, &args[1]);
			result.GetElement(2, &args[2]);
			result.GetElement(3, &args[3]);

			colors[0] = args[0].GetNumber();
			colors[1] = args[1].GetNumber();
			colors[2] = args[2].GetNumber();
			multiplier = args[3].GetNumber();
		}
	}
	
	return BSScaleformTint_Original(value, colors, multiplier);
}

void Hooks_Scaleform_Commit()
{
	UInt32	logScaleform = 0;
	if(GetConfigOption_UInt32("Interface", "bEnableGFXLog", &logScaleform))
	{
		if(logScaleform)
		{
			g_logScaleform = true;
		}
	}

	// hook creation of each menu
	{
		struct ScaleformInitHook_Code : Xbyak::CodeGenerator {
			ScaleformInitHook_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				mov(eax, 1);
				lock(); xadd(ptr [rcx + 8], eax);
				jmp((void *)&ScaleformInitHook_Install);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		ScaleformInitHook_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		g_branchTrampoline.Write5Call(ScaleformInitHook_Start, uintptr_t(code.getCode()));
	}

	// hook creation of BSScaleformManager
	{
		struct BSScaleformManager_Code : Xbyak::CodeGenerator {
			BSScaleformManager_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				push(rbp);
				push(rbx);
				push(rsi);
				push(rdi);

				jmp(ptr [rip + retnLabel]);

				L(retnLabel);
				dq(BSScaleformManager_Ctor.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		BSScaleformManager_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		BSScaleformManager_Ctor_Original = (_BSScaleformManager_Ctor)codeBuf;

		g_branchTrampoline.Write5Branch(BSScaleformManager_Ctor.GetUIntPtr(), (uintptr_t)BSScaleformManager_Ctor_Hook);
	}

	// hook global tinting of objects
	{
		struct BSScaleformTint_Code : Xbyak::CodeGenerator {
			BSScaleformTint_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp+0x18], rbx);

				jmp(ptr [rip + retnLabel]);

				L(retnLabel);
				dq(BSScaleformTint.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		BSScaleformTint_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		BSScaleformTint_Original = (_BSScaleformTint)codeBuf;

		g_branchTrampoline.Write5Branch(BSScaleformTint.GetUIntPtr(), (uintptr_t)BSScaleformTint_Hook);
	}
}
