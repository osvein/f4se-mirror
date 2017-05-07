#if NUM_PARAMS > 10
#error PapyrusStructDef: too many params
#endif

template<const char* T_structName
#if NUM_PARAMS >= 1
	, typename T_arg1
#endif
#if NUM_PARAMS >= 2
	, typename T_arg2
#endif
#if NUM_PARAMS >= 3
	, typename T_arg3
#endif
#if NUM_PARAMS >= 4
	, typename T_arg4
#endif
#if NUM_PARAMS >= 5
	, typename T_arg5
#endif
#if NUM_PARAMS >= 6
	, typename T_arg6
#endif
#if NUM_PARAMS >= 7
	, typename T_arg7
#endif
#if NUM_PARAMS >= 8
	, typename T_arg8
#endif
#if NUM_PARAMS >= 9
	, typename T_arg9
#endif
#if NUM_PARAMS >= 10
	, typename T_arg10
#endif
>
class CLASS_NAME : public VMStructBase<T_structName>
{
public:
	CLASS_NAME() : VMStructBase(), m_struct(nullptr) { }
	~CLASS_NAME() { }

	template<int N, typename T>
	void Get(T * value) { };

#if NUM_PARAMS >= 1
	template<> void Get<0>(T_arg1 * value)
	{
		*value = m_arg1;
	}
#endif
#if NUM_PARAMS >= 2
	template<> void Get<1>(T_arg2 * value)
	{
		*value = m_arg2;
	}
#endif
#if NUM_PARAMS >= 3
	template<> void Get<2>(T_arg3 * value)
	{
		*value = m_arg3;
	}
#endif
#if NUM_PARAMS >= 4
	template<> void Get<3>(T_arg4 * value)
	{
		*value = m_arg4;
	}
#endif
#if NUM_PARAMS >= 5
	template<> void Get<4>(T_arg5 * value)
	{
		*value = m_arg5;
	}
#endif
#if NUM_PARAMS >= 6
	template<> void Get<5>(T_arg6 * value)
	{
		*value = m_arg6;
	}
#endif
#if NUM_PARAMS >= 7
	template<> void Get<6>(T_arg7 * value)
	{
		*value = m_arg7;
	}
#endif
#if NUM_PARAMS >= 8
	template<> void Get<7>(T_arg8 * value)
	{
		*value = m_arg8;
	}
#endif
#if NUM_PARAMS >= 9
	template<> void Get<8>(T_arg9 * value)
	{
		*value = m_arg9;
	}
#endif
#if NUM_PARAMS >= 10
	template<> void Get<9>(T_arg10 * value)
	{
		*value = m_arg10;
	}
#endif

	template<int N, typename T>
	void Set(T a1, bool bReference = true) { }

#if NUM_PARAMS >= 1
	template<> void Set<0>(T_arg1 a1, bool bReference)
	{
		m_arg1 = a1;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[0], &a1, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 2
	template<> void Set<1>(T_arg2 a2, bool bReference)
	{
		m_arg2 = a2;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[1], &a2, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 3
	template<> void Set<2>(T_arg3 a3, bool bReference)
	{
		m_arg3 = a3;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[2], &a3, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 4
	template<> void Set<3>(T_arg4 a4, bool bReference)
	{
		m_arg4 = a4;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[3], &a4, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 5
	template<> void Set<4>(T_arg5 a5, bool bReference)
	{
		m_arg5 = a5;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[4], &a5, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 6
	template<> void Set<5>(T_arg6 a6, bool bReference)
	{
		m_arg6 = a6;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[5], &a6, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 7
	template<> void Set<6>(T_arg7 a7, bool bReference)
	{
		m_arg7 = a7;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[6], &a7, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 8
	template<> void Set<7>(T_arg8 a8, bool bReference)
	{
		m_arg8 = a8;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[7], &a8, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 9
	template<> void Set<8>(T_arg9 a9, bool bReference)
	{
		m_arg9 = a9;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[8], &a9, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif
#if NUM_PARAMS >= 10
	template<> void Set<9>(T_arg10 a10, bool bReference)
	{
		m_arg10 = a10;

		if(m_struct && bReference) {
			VMValue * value = m_struct->GetStruct();
			PackValue(&value[9], &a10, (*g_gameVM)->m_virtualMachine);
		}
	}
#endif

	void PackStruct(VMValue * dst, VirtualMachine * vm)
	{
		// Clean out the old value
		dst->SetNone();

		BSFixedString structName(T_structName);
		VMStructTypeInfo * typeInfo = nullptr;
		if(vm->GetStructTypeInfo(&structName, &typeInfo))
		{
			if(typeInfo->m_data.count <= NUM_PARAMS)
			{
				if(CreateStruct(dst, &structName, vm))
				{
					VMValue * values = dst->data.strct->GetStruct();

					// Packing is handled by the setters
#if NUM_PARAMS >= 1
					PackValue(&values[0], &m_arg1, vm);
#endif
#if NUM_PARAMS >= 2
					PackValue(&values[1], &m_arg2, vm);
#endif
#if NUM_PARAMS >= 3
					PackValue(&values[2], &m_arg3, vm);
#endif
#if NUM_PARAMS >= 4
					PackValue(&values[3], &m_arg4, vm);
#endif
#if NUM_PARAMS >= 5
					PackValue(&values[4], &m_arg5, vm);
#endif
#if NUM_PARAMS >= 6
					PackValue(&values[5], &m_arg6, vm);
#endif
#if NUM_PARAMS >= 7
					PackValue(&values[6], &m_arg7, vm);
#endif
#if NUM_PARAMS >= 8
					PackValue(&values[7], &m_arg8, vm);
#endif
#if NUM_PARAMS >= 9
					PackValue(&values[8], &m_arg9, vm);
#endif
#if NUM_PARAMS >= 10
					PackValue(&values[9], &m_arg10, vm);
#endif
				}
			}

			typeInfo->Release();
		}

		structName.Release();
	}

	void UnpackStruct(VMValue * src)
	{
		BSFixedString structName(T_structName);
		VMStructTypeInfo * typeInfo = nullptr;
		VirtualMachine * vm = (*g_gameVM)->m_virtualMachine;
		if(vm->GetStructTypeInfo(&structName, &typeInfo))
		{
			if(typeInfo->m_data.count <= NUM_PARAMS)
			{
				VMValue * values = src->data.strct->GetStruct();

				// Unpacking is handled by the getters
#if NUM_PARAMS >= 1
				UnpackValue(&m_arg1, &values[0]);
#endif
#if NUM_PARAMS >= 2
				UnpackValue(&m_arg2, &values[1]);
#endif
#if NUM_PARAMS >= 3
				UnpackValue(&m_arg3, &values[2]);
#endif
#if NUM_PARAMS >= 4
				UnpackValue(&m_arg4, &values[3]);
#endif
#if NUM_PARAMS >= 5
				UnpackValue(&m_arg5, &values[4]);
#endif
#if NUM_PARAMS >= 6
				UnpackValue(&m_arg6, &values[5]);
#endif
#if NUM_PARAMS >= 7
				UnpackValue(&m_arg7, &values[6]);
#endif
#if NUM_PARAMS >= 8
				UnpackValue(&m_arg8, &values[7]);
#endif
#if NUM_PARAMS >= 9
				UnpackValue(&m_arg9, &values[8]);
#endif
#if NUM_PARAMS >= 10
				UnpackValue(&m_arg10, &values[9]);
#endif
				m_struct = src->data.strct;
			}

			typeInfo->Release();
		}

		structName.Release();
	}

protected:
	VMValue::StructData * m_struct;
#if NUM_PARAMS >= 1
	T_arg1 m_arg1;
#endif
#if NUM_PARAMS >= 2
	T_arg2 m_arg2;
#endif
#if NUM_PARAMS >= 3
	T_arg3 m_arg3;
#endif
#if NUM_PARAMS >= 4
	T_arg4 m_arg4;
#endif
#if NUM_PARAMS >= 5
	T_arg5 m_arg5;
#endif
#if NUM_PARAMS >= 6
	T_arg6 m_arg6;
#endif
#if NUM_PARAMS >= 7
	T_arg7 m_arg7;
#endif
#if NUM_PARAMS >= 8
	T_arg8 m_arg8;
#endif
#if NUM_PARAMS >= 9
	T_arg9 m_arg9;
#endif
#if NUM_PARAMS >= 10
	T_arg10 m_arg10;
#endif
};

template <const char * NAME
#if NUM_PARAMS >= 1
	, typename T_arg1
#endif
#if NUM_PARAMS >= 2
	, typename T_arg2
#endif
#if NUM_PARAMS >= 3
	, typename T_arg3
#endif
#if NUM_PARAMS >= 4
	, typename T_arg4
#endif
#if NUM_PARAMS >= 5
	, typename T_arg5
#endif
#if NUM_PARAMS >= 6
	, typename T_arg6
#endif
#if NUM_PARAMS >= 7
	, typename T_arg7
#endif
#if NUM_PARAMS >= 8
	, typename T_arg8
#endif
#if NUM_PARAMS >= 9
	, typename T_arg9
#endif
#if NUM_PARAMS >= 10
	, typename T_arg10
#endif
>
struct IsStructType<CLASS_NAME<NAME
#if NUM_PARAMS >= 1
	, T_arg1
#endif
#if NUM_PARAMS >= 2
	, T_arg2
#endif
#if NUM_PARAMS >= 3
	, T_arg3
#endif
#if NUM_PARAMS >= 4
	, T_arg4
#endif
#if NUM_PARAMS >= 5
	, T_arg5
#endif
#if NUM_PARAMS >= 6
	, T_arg6
#endif
#if NUM_PARAMS >= 7
	, T_arg7
#endif
#if NUM_PARAMS >= 8
	, T_arg8
#endif
#if NUM_PARAMS >= 9
	, T_arg9
#endif
#if NUM_PARAMS >= 10
	, T_arg10
#endif
>>
{
	static const bool value = true;
	static inline const char* name() { return NAME; };
};

template <const char * T
#if NUM_PARAMS >= 1
	, typename T_arg1
#endif
#if NUM_PARAMS >= 2
	, typename T_arg2
#endif
#if NUM_PARAMS >= 3
	, typename T_arg3
#endif
#if NUM_PARAMS >= 4
	, typename T_arg4
#endif
#if NUM_PARAMS >= 5
	, typename T_arg5
#endif
#if NUM_PARAMS >= 6
	, typename T_arg6
#endif
#if NUM_PARAMS >= 7
	, typename T_arg7
#endif
#if NUM_PARAMS >= 8
	, typename T_arg8
#endif
#if NUM_PARAMS >= 9
	, typename T_arg9
#endif
#if NUM_PARAMS >= 10
	, typename T_arg10
#endif
>
void PackValue(VMValue * dst, CLASS_NAME<T
#if NUM_PARAMS >= 1
, T_arg1
#endif
#if NUM_PARAMS >= 2
, T_arg2
#endif
#if NUM_PARAMS >= 3
, T_arg3
#endif
#if NUM_PARAMS >= 4
, T_arg4
#endif
#if NUM_PARAMS >= 5
, T_arg5
#endif
#if NUM_PARAMS >= 6
, T_arg6
#endif
#if NUM_PARAMS >= 7
, T_arg7
#endif
#if NUM_PARAMS >= 8
, T_arg8
#endif
#if NUM_PARAMS >= 9
, T_arg9
#endif
#if NUM_PARAMS >= 10
, T_arg10
#endif
> * src, VirtualMachine * vm)
{
	src->PackStruct(dst, vm);
}


template <const char * T
#if NUM_PARAMS >= 1
	, typename T_arg1
#endif
#if NUM_PARAMS >= 2
	, typename T_arg2
#endif
#if NUM_PARAMS >= 3
	, typename T_arg3
#endif
#if NUM_PARAMS >= 4
	, typename T_arg4
#endif
#if NUM_PARAMS >= 5
	, typename T_arg5
#endif
#if NUM_PARAMS >= 6
	, typename T_arg6
#endif
#if NUM_PARAMS >= 7
	, typename T_arg7
#endif
#if NUM_PARAMS >= 8
	, typename T_arg8
#endif
#if NUM_PARAMS >= 9
	, typename T_arg9
#endif
#if NUM_PARAMS >= 10
	, typename T_arg10
#endif
>
void UnpackValue(CLASS_NAME<T
#if NUM_PARAMS >= 1
, T_arg1
#endif
#if NUM_PARAMS >= 2
, T_arg2
#endif
#if NUM_PARAMS >= 3
, T_arg3
#endif
#if NUM_PARAMS >= 4
, T_arg4
#endif
#if NUM_PARAMS >= 5
, T_arg5
#endif
#if NUM_PARAMS >= 6
, T_arg6
#endif
#if NUM_PARAMS >= 7
, T_arg7
#endif
#if NUM_PARAMS >= 8
, T_arg8
#endif
#if NUM_PARAMS >= 9
, T_arg9
#endif
#if NUM_PARAMS >= 10
, T_arg10
#endif
> * dst, VMValue * src)
{
	dst->UnpackStruct(src);
}
