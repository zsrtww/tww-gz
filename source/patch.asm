; You can use this to patch the game's code to call into the Rom Hack's code
; Resize ArenaLo in OSInit
0x802ff5d4:
u32 0x3c608045 ; lis r3, 0x8045 (Use 804504A0 as ArenaLow)

; replace cDyl_InitAsync call in main01 with our init function
0x800063ec:
bl init

; replace fapGm_Execute call in main01 with our game_loop
; replace mfspr r0, LR in cDyl_InitAsyncIsDone with fapGm_Execute call
0x80006458:
bl game_loop 
bl 0x80022e74 ; fapGm_Execute
