Scriptname UI Native Hidden

; Sets a variable in AS3 to the newly assigned type
; Can accept arrays using VarArrayToVar
bool Function Set(string menu, string path, Var arg) native global

; Returns a variable from AS3 to Papyrus
; Can return arrays using VarToVarArray
Var Function Get(string menu, string path) native global

; Top-level arguments are converted to their actual types, empty Vars are undefined
; Vars, Structs, and Forms are converted to AS3 objects
; Var example:
; {"__var__": 1.0}
; Struct Example:
; {"__struct__": {"__type__": "scriptowner#mystruct", "__data__": {"member1": 1.0, "member2": false}}}
; Form Example:
; {"__type__": "ScriptObject", "__handleHigh__": 0xFFFFFFFF, "__handleLow__": 0x00000000}
; Forms shouldn't be manipulated from AS3, they are container objects meant to be passed back from AS3 to Papyrus
Var Function Invoke(string menu, string path, Var[] args = None) native global


;; Array of Arrays
;; example:
; Var[] a = new Var[3]
; a[0] = 1.0
; a[1] = "Str1"
; Var[] b = new Var[2]
; b[0] = Game.GetForm(0xF)
; b[1] = Game.GetForm(0x7)
; a[2] = Utility.VarArrayToVar(b)
; UI.Invoke("HUDMenu", "root.func", a)
;; AS3 expansion becomes:
;; func(Number=1.0, String="Str1", Array=[{"__type__": "MiscObject", "__handleHigh__": 0xFFFFFFFF, "__handleLow__": 0x0000000F}, {"__type__": "ActorBase", "__handleHigh__": 0xFFFFFFFF, "__handleLow__": 0x00000007}])

;; Scaleform to Papyrus
;; Top-level parameters are expanded directly as parameters

;; Scaleform Code:
; root.f4se.SendExternalEvent("myeventname", Number=1.0, String="Str1", Array=[{"__type__": "MiscObject", "__handleHigh__": 0xFFFFFFFF, "__handleLow__": 0x0000000F}, {"__type__": "ActorBase", "__handleHigh__": 0xFFFFFFFF, "__handleLow__": 0x00000007}])

;; Papyrus code:
;; Must have previously registered for the event and established a callback name
; RegisterForExternalEvent("myeventname", "OnMyCallback")
;
; Event OnMyCallback(float a1, string a2, Var[] a3)
;     MiscObject myMisc = a3[0] as MiscObject ; Cast as it is currently a Var
;     ActorBase myABase = a3[1] as ActorBase
; EndEvent