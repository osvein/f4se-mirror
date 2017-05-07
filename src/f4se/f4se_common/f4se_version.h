#ifndef __F4SE_VERSION_H__
#define __F4SE_VERSION_H__

// these have to be macros so they can be used in the .rc
#define F4SE_VERSION_INTEGER		0
#define F4SE_VERSION_INTEGER_MINOR	1
#define F4SE_VERSION_INTEGER_BETA	1
#define F4SE_VERSION_VERSTRING		"0, 0, 1, 1"
#define F4SE_VERSION_PADDEDSTRING	"0001"
#define F4SE_VERSION_RELEASEIDX		1

#define MAKE_EXE_VERSION_EX(major, minor, build, sub)	(((major & 0xFF) << 24) | ((minor & 0xFF) << 16) | ((build & 0xFFF) << 4) | (sub & 0xF))
#define MAKE_EXE_VERSION(major, minor, build)			MAKE_EXE_VERSION_EX(major, minor, build, 0)

#define RUNTIME_VERSION_1_1_29	MAKE_EXE_VERSION(1, 1, 29)	// 0x010101D0	initial version released on steam
#define RUNTIME_VERSION_1_1_30	MAKE_EXE_VERSION(1, 1, 30)	// 0x010101E0	beta
#define RUNTIME_VERSION_1_2		MAKE_EXE_VERSION(1, 2, 0)	// 0x01020000	beta - not sure what build number it'll be yet

#define PACKED_F4SE_VERSION		MAKE_EXE_VERSION(F4SE_VERSION_INTEGER, F4SE_VERSION_INTEGER_MINOR, F4SE_VERSION_INTEGER_BETA)

#endif /* __F4SE_VERSION_H__ */
