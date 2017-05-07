#ifndef __F4SE_VERSION_H__
#define __F4SE_VERSION_H__

// these have to be macros so they can be used in the .rc
#define F4SE_VERSION_INTEGER		0
#define F4SE_VERSION_INTEGER_MINOR	1
#define F4SE_VERSION_INTEGER_BETA	4
#define F4SE_VERSION_VERSTRING		"0, 0, 1, 4"
#define F4SE_VERSION_PADDEDSTRING	"0001"
#define F4SE_VERSION_RELEASEIDX		1

#define MAKE_EXE_VERSION_EX(major, minor, build, sub)	(((major & 0xFF) << 24) | ((minor & 0xFF) << 16) | ((build & 0xFFF) << 4) | (sub & 0xF))
#define MAKE_EXE_VERSION(major, minor, build)			MAKE_EXE_VERSION_EX(major, minor, build, 0)

#define RUNTIME_VERSION_1_1_29	MAKE_EXE_VERSION(1, 1, 29)	// 0x010101D0	initial version released on steam
#define RUNTIME_VERSION_1_1_30	MAKE_EXE_VERSION(1, 1, 30)	// 0x010101E0	day1 patch to fix xaudio problem
#define RUNTIME_VERSION_1_2		MAKE_EXE_VERSION(1, 2, 33)	// 0x01020210	beta, removed mini-mod-manager from the launcher
#define RUNTIME_VERSION_1_2_37	MAKE_EXE_VERSION(1, 2, 37)	// 0x01020250	beta - unclear
#define RUNTIME_VERSION_1_3_45	MAKE_EXE_VERSION(1, 3, 45)	// 0x010302D0	beta - compiled with optimization enabled (finally), added hbao+ and cuda-based impact particles (shame)

#define PACKED_F4SE_VERSION		MAKE_EXE_VERSION(F4SE_VERSION_INTEGER, F4SE_VERSION_INTEGER_MINOR, F4SE_VERSION_INTEGER_BETA)

#endif /* __F4SE_VERSION_H__ */
