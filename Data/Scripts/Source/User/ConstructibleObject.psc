Scriptname ConstructibleObject extends MiscObject Native Hidden

; F4SE additions built 2019-03-14 04:47:05.463000 UTC
struct ConstructibleComponent
	Component object
	int count
endStruct

ConstructibleComponent[] Function GetConstructibleComponents() native

Function SetConstructibleComponents(ConstructibleComponent[] components) native

Form Function GetCreatedObject() native

Function SetCreatedObject(Form akForm) native

int Function GetCreatedCount() native

Function SetCreatedCount(int count) native

int Function GetPriority() native

Function SetPriority(int priority) native

Keyword Function GetWorkbenchKeyword() native

Function SetWorkbenchKeyword(Keyword akKeyword) native