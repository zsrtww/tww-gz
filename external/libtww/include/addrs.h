#pragma once

#ifdef NTSCJ

/* init */
#define tww_memcpy_addr 0x80003490
#define tww_getSave_addr 0x8005b6e8
#define tww_putSave_addr 0x8005b7a8
#define tww_drawScreenPlayer_addr 0x80232de0
#define tww_getLayerNo_addr 0x80050960
#define tww_os_report_addr 0x800068ec

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

/* c_xyz */
#define cXyz__operator_pl_addr 0x80242e04
#define cXyz__operator_mi_addr 0x80242e54
#define cXyz__operator_ml_addr 0x80242ea4
#define cXyz__operator_ml2_addr 0x80242ef0
#define cXyz__operator_dv_addr 0x80242f38

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
#define dKy_getdaytime_minute_addr 0x8018d584
#define dKy_getdaytime_hour_addr 0x8018d558
#define dKy_moon_type_chk_addr 0x80193cb4  

/* d_com_inf_game */
#define g_dComIfG_gameInfo_addr 0x803b8108
#define tww_dComIfGs_setGameStartStage_addr 0x80053054
#define dComIfGs_setSelectEquip_addr 0x80053fbc

/* d_save */
#define dSv_player_return_place_c__set_addr 0x800569c0
#define dSv_event_c__isEventBit_addr 0x8005a954
#define dSv_event_c__onEventBit_addr 0x8005a924
#define dSv_event_c__offEventBit_addr 0x8005a93c
#define onDungeonItem__12dSv_memBit_cFi_addr 0x8005a5c4
#define isDungeonItem__12dSv_memBit_cFi_addr 0x8005a664
#define getSave__10dSv_info_cFi_addr 0x8005b6e8
#define dSv_player_bag_item_c__setBeastItem_addr 0x80057760
#define dSv_player_bag_item_c__setBaitItem_addr 0x80058040
#define dSv_player_map_c__isGetMap_addr 0x800591c4
#define dSv_player_map_c__onGetMap_addr 0x80059118
#define dSv_event_c__setEventReg_addr 0x8005a978
#define dSv_event_c__getEventReg_addr 0x8005a99c
#define dSv_player_collect_c__getTriforceNum_addr 0x80059028
#define dSv_memBit_c__isTbox_addr 0x80059fa8
#define dSv_memBit_c__onTbox_addr 0x80059f0c
#define dSv_memBit_c__isSwitch_addr 0x8005a1a0
#define dSv_memBit_c__onSwitch_addr 0x8005a048
#define dSv_memBit_c__offSwitch_addr 0x8005a0f4
#define dSv_memBit_c__onDungeonItem_addr 0x8005a5c4
#define dSv_memBit_c__isDungeonItem_addr 0x8005a664
#define dSv_player_collect_c__isCollect_addr 0x80058c08
#define dSv_player_collect_c__onCollect_addr 0x80058ad8
#define dSv_player_collect_c__offCollect_addr 0x80058b70
#define dSv_player_collect_c__isTact_addr 0x80058d38
#define dSv_player_collect_c__onTact_addr 0x80058ca4
#define dSv_player_collect_c__isTriforce_addr 0x80058e64
#define dSv_player_collect_c__onTriforce_addr 0x80058dd0
#define dSv_player_collect_c__isSymbol_addr 0x80058f90
#define dSv_player_collect_c__onSymbol_addr 0x80058efc
#define dSv_info_c__onSwitch_addr 0x8005b944
#define dSv_info_c__offSwitch_addr 0x8005bb0c
#define dSv_info_c__isSwitch_addr 0x8005bcb8
#define dSv_info_c__revSwitch_addr 0x8005be00
#define dSv_info_c__onItem_addr 0x8005bfb0
#define dSv_info_c__isItem_addr 0x8005c144
#define dSv_player_get_item_c__onItem_addr 0x800572bc
#define dSv_player_get_item_c__isItem_addr 0x80057354
#define dSv_player_get_bag_item_c__onBeast_addr 0x800586c4
#define dSv_player_get_bag_item_c__isBeast_addr 0x80058758
#define dSv_player_get_bag_item_c__onBait_addr 0x800587f0
#define dSv_player_get_bag_item_c__isBait_addr 0x80058884

/* d_stage */
#define dStage_roomControl_c__mStayNo_addr 0x803e9f48
#define dStage_roomControl_c__m_time_pass_addr 0x803e9f54

/* d_s_play */
#define tww_dScnPly_Draw_addr 0x8023218c

/* d_a_player */
#define l_debug_keep_pos_addr 0x803d78fc
#define l_debug_current_angle_addr 0x803ea3c8
#define l_debug_shape_angle_addr 0x803ea3d0

/* d_com_static */
#define daArrow_c__m_keep_type_addr 0x803ea04c

#endif

#ifdef NTSCU

/* init */
#define tww_memcpy_addr 0x80003490
#define tww_getSave_addr 0x8005d8c8
#define tww_putSave_addr 0x8005d988
#define tww_drawScreenPlayer_addr 0x802357f4
#define tww_getLayerNo_addr 0x80052400
#define tww_os_report_addr 0x80006950

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

/* c_xyz */
#define cXyz__operator_pl_addr 0x80245674
#define cXyz__operator_mi_addr 0x802456c4
#define cXyz__operator_ml_addr 0x80245714
#define cXyz__operator_ml2_addr 0x80245760
#define cXyz__operator_dv_addr 0x802457a8

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
#define dKy_getdaytime_minute_addr 0x80190c40
#define dKy_getdaytime_hour_addr 0x80190c14
#define dKy_moon_type_chk_addr 0x801973b8 

/* d_com_inf_game */
#define g_dComIfG_gameInfo_addr 0x803c4c08
#define tww_dComIfGs_setGameStartStage_addr 0x800548fc
#define dComIfGs_setSelectEquip_addr 0x8005586c

/* d_save */
#define dSv_player_return_place_c__set_addr 0x80058bc8
#define dSv_event_c__isEventBit_addr 0x8005cb34
#define dSv_event_c__onEventBit_addr 0x8005cb04
#define dSv_event_c__offEventBit_addr 0x8005cb1c
#define onDungeonItem__12dSv_memBit_cFi_addr 0x8005c7a4
#define isDungeonItem__12dSv_memBit_cFi_addr 0x8005c844
#define getSave__10dSv_info_cFi_addr 0x8005d8c8
#define dSv_player_bag_item_c__setBeastItem_addr 0x80059968
#define dSv_player_bag_item_c__setBaitItem_addr 0x8005a248
#define dSv_player_map_c__isGetMap_addr 0x8005b3cc
#define dSv_player_map_c__onGetMap_addr 0x8005b320
#define dSv_event_c__setEventReg_addr 0x8005cb58
#define dSv_event_c__getEventReg_addr 0x8005cb7c
#define dSv_player_collect_c__getTriforceNum_addr 0x8005b230
#define dSv_memBit_c__isTbox_addr 0x8005c188
#define dSv_memBit_c__onTbox_addr 0x8005c0ec
#define dSv_memBit_c__isSwitch_addr 0x8005c380
#define dSv_memBit_c__onSwitch_addr 0x8005c228
#define dSv_memBit_c__offSwitch_addr 0x8005c2d4
#define dSv_memBit_c__onDungeonItem_addr 0x8005c7a4
#define dSv_memBit_c__isDungeonItem_addr 0x8005c844
#define dSv_player_collect_c__isCollect_addr 0x8005ae10
#define dSv_player_collect_c__onCollect_addr 0x8005ace0
#define dSv_player_collect_c__offCollect_addr 0x8005ad78
#define dSv_player_collect_c__isTact_addr 0x8005af40
#define dSv_player_collect_c__onTact_addr 0x8005aeac
#define dSv_player_collect_c__isTriforce_addr 0x8005b06c
#define dSv_player_collect_c__onTriforce_addr 0x8005afd8
#define dSv_player_collect_c__isSymbol_addr 0x8005b198
#define dSv_player_collect_c__onSymbol_addr 0x8005b104
#define dSv_info_c__onSwitch_addr 0x8005db24
#define dSv_info_c__offSwitch_addr 0x8005dcec
#define dSv_info_c__isSwitch_addr 0x8005de98
#define dSv_info_c__revSwitch_addr 0x8005dfe0
#define dSv_info_c__onItem_addr 0x8005e190
#define dSv_info_c__isItem_addr 0x8005e324
#define dSv_player_get_item_c__onItem_addr 0x800594c4
#define dSv_player_get_item_c__isItem_addr 0x8005955c
#define dSv_player_get_bag_item_c__onBeast_addr 0x8005a8cc
#define dSv_player_get_bag_item_c__isBeast_addr 0x8005a960
#define dSv_player_get_bag_item_c__onBait_addr 0x8005a9f8
#define dSv_player_get_bag_item_c__isBait_addr 0x8005aa8c

/* d_stage */
#define dStage_roomControl_c__mStayNo_addr 0x803f6a78
#define dStage_roomControl_c__m_time_pass_addr 0x803f6a84

/* d_s_play */
#define tww_dScnPly_Draw_addr 0x80234b9c

/* d_a_player */
#define l_debug_keep_pos_addr 0x803e440c
#define l_debug_current_angle_addr 0x803f6f10
#define l_debug_shape_angle_addr 0x803f6f18
#define daArrow_c__m_keep_type_addr 0x803f6b7c

#endif

#ifdef PAL

/* init */
#define tww_memcpy_addr 0x80003490
#define tww_getSave_addr 0x800616a8
#define tww_putSave_addr 0x80061768
#define tww_drawScreenPlayer_addr 0x8023a87c
#define tww_getLayerNo_addr 0x800561e0
#define tww_os_report_addr 0x80006950

/* MSL_C */
#define tww_strlen_addr 0x803332ec
#define tww_printf_addr 0x80331100
#define tww_sprintf_addr 0x80330e5c
#define tww_snprintf_addr 0x80330f3c
#define tww_strcat_addr 0x803331c4
#define tww_strncpy_addr 0x8033305c
#define tww_strcpy_addr 0x80333234
#define tww_strcmp_addr 0x8033309c

#define tww_atan_addr 0x80335a4c
#define tww_copysign_addr 0x80335c4c
#define tww_cos_addr 0x80335c74
#define tww_floor_addr 0x80335d48
#define tww_frexp_addr 0x80335e90
#define tww_ldexp_addr 0x80335f1c
#define tww_sin_addr 0x803361dc
#define tww_tan_addr 0x803362b4
#define tww_acos_addr 0x8033632c
#define tww_asin_addr 0x8033634c
#define tww_atan2_addr 0x8033636c
#define tww_fmod_addr 0x8033638c

/* pad */
#define tww_PADRead_addr 0x8031af78

/* gx */
#define GXSetBlendMode_addr 0x8032bdb0
#define GXBegin_addr 0x8032861c
#define GXSetVtxAttrFmt_addr 0x80327060
#define GXLoadPosMtxImm_addr 0x8032c490
#define GXSetNumIndStages_addr 0x8032b158
#define GXSetTevDirect_addr 0x8032b180
#define GXSetAlphaCompare_addr 0x8032b820
#define GXSetZMode_addr 0x8032be5c
#define GXSetTevOp_addr 0x8032b31c
#define GXSetNumChans_addr 0x80329ad0
#define GXSetNumTevStages_addr 0x8032bad0
#define GXSetNumTexGens_addr 0x80327e2c
#define GXSetTevOrder_addr 0x8032b8f8
#define GXSetTevColorIn_addr 0x8032b3a8
#define GXSetTevAlphaIn_addr 0x8032b3ec
#define GXSetTevColorOp_addr 0x8032b430
#define GXSetTevAlphaOp_addr 0x8032b498
#define GXSetCullMode_addr 0x80328880
#define GXLoadTexMtxImm_addr 0x8032c568
#define GXSetChanCtrl_addr 0x80329b14
#define GXSetCurrentMtx_addr 0x8032c530
#define GXSetTexCoordGen2_addr 0x80327b5c
#define GXSetLineWidth_addr 0x80328794
#define GXClearVtxDesc_addr 0x80327028
#define GXSetVtxDesc_addr 0x80326b60
#define GXFlush_addr 0x80327ed8
#define GXInitTexObj_addr 0x80329e04
#define GXLoadTexObj_addr 0x8032a440
#define GXInvalidateTexAll_addr 0x8032a6e0
#define GXSetProjection_addr 0x8032c2bc
#define GXSetScissor_addr 0x8032c77c
#define GXGetScissor_addr 0x8032c80c
#define wgPipe_addr 0xCC008000

/* c_malloc */
#define tww_free_addr 0x802464d0
#define tww_memalign_addr 0x80246498

/* c_lib */
#define tww_memset_addr 0x80257a64

/* c_dylink */
#define tww_cDyl_InitAsync_addr 0x80023148

/* c_counter */
#define g_Counter_addr 0x803ef940

/* c_xyz */
#define cXyz__operator_pl_addr 0x8024a814
#define cXyz__operator_mi_addr 0x8024a864
#define cXyz__operator_ml_addr 0x8024a8b4
#define cXyz__operator_ml2_addr 0x8024a900
#define cXyz__operator_dv_addr 0x8024a948

/* JUTConsole */
#define tww_draw_console_addr 0x802cfdb8

/* JUTGamePad */
#define tww_mPadStatus_addr 0x803f5018
#define tww_mPadButton_addr 0x803f5048
#define tww_mPadMStick_addr 0x803f5108
#define tww_mPadSStick_addr 0x803f5148

/* f_ap_game */
#define tww_fapGm_Execute_addr 0x80023534

/* f_op_scene_req */
#define l_fopScnRq_IsUsingOfOverlap_addr 0x803fe1e0

/* f_op_scene_mng */
#define fopScnM_ChangeReq_addr 0x8002a1bc

/* m_Do_controller_pad */
#define g_mDoCPd_cpadInfo_addr 0x803abaf0

/* m_Do_main */
#define mDoMain__developmentMode_addr 0x803fd8e0

/* d_kankyo */
#define g_env_light_addr 0x803ec3fc
#define dKy_getdaytime_minute_addr 0x80197164
#define dKy_getdaytime_hour_addr 0x80197138
#define dKy_moon_type_chk_addr 0x8019d8dc

/* d_com_inf_game */
#define g_dComIfG_gameInfo_addr 0x803cc530
#define tww_dComIfGs_setGameStartStage_addr 0x800586dc
#define dComIfGs_setSelectEquip_addr 0x8005964c

/* d_save */
#define dSv_player_return_place_c__set_addr 0x8005c9a8
#define dSv_event_c__isEventBit_addr 0x80060914
#define dSv_event_c__onEventBit_addr 0x800608e4
#define dSv_event_c__offEventBit_addr 0x800608fc
#define onDungeonItem__12dSv_memBit_cFi_addr 0x80060584
#define isDungeonItem__12dSv_memBit_cFi_addr 0x80060624
#define getSave__10dSv_info_cFi_addr 0x800616a8
#define dSv_player_bag_item_c__setBeastItem_addr 0x8005d748
#define dSv_player_bag_item_c__setBaitItem_addr 0x8005e028
#define dSv_player_map_c__isGetMap_addr 0x8005f1ac
#define dSv_player_map_c__onGetMap_addr 0x8005f100
#define dSv_event_c__setEventReg_addr 0x80060938
#define dSv_event_c__getEventReg_addr 0x8006095c
#define dSv_player_collect_c__getTriforceNum_addr 0x8005f010
#define dSv_memBit_c__isTbox_addr 0x8005ff68
#define dSv_memBit_c__onTbox_addr 0x8005fecc
#define dSv_memBit_c__isSwitch_addr 0x80060160
#define dSv_memBit_c__onSwitch_addr 0x80060008
#define dSv_memBit_c__offSwitch_addr 0x800600b4
#define dSv_memBit_c__onDungeonItem_addr 0x80060584
#define dSv_memBit_c__isDungeonItem_addr 0x80060624
#define dSv_player_collect_c__isCollect_addr 0x8005ebf0
#define dSv_player_collect_c__onCollect_addr 0x8005eac0
#define dSv_player_collect_c__offCollect_addr 0x8005eb58
#define dSv_player_collect_c__isTact_addr 0x8005ed20
#define dSv_player_collect_c__onTact_addr 0x8005ec8c
#define dSv_player_collect_c__isTriforce_addr 0x8005ee4c
#define dSv_player_collect_c__onTriforce_addr 0x8005edb8
#define dSv_player_collect_c__isSymbol_addr 0x8005ef78
#define dSv_player_collect_c__onSymbol_addr 0x8005eee4
#define dSv_info_c__onSwitch_addr 0x80061904
#define dSv_info_c__offSwitch_addr 0x80061acc
#define dSv_info_c__isSwitch_addr 0x80061c78
#define dSv_info_c__revSwitch_addr 0x80061dc0
#define dSv_info_c__onItem_addr 0x80061f70
#define dSv_info_c__isItem_addr 0x80062104
#define dSv_player_get_item_c__onItem_addr 0x8005d2a4
#define dSv_player_get_item_c__isItem_addr 0x8005d33c
#define dSv_player_get_bag_item_c__onBeast_addr 0x8005e6ac
#define dSv_player_get_bag_item_c__isBeast_addr 0x8005e740
#define dSv_player_get_bag_item_c__onBait_addr 0x8005e7d8
#define dSv_player_get_bag_item_c__isBait_addr 0x8005e86c

/* d_stage */
#define dStage_roomControl_c__mStayNo_addr 0x803fe278
#define dStage_roomControl_c__m_time_pass_addr 0x803fe284

/* d_s_play */
#define tww_dScnPly_Draw_addr 0x80239c24

/* d_a_player */
#define l_debug_keep_pos_addr 0x803ebd34
#define l_debug_current_angle_addr 0x803fe710
#define l_debug_shape_angle_addr 0x803fe718
#define daArrow_c__m_keep_type_addr 0x803fe37c

#endif