#pragma once

#include "f4se_common/Relocation.h"
#include "f4se/GameTypes.h"

class Actor;
class TESNPC;
class BGSHeadPart;
class BGSColorForm;
class BGSTextureSet;
class ActorValueInfo;

// 146FC3190 -> 9238D200

class BGSCharacterTint
{
public:
	class Template
	{
	public:
		// 20
		class Entry
		{
		public:
			virtual ~Entry();

			virtual void Unk_01();
			virtual void Unk_02();
			virtual void Unk_03();
			virtual void Unk_04() = 0;

			BSFixedString	name;		// 08
			void			* unk10;	// 10
			UInt32			unk18;		// 18
			UInt16			unk1C;		// 1C
			UInt8			unk1E;		// 1E
			UInt8			unk1F;		// 1F
		};

		// 30
		class Mask : public Entry
		{
		public:
			virtual void Unk_01();
			virtual void Unk_02();
			virtual void Unk_03();
			virtual void Unk_04();

			void	* unk20;	// 20
			UInt32	unk28;		// 28
			UInt32	unk2C;		// 2C
		};

		// 48
		class Palette : public Entry
		{
		public:
			virtual void Unk_01();
			virtual void Unk_02();
			virtual void Unk_03();
			virtual void Unk_04();

			struct ColorData
			{
				BGSColorForm * colorForm;	// 00
				float		unk08;			// 08
				UInt32		unk0C;			// 0C
				UInt16		unk10;			// 10
				UInt16		unk12;			// 12
				UInt32		unk14;			// 14
			};

			BSFixedString texturePath;	// 20
			UInt32	unk28;				// 28
			UInt32	unk2C;				// 2C
			tArray<ColorData>	colors;	// 30
		};

		// 40
		class TexureSet : public Entry
		{
		public:
			virtual void Unk_01();
			virtual void Unk_02();
			virtual void Unk_03();
			virtual void Unk_04();

			BSFixedString texturePath;	// 20
			void	* unk28;	// 28
			void	* unk30;	// 30
			UInt64	unk38;		// 38
		};
	};

	// 18
	class Entry
	{
	public:
		virtual ~Entry();

		virtual void Unk_01(void);
		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void Unk_05(void) = 0;
		virtual void Unk_06(void);

		Template * templateEntry;	// 08
		UInt16		unk10;			// 10
		UInt8		unk12;			// 12	divided by 100
		UInt8		pad13;			// 13
		UInt32		pad14;			// 14
	};

	// 18
	class MaskEntry : public Entry
	{
	public:
		virtual ~MaskEntry();

		virtual void Unk_01(void);
		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void Unk_05(void);
		virtual void Unk_06(void);
	};

	// 20
	class PaletteEntry : public MaskEntry
	{
	public:
		virtual ~PaletteEntry();

		virtual void Unk_01(void);
		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void Unk_05(void);
		virtual void Unk_06(void);

		SInt32	unk18;	// 18
		SInt16	unk1C;	// 1C
		UInt16	pad1E;	// 1E
	};

	// 18
	class TextureSetEntry : public Entry
	{
	public:
		virtual ~TextureSetEntry();

		virtual void Unk_01(void);
		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void Unk_05(void);
		virtual void Unk_06(void);
	};

};

// 548
class CharacterCreation
{
public:
	UInt64	unk00;		// 00
	void	* unk08;	// 08
	UInt64	unk10;		// 10		4
	UInt64	unk18;		// 18		1
	UInt64	unk20;		// 20
	UInt64	unk28;		// 28
	UInt64	unk30;		// 30
	UInt64	unk38;		// 38
	UInt64	unk40;		// 40
	UInt64	unk48;		// 48
	UInt64	unk50;		// 50
	Actor	* actor;	// 58
	TESNPC	* npc;		// 60
	TESNPC	* npc2;		// 68

	struct TintData
	{
		BSFixedString	category;	// 00
		SInt32			unk08;		// 08
		UInt32			type;		// 0C
		tArray<BGSCharacterTint::Template::Entry*>	entry;		// 10 BGSCharacterTint::Template::Entry
	};

	// 40
	struct RegionData
	{
		BSFixedString	name;	// 00

		// 20
		struct Type
		{
			BSFixedString	name;			// 00
			BSFixedString	type;			// 08
			BGSTextureSet	* textureSet;	// 10
			UInt32			unk18;			// 18
			float			unk1C;			// 1C
		};

		tArray<Type>		types;	// 08
		tArray<float>		unk20;	// 20
		UInt64				unk38;	// 38
	};

	struct Data1
	{
		tArray<TESNPC*>			presets;	// 00
		tArray<BGSHeadPart*>	headParts;	// 18
		tArray<void*>			unk30;		// 30

		struct Details
		{
			BSFixedString	location;	// 00
			struct Data
			{
				BSFixedString	name;	// 00
				BSFixedString	type;	// 08
				BGSTextureSet	* textureSet;	// 10
				UInt32			unk18;
				float			unk1C;
			};
			tArray<Data>	selection;	// 08
		};
		tArray<Details*>		details;	// 48
		tArray<TintData*>		tintData;	// 60
		tArray<BGSTextureSet*>	textures;	// 78
		// ...
	};
	Data1					* unk70;		// 70

	// Used by Scaleform callback to SetHairColor (17)
	tArray<BGSColorForm*>	hairColors;		// 78

	struct Data2
	{
		tArray<BGSTextureSet*>	unk00;	// 00
		tArray<BGSColorForm*>	unk18;	// 18
	};
	Data2					* unk90;		// 90
	UInt64					unk98;			// 98
	UInt64					unkA0;			// A0
	UInt64					unkA8;			// A8
	tArray<BGSHeadPart*>	faces;			// B0
	tArray<BGSHeadPart*>	eyes;			// C8
	tArray<BGSHeadPart*>	hairStyles;		// E0
	tArray<UInt64>			unkF8;			// F8
	UInt64					unk110[(0x350-0x110)/8];	// 110

	BGSCharacterTint::Template::Palette	* skinTint;		// 350 BGSCharacterTint::Template::Entry - Skin Tone?

	// Used by Scaleform callback to SetDetailColor (31)
	tArray<TintData*> tints;										// 358
	tArray<tArray<BGSCharacterTint::Template::Entry*>*>	details;	// 370

	// ...
};

extern RelocPtr <CharacterCreation*> g_characterCreation;

// Texture updating notes
// UInt64 unk2;
// call 140017224(player, &unk2);
// node = player->GetRootNode()
// call 14006CEF4(*146CC4360, actorBase, node, (UInt8)1, (UInt8)0, func_140045241, func_1400A7FC7, unk2, staticTextureIndexedArray);
