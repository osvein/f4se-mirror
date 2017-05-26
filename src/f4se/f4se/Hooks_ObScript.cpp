#include "Hooks_ObScript.h"
#include "ObScript.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "f4se_common/SafeWrite.h"
#include "f4se_common/f4se_version.h"

// currently ForceRSXCrash, could also use ToggleESRAM and several others
static ObScriptCommand * s_hijackedCommand = nullptr;

#ifdef _DEBUG
static ObScriptCommand * s_testCommand = nullptr;
#endif

void Hooks_ObScript_Init()
{
	// instead of hooking the entire classic scripting system, we're just hijacking some unused commands

	for(ObScriptCommand * iter = g_firstConsoleCommand; iter->opcode < kObScript_NumConsoleCommands; ++iter)
	{
		if(!strcmp(iter->longName, "ForceRSXCrash"))
		{
			s_hijackedCommand = iter;
#ifndef _DEBUG
			break;
#endif
		}
#ifdef _DEBUG
		if(!strcmp(iter->longName, "TestCode"))
		{
			s_testCommand = iter;
		}
#endif
	}

	if(!s_hijackedCommand)
	{
		_ERROR("couldn't find obscript command to use");
	}
}

bool GetF4SEVersion_Execute(void * paramInfo, void * scriptData, TESObjectREFR * thisObj, void * containingObj, void * scriptObj, void * locals, double * result, void * opcodeOffsetPtr)
{
	_MESSAGE("GetF4SEVersion_Execute");

	Console_Print("F4SE version: %d.%d.%d, release idx %d, runtime %08X",
		F4SE_VERSION_INTEGER, F4SE_VERSION_INTEGER_MINOR, F4SE_VERSION_INTEGER_BETA,
		F4SE_VERSION_RELEASEIDX, RUNTIME_VERSION);
	return true;
}

#ifdef _DEBUG
#include "f4se/GameRTTI.h"
#include "f4se/GameObjects.h"
#include "f4se/GameData.h"
#include "f4se/GameMenus.h"
#include "f4se/GameMessages.h"
#include "f4se/BSGeometry.h"
#include "f4se/NiProperties.h"
#include "f4se/NiMaterials.h"
#include "f4se/NiNodes.h"
#include "f4se/NiRTTI.h"
#include "f4se/NiExtraData.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameThreads.h"
#include "f4se/Hooks_Threads.h"
#include "f4se/BSModelDB.h"
#include <functional>
#include "f4se/BSGraphics.h"
#include "f4se/NiTextures.h"
#include "f4se/PapyrusEvents.h"
#include "f4se/GameCamera.h"

RelocAddr <uintptr_t> GetActorBaseHeadData_Start(0x00687920 + 0xCF);
RelocAddr <uintptr_t> GetMorphGroups_Start(0x00687920 + 0x390);
RelocAddr <uintptr_t> StaticTextureIndexed_Ctor_Start(0x00687920 + 0xD38);

#include <mutex>
#include "f4se/GameObjects.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/SafeWrite.h"
#include "xbyak/xbyak.h"
#include "common/ICriticalSection.h"

class F4SECharGen
{
public:
	void SetBaseTintTextureOverride(BGSTextureSet * textureSet)
	{
		m_faceTextureOverride.faceTextures = textureSet;
	}

	void LockBaseTextureOverride()
	{
		m_cs.Enter();
	}

	void ReleaseBaseTextureOverride()
	{
		m_cs.Leave();
	}

	TESNPC::HeadData * ProcessHeadData(TESNPC * npc)
	{
		IScopedCriticalSection locker(&m_cs);
		if(m_faceTextureOverride.faceTextures) {
			return &m_faceTextureOverride;
		}

		return npc->headData;
	}

	tArray<CharacterCreation::MorphGroup*> * ProcessMorphGroups(CharacterCreation::CharGenData * chargenData)
	{
		IScopedCriticalSection locker(&m_cs);
		if(m_faceTextureOverride.faceTextures) {
			return nullptr;
		}

		return chargenData->morphGroups;
	}

	TESNPC::HeadData m_faceTextureOverride;
	ICriticalSection m_cs;
};

F4SECharGen g_charGen;

TESNPC::HeadData * GetActorBaseHeadData_Hook(TESNPC * npc)
{
	return g_charGen.ProcessHeadData(npc);
}


BSTextureArray::StaticTextureIndexed* StaticTextureIndexed_ctor_Hook(BSTextureArray::StaticTextureIndexed* _this, UInt32 unk1, int unk2, bool unk3)
{
	BSTextureArray::StaticTextureIndexed* ret = CALL_MEMBER_FN(_this, ctor)(unk1, unk2, unk3);
	//ret->unk18 = 4096;
	return ret;
}

tArray<CharacterCreation::MorphGroup*> * GetMorphGroups_Hook(CharacterCreation::CharGenData * chargenData)
{
	return g_charGen.ProcessMorphGroups(chargenData);
}

ObScriptCommand * GetCommandByOpcode(UInt16 opcode)
{
	for(ObScriptCommand * iter = g_firstConsoleCommand; iter->opcode < kObScript_NumConsoleCommands; ++iter)
	{
		if(iter->opcode == opcode)
			return iter;
	}

	return nullptr;
}

void DumpNodeChildren(NiAVObject * node)
{
	_MESSAGE("{%s} {%s} {%016I64X} {Flags %016I64X}", node->GetRTTI()->name, node->m_name.c_str(), node, node->flags);
	if(node->m_extraData) {
		gLog.Indent();
		for(UInt16 i = 0; i < node->m_extraData->count; i++) {
			_MESSAGE("{%s} {%s} {%016I64X}", node->m_extraData->entries[i]->GetRTTI()->name, node->m_extraData->entries[i]->m_name.c_str(), node);
		}
		gLog.Outdent();
	}
	//DumpClass(node);
	NiNode * niNode = node->GetAsNiNode();
	if(niNode && niNode->m_children.m_emptyRunStart > 0)
	{
		gLog.Indent();
		for(int i = 0; i < niNode->m_children.m_emptyRunStart; i++)
		{
			NiAVObject * object = niNode->m_children.m_data[i];
			if(object) {
				BSTriShape * trishape = object->GetAsBSTriShape();
				BSDynamicTriShape * dynamicShape = object->GetAsBSDynamicTriShape();
				if(trishape || dynamicShape) {
					_MESSAGE("{%s} {%s} {%016I64X} {Vertices %d} {Flags %016I64X}", trishape->GetRTTI()->name, trishape->m_name.c_str(), trishape, trishape->numVertices, trishape->flags);
					gLog.Indent();
					_MESSAGE("{VertexData: %016I64X}", trishape->geometryData->vertexData);
					if(dynamicShape) {
						_MESSAGE("{DynamicData: %016I64X}", dynamicShape->dynamicVertices);
					}
					gLog.Outdent();
					if(object->m_extraData) {
						gLog.Indent();
						for(UInt16 i = 0; i < object->m_extraData->count; i++) {
							_MESSAGE("{%s} {%s} {%016I64X} {Flags %016I64X}", object->m_extraData->entries[i]->GetRTTI()->name, object->m_extraData->entries[i]->m_name.c_str(), object, object->flags);
						}
						gLog.Outdent();
					}					
				} else {
					DumpNodeChildren(object);
				}
			}
		}
		gLog.Outdent();
	}
}

bool VisitObjects(NiAVObject * parent, std::function<bool(NiAVObject*)> functor)
{
	if (functor(parent))
		return true;

	NiPointer<NiNode> node(parent->GetAsNiNode());
	if(node) {
		for(UInt32 i = 0; i < node->m_children.m_emptyRunStart; i++) {
			NiPointer<NiAVObject> object(node->m_children.m_data[i]);
			if(object) {
				if (VisitObjects(object, functor))
					return true;
			}
		}
	}

	return false;
}

#include "GameThreads.h"

class SomeTask : public ITaskDelegate
{
public:
	virtual void Run() override
	{
		IMenu * pMenu = (*g_ui)->GetMenu(&BSFixedString("HUDMenu"));
		if(pMenu)
		{
			DumpClass(pMenu, sizeof(HUDMenu)>>3);
			GFxMovieRoot * movieRoot = pMenu->movie->movieRoot;
			GFxValue::DisplayInfo dp;
			pMenu->stage.GetDisplayInfo(&dp);
			dp.SetAlpha(50.0f);
			pMenu->stage.SetDisplayInfo(&dp);
		}
	}
};

class CombatSink : public BSTEventSink<TESCombatEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESCombatEvent * evn, void * dispatcher) override
	{
		DumpClass(evn, sizeof(TESCombatEvent)/8);
		return kEvent_Continue;
	}
};

CombatSink combatSink;


//#include "d3d11.h"
//#include "d3dx11tex.h"
//#define BODY_PAINT

bool F4SETestCode_Execute(void * paramInfo, void * scriptData, TESObjectREFR * thisObj, void * containingObj, void * scriptObj, void * locals, double * result, void * opcodeOffsetPtr)
{
	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrHDPT.count; i++)
	{
		BGSHeadPart * headPart = (*g_dataHandler)->arrHDPT[i];
		_MESSAGE("Part: %s", headPart->partName.data ? headPart->partName.data->Get<char>() : "");
		DumpClass(headPart, sizeof(BGSHeadPart)/8);
	}*/

	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrFLST.count; i++)
	{
		BGSListForm * listForm = (*g_dataHandler)->arrFLST[i];
		if(listForm->unk38 != 0) {
			DumpClass(listForm, sizeof(BGSListForm)/8);
		}
	}*/

	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrMISC.count; i++)
	{
		TESObjectMISC * miscObject = (*g_dataHandler)->arrMISC[i];
		if(miscObject) {
			DumpClass(miscObject, sizeof(TESObjectMISC)/8);
		}
	}*/

	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrWATR.count; i++)
	{
		TESWaterForm * waterForm = (*g_dataHandler)->arrWATR[i];
		_MESSAGE("Water: %s", waterForm->fullName.name.c_str());
		DumpClass(waterForm, sizeof(TESWaterForm)/8);
	}*/

	/*_MESSAGE("Location");
	for(UInt32 i = 0; i < (*g_dataHandler)->arrLCTN.count; i++)
	{
		BGSLocation * form = (*g_dataHandler)->arrLCTN[i];
		DumpClass(form, sizeof(BGSLocation)/8);
	}

	_MESSAGE("EncounterZone");
	for(UInt32 i = 0; i < (*g_dataHandler)->arrECZN.count; i++)
	{
		BGSEncounterZone * form = (*g_dataHandler)->arrECZN[i];
		DumpClass(form, sizeof(BGSEncounterZone)/8);
	}*/

	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrPERK.count; i++)
	{
		BGSPerk * form = (*g_dataHandler)->arrPERK[i];
		_MESSAGE("Form: %s", form->fullName.name.c_str());

		TESDescription * pDescription = DYNAMIC_CAST(form, TESForm, TESDescription);
		if(pDescription) {
			BSString str;
			CALL_MEMBER_FN(pDescription, Get)(&str, nullptr);
			_MESSAGE("Description: %s", str.Get());
		}

		DumpClass(form, sizeof(BGSPerk)/8);
	}*/


	for(UInt32 i = 0; i < 2; i++)
	{
		TESObjectARMO * armor = (TESObjectARMO*)LookupFormByID(0x7B000F99 + i);
		if(armor) {
			DumpClass(armor, sizeof(TESObjectARMO)/8);
		}
	}

	
	/*for(UInt32 i = 0; i < 18; i++)
	{
		TESObjectWEAP * weapon = (TESObjectWEAP*)LookupFormByID(0x74001ED1 + i);
		if(weapon) {
			DumpClass(weapon, sizeof(TESObjectWEAP)/8);
		}
	}*/
	

	//BGSMod::Attachment::Mod * modForm = (BGSMod::Attachment::Mod*)LookupFormByID(0x74000F9A);
	//if(modForm)
	//{
	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrOMOD.count; i++)
	{
		BGSMod::Attachment::Mod * modForm = (*g_dataHandler)->arrOMOD[i];
		TESFullName * fullName = DYNAMIC_CAST(modForm, TESForm, TESFullName);
		_MESSAGE("Mod: %X - Name: %s UnkC0: %02X UnkC2: %01X UnkC4: %01X UnkC6: %01X UnkC7: %01X", modForm->formID, fullName ? fullName->name.c_str() : "", modForm->unkC0, modForm->targetType, modForm->scaledOffset, modForm->unkC6, modForm->unkC7);
		for(UInt32 j = 0; j < modForm->modContainer.dataSize / sizeof(BGSMod::Container::Data); j++)
		{
			gLog.Indent();
			_MESSAGE("Type: %d Operator: %01X Value: %016I64X", modForm->modContainer.data[j].target, modForm->modContainer.data[j].op, modForm->modContainer.data[j].value.form);
			gLog.Outdent();
		}
	}*/

	/*for(UInt32 i = 0; i < (*g_dataHandler)->arrOMOD.count; i++)
	{
		BGSMod::Attachment::Mod * modForm = (*g_dataHandler)->arrOMOD[i];
		_MESSAGE("%lX", modForm->formID);
		DumpClass(modForm, sizeof(BGSMod::Attachment::Mod)/8);
		for(UInt32 j = 0; j < modForm->modContainer.dataSize / sizeof(BGSMod::Container::Data); j++)
		{
			gLog.Indent();
			DumpClass(&modForm->modContainer.data[j], 2);
			gLog.Outdent();
		}
	}*/

	//TaskInterface::AddUITask(new SomeTask);

	//GetEventDispatcher<TESCombatEvent>()->AddEventSink(&combatSink);
	//pCombatEventDispatcher->RemoveEventSink(&combatSink);
	//return false;

	
	//if(!thisObj)
	//	return true;

	//(*g_gameVM)->m_virtualMachine->m_allStacks.Dump();
	//(*g_gameVM)->m_virtualMachine->m_waitStacks.Dump();

	//DumpClass((*g_gameVM)->m_virtualMachine, 0xC000 / 8);

	/*VMArray<VMVariable> vmData;
	VMVariable forceOpen;
	bool bForce = true;
	forceOpen.Set(&bForce);
	vmData.Push(&forceOpen);
	CallFunctionNoWait<TESObjectREFR>(thisObj, "OpenInventory", vmData);*/

	/*
	auto pTints = (*g_player)->tints;
	_MESSAGE("NPC Tint Entries: %d", pTints->count);

	CharacterCreation::CharGenData * chargenData = nullptr;
	TESNPC * actorBase = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);
	if(actorBase) {
		TESRace * race = actorBase->race.race;
		UInt8 gender = CALL_MEMBER_FN(actorBase, GetSex)();
		chargenData = race->chargenData[gender];
	}

	for(UInt32 i = 0; i < pTints->count; i++)
	{
		BGSCharacterTint::Entry * entry;
		pTints->GetNthItem(i, entry);

		if(!entry->templateEntry && chargenData) {
			entry->templateEntry = chargenData->GetTemplateByIndex(entry->tintIndex);
		}

		_MESSAGE("Entry: Index: %08X, percent: %d", entry->tintIndex, entry->percent);
		switch(entry->GetType())
		{
		case BGSCharacterTint::Entry::kTypeMask:
			{
				gLog.Indent();
				BGSCharacterTint::Template::Mask * templateMask = static_cast<BGSCharacterTint::Template::Mask *>(entry->templateEntry);
				if(templateMask)
				{
					_MESSAGE("Mask: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOp: %08X, unk2C: %08X", templateMask->templateIndex, templateMask->name.data ? templateMask->name.data->Get<char>() : "", templateMask->slot, templateMask->flags, templateMask->unk1F, templateMask->blendOp, templateMask->unk2C);
				}
				gLog.Outdent();
			}
			break;
		case BGSCharacterTint::Entry::kTypeTexture:
			{
				gLog.Indent();
				BGSCharacterTint::Template::TextureSet * templateTexture = static_cast<BGSCharacterTint::Template::TextureSet *>(entry->templateEntry);
				if(templateTexture)
				{
					_MESSAGE("Texture: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOP: %08X, default: %f", templateTexture->templateIndex, templateTexture->name.data ? templateTexture->name.data->Get<char>() : "", templateTexture->slot, templateTexture->flags, templateTexture->unk1F, templateTexture->blendOp, templateTexture->defaultValue);
					gLog.Indent();
					_MESSAGE("Diffuse: %s", templateTexture->diffuse.data ? templateTexture->diffuse.data->Get<char>() : "Empty");
					_MESSAGE("Normal: %s", templateTexture->specular.data ? templateTexture->specular.data->Get<char>() : "Empty");
					_MESSAGE("Specular: %s", templateTexture->normal.data ? templateTexture->normal.data->Get<char>() : "Empty");
					gLog.Outdent();
				}
				gLog.Outdent();
			}
			break;
		case BGSCharacterTint::Entry::kTypePalette:
			{
				gLog.Indent();
				BGSCharacterTint::PaletteEntry* paletteEntry = static_cast<BGSCharacterTint::PaletteEntry*>(entry);
				_MESSAGE("Palette: color: %08X, colorID: %04X", paletteEntry->color, paletteEntry->colorID);

				BGSCharacterTint::Template::Palette * templatePalette = static_cast<BGSCharacterTint::Template::Palette *>(entry->templateEntry);
				if(templatePalette)
				{

					_MESSAGE("Mask: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, unk28: %08X, unk2C: %08X", templatePalette->templateIndex, templatePalette->name.data ? templatePalette->name.data->Get<char>() : "", templatePalette->slot, templatePalette->flags, templatePalette->unk1F, templatePalette->unk28, templatePalette->unk2C);
					gLog.Indent();
					for(UInt32 k = 0; k < templatePalette->colors.count; k++)
					{
						BGSCharacterTint::Template::Palette::ColorData colorData;
						templatePalette->colors.GetNthItem(k, colorData);
						_MESSAGE("Color: Name: %s FormID: %08X, Color: %08X, alpha: %f, blendOp: %08X, colorID: %04X, unk12: %04X, unk14: %04X", colorData.colorForm->fullName.name.data ? colorData.colorForm->fullName.name.data->Get<char>() : "", colorData.colorForm->formID, colorData.colorForm->color.rgb, colorData.alpha, colorData.blendOp, colorData.colorID, colorData.unk12, colorData.unk14);
					}
					gLog.Outdent();
				}
				gLog.Outdent();
			}
			break;

		}

	}

	return true;*/

#ifdef BODY_PAINT
	TESNPC * actorBase = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);
	if(actorBase) {
		TESRace * race = actorBase->race.race;
		UInt8 gender = CALL_MEMBER_FN(actorBase, GetSex)();
		auto chargenData = race->chargenData[gender];
		NiNode * root = thisObj->GetObjectRootNode();
		/*VisitObjects(root, [&](NiAVObject* object) {
			BSTriShape * trishape = object->GetAsBSTriShape();
			if(trishape) {
				BSLightingShaderProperty * lightingShader = ni_cast(trishape->shaderProperty, BSLightingShaderProperty);
				if(lightingShader) {
					BSLightingShaderMaterialBase * material = static_cast<BSLightingShaderMaterialBase *>(lightingShader->shaderMaterial);
					if(material->GetType() == BSLightingShaderMaterialBase::kType_Face) {
						BSLightingShaderMaterialFace * faceMaterial = static_cast<BSLightingShaderMaterialFace*>(material);

						std::string shapeName(trishape->m_name.c_str());
						std::replace(shapeName.begin(), shapeName.end(), '/', '_');
						std::replace(shapeName.begin(), shapeName.end(), ' ', '_');
						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), material->spDiffuseTexture->rendererData->resource, D3DX11_IFF_DDS, std::string(shapeName + "_d.dds").c_str());
						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), material->spNormalTexture->rendererData->resource, D3DX11_IFF_DDS, std::string(shapeName + "_n.dds").c_str());
						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), material->spSmoothnessSpecMaskTexture->rendererData->resource, D3DX11_IFF_DDS, std::string(shapeName + "_s.dds").c_str());
					}
				}
			}
			return false;
		});*/

		VisitObjects(root, [&](NiAVObject* object) {
			BSTriShape * trishape = object->GetAsBSTriShape();
			if(trishape) {
				BSLightingShaderProperty * lightingShader = ni_cast(trishape->shaderProperty, BSLightingShaderProperty);
				if(lightingShader) {
					BSLightingShaderMaterialBase * material = static_cast<BSLightingShaderMaterialBase *>(lightingShader->shaderMaterial);
					if(material->GetType() == BSLightingShaderMaterialBase::kType_SkinTint) {
						BSLightingShaderMaterialFace * faceMaterial = static_cast<BSLightingShaderMaterialFace*>(CreateShaderMaterialByType(BSLightingShaderMaterialBase::kType_Face));
						CALL_MEMBER_FN(faceMaterial, Copy)(material);
						CALL_MEMBER_FN(lightingShader, SetFlag)(21, false); // Turn off SkinTint
						CALL_MEMBER_FN(lightingShader, SetFlag)(9, true); // Turn on FaceTint

						//faceMaterial->baseDiffuse = material->spDiffuseTexture;

						tArray<BGSCharacterTint::Entry*> tempTints;
						tArray<BGSCharacterTint::Entry*> * previousTints = nullptr;
						if(thisObj == (*g_player))
							previousTints = (*g_player)->tints;
						else
							previousTints = actorBase->tints;
						/*if(thisObj == (*g_player))
							CopyCharacterTints(&tempTints, (*g_player)->tints);
						else
							CopyCharacterTints(&tempTints, actorBase->tints);

						for(int i = 0; i < tempTints.count; i++)
						{
							BGSCharacterTint::Entry * entry;
							tempTints.GetNthItem(i, entry);
							auto tintTemplate = chargenData->GetTemplateByIndex(entry->tintIndex);
							entry->templateEntry = tintTemplate;
						}*/


						/*BGSCharacterTint::TextureSetEntry* pTextureSet = (BGSCharacterTint::TextureSetEntry*)CreateCharacterTintEntry((3587L << 16) | BGSCharacterTint::Entry::kTypeTexture);
						pTextureSet->templateEntry = chargenData->GetTemplateByIndex(3587);
						pTextureSet->percent = 100;
						tempTints.Push(pTextureSet);*/

						BGSCharacterTint::PaletteEntry* pSkinReference = nullptr;
						BGSCharacterTint::Template::Palette * pSkinTemplate = nullptr;
						for(int i = 0; i < previousTints->count; i++)
						{
							BGSCharacterTint::Entry* tintEntry;
							previousTints->GetNthItem(i, tintEntry);

							if(tintEntry->tintIndex == 0x490)
							{
								pSkinReference = static_cast<BGSCharacterTint::PaletteEntry*>(tintEntry);
								pSkinTemplate = static_cast<BGSCharacterTint::Template::Palette*>(chargenData->GetTemplateByIndex(tintEntry->tintIndex));
								break;
							}
						}
						BGSCharacterTint::Template::Palette * pSkinToneTemplate = BGSCharacterTint::Template::Palette::Create();
						pSkinToneTemplate->templateIndex = 3602;
						pSkinToneTemplate->name = BSFixedString("Body Skin Tone");
						pSkinToneTemplate->texture = BSFixedString("Actors\\Character\\Character Assets\\TintMasks\\BodySkinTone2k.dds");
						pSkinToneTemplate->slot = BGSCharacterTint::Template::Entry::kSlotSkinTone;
						for(int i = 0; i < pSkinTemplate->colors.count; i++)
						{
							BGSCharacterTint::Template::Palette::ColorData colorData;
							pSkinTemplate->colors.GetNthItem(i, colorData);
							pSkinToneTemplate->colors.Push(colorData);
						}

						BGSCharacterTint::PaletteEntry* pSkinTone = (BGSCharacterTint::PaletteEntry*)CreateCharacterTintEntry((3602L << 16) | BGSCharacterTint::Entry::kTypePalette);
						pSkinTone->color = pSkinReference->color;//0x00CBD3E7;
						pSkinTone->colorID = pSkinReference->colorID;
						pSkinTone->percent = pSkinReference->percent;
						pSkinTone->templateEntry = pSkinToneTemplate;
						tempTints.Push(pSkinTone);

						BGSCharacterTint::Template::Palette * pTattooTemplate = BGSCharacterTint::Template::Palette::Create();
						pTattooTemplate->templateIndex = 3603;
						pTattooTemplate->name = BSFixedString("Sample Tattoo");
						pTattooTemplate->texture = BSFixedString("Actors\\Character\\Character Assets\\TintMasks\\SampleTattoo2k.dds");
						pTattooTemplate->slot = BGSCharacterTint::Template::Entry::kSlotPaint;
						pTattooTemplate->flags = BGSCharacterTint::Template::Entry::kFlagChargenDetail;

						BGSCharacterTint::Template::Palette::ColorData colorData;
						for(int i = 0; i < pSkinTemplate->colors.count; i++)
						{
							pSkinTemplate->colors.GetNthItem(i, colorData);
							pTattooTemplate->colors.Push(colorData);
						}

						BGSCharacterTint::PaletteEntry* pTattoo = (BGSCharacterTint::PaletteEntry*)CreateCharacterTintEntry((3603L << 16) | BGSCharacterTint::Entry::kTypePalette);
						pTattoo->color = 0xffffff00;//colorData.colorForm->color.rgb;//0x00CBD3E7;
						pTattoo->colorID = colorData.colorID;
						pTattoo->percent = 100;
						pTattoo->templateEntry = pTattooTemplate;
						tempTints.Push(pTattoo);


						/*BGSCharacterTint::Template::TextureSet * pScarTemplate = BGSCharacterTint::Template::TextureSet::Create();
						pScarTemplate->templateIndex = 3604;
						pScarTemplate->name = BSFixedString("Sample Scar");
						pScarTemplate->diffuse = BSFixedString("Actors\\Character\\Character Assets\\TintMasks\\Test Scar_d.dds");
						pScarTemplate->normal = BSFixedString("Actors\\Character\\Character Assets\\TintMasks\\Test Scar_n.dds");
						pScarTemplate->specular = BSFixedString("Actors\\Character\\Character Assets\\TintMasks\\Test Scar_s.dds");
						pScarTemplate->slot = BGSCharacterTint::Template::Entry::kSlotFaceDetail;
						pScarTemplate->flags = BGSCharacterTint::Template::Entry::kFlagChargenDetail;
						pScarTemplate->blendOp = BGSCharacterTint::Template::TextureSet::kBlendOpHardLight;

						BGSCharacterTint::TextureSetEntry* pScar = (BGSCharacterTint::TextureSetEntry*)CreateCharacterTintEntry((3604L << 16) | BGSCharacterTint::Entry::kTypeTexture);
						pScar->percent = 100;
						pScar->templateEntry = pScarTemplate;
						tempTints.Push(pScar);*/

						
						/*
						auto pTints = &tempTints;
						_MESSAGE("NPC Tint Entries: %d", pTints->count);

						for(UInt32 i = 0; i < pTints->count; i++)
						{
							BGSCharacterTint::Entry * entry;
							pTints->GetNthItem(i, entry);

							_MESSAGE("Entry: Index: %08X, percent: %d", entry->tintIndex, entry->percent);
							switch(entry->GetType())
							{
							case BGSCharacterTint::Entry::kTypeMask:
								{
									gLog.Indent();
									BGSCharacterTint::Template::Mask * templateMask = static_cast<BGSCharacterTint::Template::Mask *>(entry->templateEntry);
									if(templateMask)
									{
										_MESSAGE("Mask: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOp: %08X, unk2C: %08X", templateMask->templateIndex, templateMask->name.data ? templateMask->name.data->Get<char>() : "", templateMask->slot, templateMask->flags, templateMask->unk1F, templateMask->blendOp, templateMask->unk2C);
									}
									gLog.Outdent();
								}
								break;
							case BGSCharacterTint::Entry::kTypeTexture:
								{
									gLog.Indent();
									BGSCharacterTint::Template::TextureSet * templateTexture = static_cast<BGSCharacterTint::Template::TextureSet *>(entry->templateEntry);
									if(templateTexture)
									{
										_MESSAGE("Texture: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOP: %08X, default: %f", templateTexture->templateIndex, templateTexture->name.data ? templateTexture->name.data->Get<char>() : "", templateTexture->slot, templateTexture->flags, templateTexture->unk1F, templateTexture->blendOp, templateTexture->defaultValue);
										gLog.Indent();
										_MESSAGE("Diffuse: %s", templateTexture->diffuse.data ? templateTexture->diffuse.data->Get<char>() : "Empty");
										_MESSAGE("Normal: %s", templateTexture->specular.data ? templateTexture->specular.data->Get<char>() : "Empty");
										_MESSAGE("Specular: %s", templateTexture->normal.data ? templateTexture->normal.data->Get<char>() : "Empty");
										gLog.Outdent();
									}
									gLog.Outdent();
								}
								break;
							case BGSCharacterTint::Entry::kTypePalette:
								{
									gLog.Indent();
									BGSCharacterTint::PaletteEntry* paletteEntry = static_cast<BGSCharacterTint::PaletteEntry*>(entry);
									_MESSAGE("Palette: color: %08X, colorID: %04X", paletteEntry->color, paletteEntry->colorID);

									BGSCharacterTint::Template::Palette * templatePalette = static_cast<BGSCharacterTint::Template::Palette *>(entry->templateEntry);
									if(templatePalette)
									{

										_MESSAGE("Mask: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, unk28: %08X, unk2C: %08X", templatePalette->templateIndex, templatePalette->name.data ? templatePalette->name.data->Get<char>() : "", templatePalette->slot, templatePalette->flags, templatePalette->unk1F, templatePalette->unk28, templatePalette->unk2C);
										gLog.Indent();
										for(UInt32 k = 0; k < templatePalette->colors.count; k++)
										{
											BGSCharacterTint::Template::Palette::ColorData colorData;
											templatePalette->colors.GetNthItem(k, colorData);
											_MESSAGE("Color: Name: %s FormID: %08X, Color: %08X, alpha: %f, blendOp: %08X, colorID: %04X, unk12: %04X, unk14: %04X", colorData.colorForm->fullName.name.data ? colorData.colorForm->fullName.name.data->Get<char>() : "", colorData.colorForm->formID, colorData.colorForm->color.rgb, colorData.alpha, colorData.blendOp, colorData.colorID, colorData.unk12, colorData.unk14);
										}
										gLog.Outdent();
									}
									gLog.Outdent();
								}
								break;

							}

						}*/
						
						//FillTintTemplates(tempTints, chargenData);
						auto pFaceGenManager = (*g_faceGenManager);

						auto lastTextures = chargenData->defaultTexture;
						BGSTextureSet * bodyTextures = (BGSTextureSet *)LookupFormByID(0xF7E66);
						chargenData->defaultTexture = bodyTextures;

						faceMaterial->baseDiffuse = material->spDiffuseTexture;
						faceMaterial->spTextureSet = nullptr;

						g_charGen.LockBaseTextureOverride();
						g_charGen.SetBaseTintTextureOverride(bodyTextures);
						CreateMergeTintTextures(actorBase, &tempTints, nullptr, 0);
						g_charGen.SetBaseTintTextureOverride(nullptr);
						g_charGen.ReleaseBaseTextureOverride();


						EnterCriticalSection(&g_renderManager->m_textureLock);

						CALL_MEMBER_FN(g_renderTargetManager, LockTextureType)(16);
						CALL_MEMBER_FN(g_renderTargetManager, LockTextureType)(17);
						CALL_MEMBER_FN(g_renderTargetManager, LockTextureType)(18);

						NiPointer<NiTexture> diffuse = CreateTexture("BodyCustomizationDiffuse", 1);
						diffuse->rendererData = CALL_MEMBER_FN(g_renderTargetManager, GetRenderData)(16, 1, 1, 0);
						faceMaterial->spDiffuseTexture = diffuse;

						NiPointer<NiTexture> normal = CreateTexture("BodyCustomizationNormals", 0);
						normal->rendererData = CALL_MEMBER_FN(g_renderTargetManager, GetRenderData)(17, 1, 1, 0);
						faceMaterial->spNormalTexture = normal;
						//faceMaterial->spNormalTexture = material->spNormalTexture;

						NiPointer<NiTexture> spec = CreateTexture("BodyCustomizationSmoothSpec", 0);
						spec->rendererData = CALL_MEMBER_FN(g_renderTargetManager, GetRenderData)(18, 1, 1, 0);
						faceMaterial->spSmoothnessSpecMaskTexture = spec;
						//faceMaterial->spSmoothnessSpecMaskTexture = material->spSmoothnessSpecMaskTexture;

						CALL_MEMBER_FN(g_renderTargetManager, ReleaseTextureType)(16);
						CALL_MEMBER_FN(g_renderTargetManager, ReleaseTextureType)(17);
						CALL_MEMBER_FN(g_renderTargetManager, ReleaseTextureType)(18);

						CALL_MEMBER_FN(lightingShader, SetMaterial)(faceMaterial, true);
						//CALL_MEMBER_FN(lightingShader, MakeValidForRendering)(trishape);

						CALL_MEMBER_FN(trishape, UpdateShaderProperty)();

						chargenData->defaultTexture = lastTextures;
						LeaveCriticalSection(&g_renderManager->m_textureLock);

						/*D3D11_TEXTURE2D_DESC pDesc;
						((ID3D11Texture2D *)diffuse->rendererData->resource)->GetDesc(&pDesc);
						((ID3D11Texture2D *)normal->rendererData->resource)->GetDesc(&pDesc);
						((ID3D11Texture2D *)spec->rendererData->resource)->GetDesc(&pDesc);

						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), diffuse->rendererData->resource, D3DX11_IFF_DDS, "DumpedDiffuse.dds");
						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), normal->rendererData->resource, D3DX11_IFF_DDS, "DumpedNormal.dds");
						D3DX11SaveTextureToFile((*g_D3D11DeviceContext), spec->rendererData->resource, D3DX11_IFF_DDS, "DumpedSpec.dds");*/

						return true;
					}
				}
			}
			return false;
		});
	}

	return true;
#endif

	//if(!thisObj)
	//	return true;

	/*PlayerCharacter * pc2 = DYNAMIC_CAST(thisObj, TESForm, PlayerCharacter);
	if(pc2) {
		auto equipData = pc2->equipData;
		if(equipData) {
			for(int i = 0; i < ActorEquipData::kMaxSlots; i++)
			{
				if(equipData->slots[i].item) {
					DumpClass(equipData->slots[i].item, max(sizeof(TESObjectARMO) >> 3, sizeof(TESObjectWEAP) >> 3));
				}
			}
		}
	}*/

	//DumpNodeChildren(thisObj->GetObjectRootNode());
	//return true;

	/*TESNPC * npc2 = (TESNPC*)LookupFormByID(0x2CCF);
	if(npc2) {
		CharacterCreation::MorphIntensity * intensity = g_morphIntensityMap->Find(&npc2);
		if(intensity) {
			_MESSAGE("Intensity: %f", intensity->morphIntensity);
		}

		if(npc2->morphRegionData)
			npc2->morphRegionData->Dump();
		if(npc2->morphSetData)
			npc2->morphSetData->Dump();

		g_morphIntensityMap->Dump();
	}*/

	Actor * actor = DYNAMIC_CAST(thisObj, TESForm, Actor);
	if(0)
	{
		if(actor->unk300) {
			DumpClass(actor->unk300, 80);
			if(actor->unk300->unk08) {
				DumpClass(actor->unk300->unk08, 80);
			}
		}

		for(int i = 0; i < ActorEquipData::kMaxSlots; i++)
		{
			ActorEquipData::SlotData * slotData = &actor->equipData->slots[i];
			if(actor->equipData->slots[i].instanceData)
			{
				TBO_InstanceData * instanceData = actor->equipData->slots[i].instanceData;
				TESObjectWEAP::InstanceData * pWeapInst = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(instanceData, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
				if(pWeapInst) {
					_MESSAGE("Weapon Slot %d Item %08X", i, actor->equipData->slots[i].item->formID);
				}

				TESObjectARMO::InstanceData * pArmoInst = (TESObjectARMO::InstanceData*)Runtime_DynamicCast(instanceData, RTTI_TBO_InstanceData, RTTI_TESObjectARMO__InstanceData);
				if(pArmoInst) {
					_MESSAGE("Armor Slot %d Item %08X", i, actor->equipData->slots[i].item->formID);
				}

				if(!pWeapInst && !pArmoInst) {
					_MESSAGE("Slot %d Item %08X", i, actor->equipData->slots[i].item->formID);
				}
				
			}
			BGSObjectInstanceExtra * extraData = actor->equipData->slots[i].extraData;
			if(extraData)
			{
				if(extraData->data)
				{
					for(int i = 0; i < extraData->data->blockSize / sizeof(BGSObjectInstanceExtra::Data::Form); i++)
					{
						TESForm * form = LookupFormByID(extraData->data->forms[i].formId);
						_MESSAGE("Owner %08X InstanceData: %08X", actor->formID, form->formID);
					}
				}
			}
		}

		return true;
	}
	if(0)
	{
		TESNPC * npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);
		if(npc) {
			_MESSAGE("Actor: %08X ActorBase: %08X BaseContainer", actor->formID, npc->formID);

			TESContainer * container = DYNAMIC_CAST(npc, TESNPC, TESContainer);
			if(container)
			{
				for(UInt32 i = 0; i < container->numEntries; i++)
				{
					_MESSAGE("%016I64X %s - Count: %d", container->entries[i]->form->formID, GetObjectClassName(container->entries[i]->form), container->entries[i]->count);
					DumpClass(container->entries[i]->data, sizeof(TESContainer::Entry::Data) >> 3);
				}
			}
		}

		_MESSAGE("Actor: %08X Inventory", actor->formID);
		auto inventory = actor->inventoryList;
		if(inventory) {
			for(int i = 0; i < inventory->items.count; i++) {
				BGSInventoryItem item;
				inventory->items.GetNthItem(i, item);
				item.Dump();
			}
		}
	}

	if(0) {
		TESNPC * npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);
		if(npc) {
			npc->weightLarge = 1.0;
			npc->weightMuscular = 0.0;
			npc->weightThin = 0.0;
			CALL_MEMBER_FN(actor, UpdateEquipment)();
		}

		return true;
	}

	if(thisObj) {
		//DumpNodeChildren(thisObj->GetObjectRootNode());

		/*BGSInventoryList	* inventory = thisObj->inventoryList;
		_MESSAGE("Reference: %08X Inventory Dump %016I64X", thisObj->formID, inventory);

		if(inventory) {
			for(int i = 0; i < inventory->items.count; i++) {
				BGSInventoryItem item;
				inventory->items.GetNthItem(i, item);

				_MESSAGE("%016I64X %s", item.form, GetObjectClassName(item.form));
				item.Dump();
			}
		}

		ExtraDataList		* extraDataList = thisObj->extraDataList;
		_MESSAGE("Reference: %08X Data Dump %016I64X", thisObj->formID, extraDataList);
		if(extraDataList) {
			extraDataList->Dump();
		}*/
	}

	
	return true;


	TESNPC * npc = DYNAMIC_CAST(thisObj->baseForm, TESForm, TESNPC);
	if(0)
	{
		TESRace * race = npc->race.race;
		UInt8 gender = CALL_MEMBER_FN(npc, GetSex)();

		CharacterCreation::CharGenData * chargen = race->chargenData[gender];
		TESRace::BoneScaleMap * boneScaleMap = race->boneScaleMap[gender];

		auto tints = chargen->tintData;
		_MESSAGE("TintData Categories: %d", tints->count);
		for(UInt32 i = 0; i < tints->count; i++)
		{
			CharacterCreation::TintData * tintData;
			tints->GetNthItem(i, tintData);

			_MESSAGE("TintData Category: %s, Type: %08X, Count: %d", tintData->category.data ? tintData->category.data->Get<char>() : "", tintData->type, tintData->entry.count);
			gLog.Indent();
			for(UInt32 k = 0; k < tintData->entry.count; k++)
			{
				BGSCharacterTint::Template::Entry * templateEntry;
				tintData->entry.GetNthItem(k, templateEntry);

				BGSCharacterTint::Template::Mask * pMask = (BGSCharacterTint::Template::Mask *)Runtime_DynamicCast(templateEntry, RTTI_BGSCharacterTint__Template__Entry, RTTI_BGSCharacterTint__Template__Mask);
				if(pMask)
				{
					_MESSAGE("Mask: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOp: %08X, unk2C: %08X", pMask->templateIndex, pMask->name.data ? pMask->name.data->Get<char>() : "", pMask->slot, pMask->flags, pMask->unk1F, pMask->blendOp, pMask->unk2C);
				}
				BGSCharacterTint::Template::Palette * pPalette = (BGSCharacterTint::Template::Palette *)Runtime_DynamicCast(templateEntry, RTTI_BGSCharacterTint__Template__Entry, RTTI_BGSCharacterTint__Template__Palette);
				if(pPalette)
				{
					_MESSAGE("Palette: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, unk28: %08X, unk2C: %08X", pPalette->templateIndex, pPalette->name.data ? pPalette->name.data->Get<char>() : "", pPalette->slot, pPalette->flags, pPalette->unk1F, pPalette->unk28, pPalette->unk2C);
					gLog.Indent();
					for(UInt32 k = 0; k < pPalette->colors.count; k++)
					{
						BGSCharacterTint::Template::Palette::ColorData colorData;
						pPalette->colors.GetNthItem(k, colorData);
						_MESSAGE("Color: Name: %s FormID: %08X, Color: %08X, alpha: %f, blendOp: %08X, colorID: %04X, unk12: %04X, unk14: %04X", colorData.colorForm->fullName.name.data ? colorData.colorForm->fullName.name.data->Get<char>() : "", colorData.colorForm->formID, colorData.colorForm->color.rgb, colorData.alpha, colorData.blendOp, colorData.colorID, colorData.unk12, colorData.unk14);
					}
					gLog.Outdent();
				}
				BGSCharacterTint::Template::TextureSet * pTS = (BGSCharacterTint::Template::TextureSet *)Runtime_DynamicCast(templateEntry, RTTI_BGSCharacterTint__Template__Entry, RTTI_BGSCharacterTint__Template__TextureSet);
				if(pTS)
				{
					_MESSAGE("TextureSet: Index: %08X, Name: %s, slot: %d, flags: %d, unk1F: %d, blendOp: %08X, defaultValue: %f", pTS->templateIndex, pTS->name.data ? pTS->name.data->Get<char>() : "", pTS->slot, pTS->flags, pTS->unk1F, pTS->blendOp, pTS->defaultValue);
					gLog.Indent();
					_MESSAGE("Diffuse: %s", pTS->diffuse.data ? pTS->diffuse.data->Get<char>() : "Empty");
					_MESSAGE("Normal: %s", pTS->specular.data ? pTS->specular.data->Get<char>() : "Empty");
					_MESSAGE("Specular: %s", pTS->normal.data ? pTS->normal.data->Get<char>() : "Empty");
					gLog.Outdent();
				}
			}
			gLog.Outdent();
		}

		/*auto morphs = chargen->faceMorphs;
		_MESSAGE("FaceMorphRegions: %d", morphs->count);
		for(UInt32 i = 0; i < morphs->count; i++)
		{
			CharacterCreation::FaceMorphRegion * region;
			morphs->GetNthItem(i, region);

			_MESSAGE("MorphRegion Index: %08X, Name: %s", region->index, region->name.data ? region->name.data->Get<char>() : "");
			//gLog.Indent();
			//region->dataSet.Dump();
			//gLog.Outdent();
		}

		auto morphGroups = chargen->morphGroups;
		_MESSAGE("MorphGroups: %d", morphGroups->count);
		for(UInt32 i = 0; i < morphGroups->count; i++)
		{
			CharacterCreation::MorphGroup * morphGroup;
			morphGroups->GetNthItem(i, morphGroup);

			_MESSAGE("MorphGroup Key: %08X, Name: %s, Count: %d", morphGroup->key, morphGroup->name.data ? morphGroup->name.data->Get<char>() : "", morphGroup->presets.count);
			gLog.Indent();
			for(UInt32 k = 0; k < morphGroup->presets.count; k++)
			{
				CharacterCreation::MorphGroup::Preset preset;
				morphGroup->presets.GetNthItem(k, preset);

				_MESSAGE("Morph Index: %08X, Name: %s, Morph: %s", preset.index, preset.name.data ? preset.name.data->Get<char>() : "", preset.morph.data ? preset.morph.data->Get<char>() : "");
				gLog.Indent();
				if(preset.texture)
				{
					for(UInt32 n = 0; n < 8; n++)
					{
						_MESSAGE("%d - %s", n, preset.texture->texture[n].str.data ? preset.texture->texture[n].str.data->Get<char>() : "");
					}
				}
				gLog.Outdent();
			}
			gLog.Outdent();
		}

		_MESSAGE("morphSliders");
		gLog.Indent();
		race->morphSliders.Dump();
		gLog.Outdent();

		_MESSAGE("WeightMap 1");
		gLog.Indent();
		boneScaleMap->weightMap1.Dump();
		gLog.Outdent();
		_MESSAGE("WeightMap 2");
		gLog.Indent();
		boneScaleMap->weightMap2.Dump();
		gLog.Outdent();

		_MESSAGE("morphSetData");
		gLog.Indent();
		if(npc->morphSetData)
		{
			npc->morphSetData->Dump();
		}
		gLog.Outdent();

		_MESSAGE("morphRegionData");
		gLog.Indent();
		if(npc->morphRegionData)
		{
			npc->morphRegionData->Dump();
		}
		gLog.Outdent();

		tArray<BGSCharacterTint::Entry*> * tintArray[2];
		tintArray[0] = npc->tints;
		tintArray[1] = pc ? pc->tints : nullptr;

		for(UInt32 t = 0; t < 2; t++)
		{
			gLog.Indent();
			if(tintArray[t])
			{
				if(t == 0)
					_MESSAGE("NPC Tint Entries: %d", tintArray[t]->count);
				if(t == 1)
					_MESSAGE("PC Tint Entries: %d", tintArray[t]->count);

				for(UInt32 i = 0; i < tintArray[t]->count; i++)
				{
					BGSCharacterTint::Entry * entry;
					tintArray[t]->GetNthItem(i, entry);

					_MESSAGE("Entry: Index: %08X, percent: %d", entry->tintIndex, entry->percent);
					switch(entry->GetType())
					{
						case BGSCharacterTint::Entry::kTypeMask:
							{
								gLog.Indent();
								BGSCharacterTint::Template::Mask * templateMask = static_cast<BGSCharacterTint::Template::Mask *>(entry->templateEntry);
								if(templateMask)
								{
									_MESSAGE("Mask: Index: %08X, Name: %s, unk18: %d, unk1E: %d, unk1F: %d, unk28: %08X, unk2C: %08X", templateMask->templateIndex, templateMask->name.data ? templateMask->name.data->Get<char>() : "", templateMask->unk18, templateMask->unk1E, templateMask->unk1F, templateMask->unk28, templateMask->unk2C);
									Condition * pCondition = templateMask->conditions;
									while(pCondition)
									{
										ObScriptCommand * cmd = GetCommandByOpcode(pCondition->functionId);
										_MESSAGE("Condition: Compare: %f, Type: %d Function: %s, ReferenceType: %d, P1: %016I64X, P2: %016I64X", pCondition->compareValue, pCondition->comparisonType, cmd ? cmd->longName : "no name", pCondition->referenceType, pCondition->param1.form, pCondition->param2.form);
										pCondition = pCondition->next;
									}
								}
								gLog.Outdent();
							}
							break;
						case BGSCharacterTint::Entry::kTypeTexture:
							{
								gLog.Indent();
								BGSCharacterTint::Template::TexureSet * templateTexture = static_cast<BGSCharacterTint::Template::TexureSet *>(entry->templateEntry);
								if(templateTexture)
								{
									_MESSAGE("Texture: Index: %08X, Name: %s, unk18: %d, unk1E: %d, unk1F: %d, unk38: %08X, unk3C: %08X", templateTexture->templateIndex, templateTexture->name.data ? templateTexture->name.data->Get<char>() : "", templateTexture->unk18, templateTexture->unk1E, templateTexture->unk1F, templateTexture->unk38, templateTexture->unk3C);
									gLog.Indent();
									_MESSAGE("Diffuse: %s", templateTexture->diffuse.data ? templateTexture->diffuse.data->Get<char>() : "Empty");
									_MESSAGE("Normal: %s", templateTexture->specular.data ? templateTexture->specular.data->Get<char>() : "Empty");
									_MESSAGE("Specular: %s", templateTexture->normal.data ? templateTexture->normal.data->Get<char>() : "Empty");
									gLog.Outdent();
									Condition * pCondition = templateTexture->conditions;
									while(pCondition)
									{
										ObScriptCommand * cmd = GetCommandByOpcode(pCondition->functionId);
										_MESSAGE("Condition: Compare: %f, Type: %d Function: %s, ReferenceType: %d, P1: %016I64X, P2: %016I64X", pCondition->compareValue, pCondition->comparisonType, cmd ? cmd->longName : "no name", pCondition->referenceType, pCondition->param1.form, pCondition->param2.form);
										pCondition = pCondition->next;
									}
								}
								gLog.Outdent();
							}
							break;
						case BGSCharacterTint::Entry::kTypePalette:
							{
								gLog.Indent();
								BGSCharacterTint::PaletteEntry* paletteEntry = static_cast<BGSCharacterTint::PaletteEntry*>(entry);
								_MESSAGE("Palette: color: %08X, colorID: %04X", paletteEntry->color, paletteEntry->colorID);

								BGSCharacterTint::Template::Palette * templatePalette = static_cast<BGSCharacterTint::Template::Palette *>(entry->templateEntry);
								if(templatePalette)
								{
									
									_MESSAGE("Mask: Index: %08X, Name: %s, unk18: %d, unk1E: %d, unk1F: %d, unk28: %08X, unk2C: %08X", templatePalette->templateIndex, templatePalette->name.data ? templatePalette->name.data->Get<char>() : "", templatePalette->unk18, templatePalette->unk1E, templatePalette->unk1F, templatePalette->unk28, templatePalette->unk2C);
									gLog.Indent();
									for(UInt32 k = 0; k < templatePalette->colors.count; k++)
									{
										BGSCharacterTint::Template::Palette::ColorData colorData;
										templatePalette->colors.GetNthItem(k, colorData);
										_MESSAGE("Color: Name: %s FormID: %08X, Color: %08X, alpha: %f, unk0C: %08X, colorID: %04X, unk12: %04X, unk14: %04X", colorData.colorForm->fullName.name.data ? colorData.colorForm->fullName.name.data->Get<char>() : "", colorData.colorForm->formID, colorData.colorForm->color.rgb, colorData.alpha, colorData.unk0C, colorData.colorID, colorData.unk12, colorData.unk14);
									}
									gLog.Outdent();
									Condition * pCondition = templatePalette->conditions;
									while(pCondition)
									{
										ObScriptCommand * cmd = GetCommandByOpcode(pCondition->functionId);
										_MESSAGE("Condition: Compare: %f, Type: %d Function: %s, ReferenceType: %d, P1: %016I64X, P2: %016I64X", pCondition->compareValue, pCondition->comparisonType, cmd ? cmd->longName : "no name", pCondition->referenceType, pCondition->param1.form, pCondition->param2.form);
										pCondition = pCondition->next;
									}
									
								}
								gLog.Outdent();
							}
							break;
					
					}

				}
			}
			gLog.Outdent();
		}*/
	}

	Console_Print("F4SE test func executed");
	return true;
}
#endif

void Hooks_ObScript_Commit()
{
	ObScriptCommand cmd = *s_hijackedCommand;

	cmd.longName = "GetF4SEVersion";
	cmd.shortName = "";
	cmd.helpText = "";
	cmd.needsParent = 0;
	cmd.numParams = 0;
	cmd.execute = GetF4SEVersion_Execute;
	cmd.flags = 0;

	SafeWriteBuf((uintptr_t)s_hijackedCommand, &cmd, sizeof(cmd));

#ifdef _DEBUG
	if(s_testCommand)
	{
		ObScriptCommand testcmd = *s_testCommand;

		testcmd.longName = "F4SETestCode";
		testcmd.shortName = "";
		testcmd.helpText = "";
		testcmd.needsParent = 0;
		testcmd.numParams = 0;
		testcmd.params = nullptr;
		testcmd.execute = F4SETestCode_Execute;
		testcmd.flags = 0;

		SafeWriteBuf((uintptr_t)s_testCommand, &testcmd, sizeof(testcmd));
	}
#endif

	/*// Allow re-enable Survival
	UInt8 nop[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	SafeWriteBuf(RelocAddr <uintptr_t>(0x00B6656D).GetUIntPtr(), nop, sizeof(nop));

	// Skip difficulty check
	UInt8 jmp1c[] = {0xEB, 0x27};
	SafeWriteBuf(RelocAddr <uintptr_t>(0x00E89D81).GetUIntPtr(), jmp1c, sizeof(jmp1c));
	SafeWriteBuf(RelocAddr <uintptr_t>(0x00E89DE1).GetUIntPtr(), jmp1c, sizeof(jmp1c));*/

	// 140B6646C - Pause menu Quicksave/Save check
	// 14128DA81 - Quicksave check

	// 0B6656D
	// 140B6656D
	// 0E96979
#ifdef BODY_PAINT
	// Hook to re-route the face texture
	{
		struct GetActorBaseHeadData_Code : Xbyak::CodeGenerator {
			GetActorBaseHeadData_Code(void * buf, UInt64 funcAddr) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label funcLabel;
				Xbyak::Label retnLabel;

				mov(rcx, r15);
				call(ptr [rip + funcLabel]);
				mov(rcx, rax);
				jmp(ptr [rip + retnLabel]);

				L(funcLabel);
				dq(funcAddr);

				L(retnLabel);
				dq(GetActorBaseHeadData_Start.GetUIntPtr() + 0x07);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		GetActorBaseHeadData_Code code(codeBuf, (uintptr_t)GetActorBaseHeadData_Hook);
		g_localTrampoline.EndAlloc(code.getCurr());

		g_branchTrampoline.Write6Branch(GetActorBaseHeadData_Start.GetUIntPtr(), uintptr_t(code.getCode()));
		SafeWrite8(GetActorBaseHeadData_Start.GetUIntPtr() + 0x06, 0x90);
	}

	// Hook to bypass morph groups in tint textures
	{
		struct GetMorphGroups_Code : Xbyak::CodeGenerator {
			GetMorphGroups_Code(void * buf, UInt64 funcAddr) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label funcLabel;
				Xbyak::Label retnLabel;

				mov(rcx, rax);
				call(ptr [rip + funcLabel]);
				test(rax, rax);
				jmp(ptr [rip + retnLabel]);

				L(funcLabel);
				dq(funcAddr);

				L(retnLabel);
				dq(GetMorphGroups_Start.GetUIntPtr() + 0x07);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		GetMorphGroups_Code code(codeBuf, (uintptr_t)GetMorphGroups_Hook);
		g_localTrampoline.EndAlloc(code.getCurr());

		g_branchTrampoline.Write6Branch(GetMorphGroups_Start.GetUIntPtr(), uintptr_t(code.getCode()));
		SafeWrite8(GetMorphGroups_Start.GetUIntPtr() + 0x06, 0x90);
	}

	g_branchTrampoline.Write5Call(StaticTextureIndexed_Ctor_Start.GetUIntPtr(), (uintptr_t)StaticTextureIndexed_ctor_Hook);
#endif
}
