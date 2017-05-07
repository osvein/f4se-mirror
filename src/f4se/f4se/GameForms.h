#pragma once

#include "f4se/GameFormComponents.h"
#include "f4se_common/Relocation.h"

class TESForm;

typedef TESForm* (* _LookupFormByID)(UInt32 id);
extern RelocAddr <_LookupFormByID> LookupFormByID;

// 20
class TESForm : public BaseFormComponent
{
public:
	enum { kTypeID = 0 };	// special-case

	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual void	Unk_13();
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();
	virtual void	Unk_2C();
	virtual void	Unk_2D();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();
	virtual void	Unk_34();
	virtual void	Unk_35();
	virtual void	Unk_36();
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();
	virtual void	Unk_3E();
	virtual void	Unk_3F();
	virtual void	Unk_40();
	virtual void	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43();
	virtual void	Unk_44();
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();

	void	* unk08;	// 08
	UInt32	flags;		// 10
	UInt32	formID;		// 14
	UInt16	unk18;		// 18
	UInt8	formType;	// 1A
	UInt8	unk1B;		// 1B
	UInt8	pad1C[4];	// 1C
};
