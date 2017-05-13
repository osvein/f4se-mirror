#include "f4se/GameForms.h"
#include "f4se/GameUtilities.h"

RelocAddr <_LookupFormByID> LookupFormByID(0x00151610);

// 19AD05F2961D07B65E7987D210D6A47199FC0EFA+21
RelocPtr <IFormFactory*> g_formFactoryList(0x0585F640);

RelocPtr <tHashSet<ObjectModMiscPair, BGSMod::Attachment::Mod*>> g_modAttachmentMap(0x03673100);