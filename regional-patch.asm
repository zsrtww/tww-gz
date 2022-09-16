; You can use this to patch the game's code to call into the Rom Hack's code
; Resize ArenaLo in OSInit
0x802ff5d4:
u32 0x3c608045 ; lis r3, 0x8045 (Use 804504A0 as ArenaLow)

; replace fapGm_Execute call in main01 with our lib hooks
0x80006338:
b apply_lib_hooks 

; This is an unused section of the dol that we use to store the trampoline for the main function
0x80336068:
u32 0x9421fff0
u32 0x4bcd02d0