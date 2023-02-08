#pragma once

#ifdef NTSCJ

/* init */
#define tww_memcpy_addr 0x80003490

/* MSL_C */
#define tww_strlen_addr 0x8032b798
#define tww_printf_addr 0x803295ac
#define tww_sprintf_addr 0x80329308
#define tww_snprintf_addr 0x803293e8
#define tww_strcat_addr 0x8032b670
#define tww_strncpy_addr 0x8032b69c
#define tww_strcpy_addr 0x8032b6e0
#define tww_strcmp_addr 0x8032b548

#define tww_atan_addr 0x8032def8
#define tww_copysign_addr 0x8032e0f8
#define tww_cos_addr 0x8032e120
#define tww_floor_addr 0x8032e1f4
#define tww_frexp_addr 0x8032e33c
#define tww_ldexp_addr 0x8032e3c8
#define tww_sin_addr 0x8032e688
#define tww_tan_addr 0x8032e760
#define tww_acos_addr 0x8032e7d8
#define tww_asin_addr 0x8032e7f8
#define tww_atan2_addr 0x8032e818
#define tww_fmod_addr 0x8032e838

/* pad */
#define tww_PADRead_addr 0x80313768

/* gx */
#define GXSetBlendMode_addr 0x8032425c
#define GXBegin_addr 0x80320e0c
#define GXSetVtxAttrFmt_addr 0x8031f850
#define GXLoadPosMtxImm_addr 0x8032493c
#define GXSetNumIndStages_addr 0x80323604
#define GXSetTevDirect_addr 0x8032362c
#define GXSetAlphaCompare_addr 0x80323ccc
#define GXSetZMode_addr 0x80324308
#define GXSetTevOp_addr 0x803237c8
#define GXSetNumChans_addr 0x80321ff8
#define GXSetNumTevStages_addr 0x80323f7c
#define GXSetNumTexGens_addr 0x8032061c
#define GXSetTevOrder_addr 0x80323da4
#define GXSetTevColorIn_addr 0x80323854
#define GXSetTevAlphaIn_addr 0x80323898
#define GXSetTevColorOp_addr 0x803238dc
#define GXSetTevAlphaOp_addr 0x80323944
#define GXSetCullMode_addr 0x80321070
#define GXLoadTexMtxImm_addr 0x80324a14
#define GXSetChanCtrl_addr 0x8032203c
#define GXSetCurrentMtx_addr 0x803249dc
#define GXSetTexCoordGen2_addr 0x8032034c
#define GXSetLineWidth_addr 0x80320f84
#define GXClearVtxDesc_addr 0x8031f818
#define GXSetVtxDesc_addr 0x8031f350
#define GXFlush_addr 0x803206c8
#define GXInitTexObj_addr 0x8032232c
#define GXLoadTexObj_addr 0x80322968
#define GXInvalidateTexAll_addr 0x80322c08
#define GXSetProjection_addr 0x80324768
#define GXSetScissor_addr 0x80324c28
#define GXGetScissor_addr 0x80324cb8
#define wgPipe_addr 0xCC008000

/* c_malloc */
#define tww_free_addr 0x8023eac0
#define tww_memalign_addr 0x8023ea88

/* c_lib */
#define tww_memset_addr 0x80250054

/* c_dylink */
#define tww_cDyl_InitAsync_addr 0x80022a88

/* c_counter */
#define g_Counter_addr 0x803db620

/* JUTConsole */
#define tww_draw_console_addr 0x802c8278

/* JUTGamePad */
#define tww_mPadStatus_addr 0x803e0cf8
#define tww_mPadButton_addr 0x803e0d28
#define tww_mPadMStick_addr 0x803e0de8
#define tww_mPadSStick_addr 0x803e0e28

/* f_ap_game */
#define tww_fapGm_Execute_addr 0x80022e74

/* f_op_scene_req */
#define l_fopScnRq_IsUsingOfOverlap_addr 0x803e9ec0

/* f_op_scene_mng */
#define fopScnM_ChangeReq_addr 0x80029afc

/* m_Do_controller_pad */
#define g_mDoCPd_cpadInfo_addr 0x80398308

/* m_Do_main */
#define mDoMain__developmentMode_addr 0x803e95c0

/* d_kankyo */
#define g_env_light_addr 0x803d7fa4

/* d_com_inf_game */
#define g_dComIfG_gameInfo_addr 0x803b8108
#define tww_dComIfGs_setGameStartStage_addr 0x80053054

/* d_save */
#define dSv_player_return_place_c__set_addr 0x800569c0

/* d_stage */
#define dStage_roomControl_c__mStayNo_addr 0x803e9f48

/* d_s_play */
#define tww_dScnPly_Draw_addr 0x8023218c

/* d_a_player */
#define l_debug_keep_pos_addr 0x803d78fc
#define l_debug_current_angle_addr 0x803ea3c8
#define l_debug_shape_angle_addr 0x803ea3d0

#endif

#ifdef NTSCU

/* init */
#define tww_memcpy_addr 0x80003490

/* MSL_C */
#define tww_strlen_addr 0x8032dd94
#define tww_printf_addr 0x8032bba8
#define tww_sprintf_addr 0x8032b904
#define tww_snprintf_addr 0x8032b9e4
#define tww_strcat_addr 0x8032dc6c
#define tww_strncpy_addr 0x8032dc98
#define tww_strcpy_addr 0x8032dcdc
#define tww_strcmp_addr 0x8032db44

#define tww_atan_addr 0x803304f4
#define tww_copysign_addr 0x803306f4
#define tww_cos_addr 0x8033071c
#define tww_floor_addr 0x803307f0
#define tww_frexp_addr 0x80330938
#define tww_ldexp_addr 0x803309c4
#define tww_sin_addr 0x80330c84
#define tww_tan_addr 0x80330d5c
#define tww_acos_addr 0x80330dd4
#define tww_asin_addr 0x80330df4
#define tww_atan2_addr 0x80330e14
#define tww_fmod_addr 0x80330e34

/* pad */
#define tww_PADRead_addr 0x80315a20

/* gx */
#define GXSetBlendMode_addr 0x80326858
#define GXBegin_addr 0x803230c4
#define GXSetVtxAttrFmt_addr 0x80321b08
#define GXLoadPosMtxImm_addr 0x80326f38
#define GXSetNumIndStages_addr 0x80325c00
#define GXSetTevDirect_addr 0x80325c28
#define GXSetAlphaCompare_addr 0x803262c8
#define GXSetZMode_addr 0x80326904
#define GXSetTevOp_addr 0x80325dc4
#define GXSetNumChans_addr 0x80324578
#define GXSetNumTevStages_addr 0x80326578
#define GXSetNumTexGens_addr 0x803228d4
#define GXSetTevOrder_addr 0x803263a0
#define GXSetTevColorIn_addr 0x80325e50
#define GXSetTevAlphaIn_addr 0x80325e94
#define GXSetTevColorOp_addr 0x80325ed8
#define GXSetTevAlphaOp_addr 0x80325f40
#define GXSetCullMode_addr 0x80323328
#define GXLoadTexMtxImm_addr 0x80327010
#define GXSetChanCtrl_addr 0x803245bc
#define GXSetCurrentMtx_addr 0x80326fd8
#define GXSetTexCoordGen2_addr 0x80322604
#define GXSetLineWidth_addr 0x8032323c
#define GXClearVtxDesc_addr 0x80321ad0
#define GXSetVtxDesc_addr 0x80321608
#define GXFlush_addr 0x80322980
#define GXInitTexObj_addr 0x803248ac
#define GXLoadTexObj_addr 0x80324ee8
#define GXInvalidateTexAll_addr 0x80325188
#define GXSetProjection_addr 0x80326d64
#define GXSetScissor_addr 0x80327224
#define GXGetScissor_addr 0x803272b4
#define wgPipe_addr 0xCC008000

/* c_malloc */
#define tww_free_addr 0x80241330
#define tww_memalign_addr 0x802412f8

/* c_lib */
#define tww_memset_addr 0x802528c4

/* c_dylink */
#define tww_cDyl_InitAsync_addr 0x80022df8

/* c_counter */
#define g_Counter_addr 0x803e8140

/* JUTConsole */
#define tww_draw_console_addr 0x802cac18

/* JUTGamePad */
#define tww_mPadStatus_addr 0x803ed818
#define tww_mPadButton_addr 0x803ed848
#define tww_mPadMStick_addr 0x803ed908
#define tww_mPadSStick_addr 0x803ed948

/* f_ap_game */
#define tww_fapGm_Execute_addr 0x800231e4

/* f_op_scene_req */
#define l_fopScnRq_IsUsingOfOverlap_addr 0x803f69e0

/* f_op_scene_mng */
#define fopScnM_ChangeReq_addr 0x80029e6c

/* m_Do_controller_pad */
#define g_mDoCPd_cpadInfo_addr 0x803a4df0

/* m_Do_main */
#define mDoMain__developmentMode_addr 0x803f60e0

/* d_kankyo */
#define g_env_light_addr 0x803e4ab4

/* d_com_inf_game */
#define g_dComIfG_gameInfo_addr 0x803c4c08
#define tww_dComIfGs_setGameStartStage_addr 0x800548fc

/* d_save */
#define dSv_player_return_place_c__set_addr 0x80058bc8

/* d_stage */
#define dStage_roomControl_c__mStayNo_addr 0x803f6a78

/* d_s_play */
#define tww_dScnPly_Draw_addr 0x80234b9c

/* d_a_player */
#define l_debug_keep_pos_addr 0x803e440c
#define l_debug_current_angle_addr 0x803f6f10
#define l_debug_shape_angle_addr 0x803f6f18

#endif