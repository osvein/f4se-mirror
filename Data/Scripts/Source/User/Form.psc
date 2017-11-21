Scriptname Form extends ScriptObject Native Hidden

; Returns the formID for this object
Int Function GetFormID() native

; Obtains this form's value in gold. Will return -1 if the form doesn't have any value (like a quest)
int Function GetGoldValue() native

; Returns if this form has the specified keyword attached
bool Function HasKeyword(Keyword akKeyword) native

; Returns if this form has any of the keywords in the list attached
bool Function HasKeywordInFormList(FormList akKeywordList) native

; Is the "Known" flag set for this form?
bool Function PlayerKnows() native

; Turns on profiling for this specific object and all scripts attached to it - setting doesn't persist across saves
; Will do nothing on release console builds, and if the Papyrus:bEnableProfiling ini setting is off
Function StartObjectProfiling() native debugOnly

; Turns off profiling for this specific object and all scripts attached to it - setting doesn't persist across saves
; Will do nothing on release console builds, and if the Papyrus:bEnableProfiling ini setting is off
Function StopObjectProfiling() native debugOnly

; F4SE additions built 2017-11-21 01:02:02.789000 UTC

; returns the form's name, full name if possible
string Function GetName() native

; sets the name of the form
Function SetName(string name) native

; returns the description of the form
string Function GetDescription() native

; returns the weight of the form
float Function GetWeight() native

; sets the weight of the form
Function SetWeight(float weight) native

; sets the gold value of the form
Function SetGoldValue(int value) native

; returns all keywords of the form
Keyword[] Function GetKeywords() native

; Returns whether this Form has a World Model (fast)
bool Function HasWorldModel() native

; Returns the world model path of this Form, if it has a world model
string Function GetWorldModelPath() native
Function SetWorldModelPath(string path) native

; works on the path to the nif file representing the icon for the form in the inventory
string Function GetIconPath() native
Function SetIconPath(string path) native

; works on the path to the file representing the message icon for the form
string Function GetMessageIconPath() native
Function SetMessageIconPath(string path) native

; works on the enchantment associated with the form
Enchantment Function GetEnchantment() native
Function SetEnchantment(Enchantment e) native

; works on the enchantment value of the associated form
int Function GetEnchantmentValue() native
Function SetEnchantmentValue(int value) native

; Returns the particular equipslot type
EquipSlot Function GetEquipType() native
Function SetEquipType(EquipSlot type) native