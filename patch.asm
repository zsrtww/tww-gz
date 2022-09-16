; You can use this to patch the game's code to call into the Rom Hack's code
; Resize ArenaLo in OSInit
@arenaLo:
u32 @arenaLoVal ; lis r3, 0x8045 (Use 804504A0 as ArenaLow)

; replace fapGm_Execute call in main01 with our lib hooks
@main:
b apply_lib_hooks 

; This is an unused section of the dol that we use to store the trampoline for the main function
@mainTrampoline:
u32 @firstInstruction
u32 @returnMn