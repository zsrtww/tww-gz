#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef int (*_strcmp)(const char* str1, const char* str2);

#ifdef NTSCJ

#define tww_strlen ((_strlen)0x8032b798)
#define tww_printf ((_printf)0x803295ac)
#define tww_sprintf ((_sprintf)0x80329308)
#define tww_snprintf ((_snprintf)0x803293e8)
#define tww_strcat ((_strcat)0x8032b670)
#define tww_strncpy ((_strncpy)0x8032b69c)
#define tww_strcpy ((_strcpy)0x8032b6e0)
#define tww_strcmp ((_strcmp)0x8032b548)
#define tww_free_addr 0x8023eac0
#define tww_memset_addr 0x80250054
#define tww_memalign_addr 0x8023ea88
#define tww_memcpy_addr 0x80003490
#define tww_draw_console_addr 0x802c8278
#define tww_cDyl_InitAsync_addr 0x80022a88
#define tww_fapGm_Execute_addr 0x80022e74

typedef char (*_strcpy)(char *dest, const char *source);
typedef char (*_strcat)(char *dst, const char *src);
typedef size_t (*_strlen)(const char *str);
typedef int (*_sprintf)(char *str, const char *string, ...);
typedef int (*_printf)(const char *string, ...);
typedef int (*_snprintf)(char *s, size_t n, const char *format, ...);
typedef char (*_strncpy) (char *destination, const char *source, size_t num);
typedef void (*tww_free_t)(void* memory);
#define tww_free ((tww_free_t)tww_free_addr)

typedef void (*tww_memset_t)(void* addr, int value, uint32_t size);
#define tww_memset ((tww_memset_t)tww_memset_addr)

typedef void* (*tww_memalign_t)(int32_t align, uint32_t size);
#define tww_memalign ((tww_memalign_t)tww_memalign_addr)

typedef void* (*tww_memcpy_t)(void* dest, void* src, size_t size);
#define tww_memcpy ((tww_memcpy_t)tww_memcpy_addr)


#define tww_mPadStatus_addr 0x803e0cf8
#define tww_mPadButton_addr 0x803e0d28
#define tww_mPadMStick_addr 0x803e0de8
#define tww_mPadSStick_addr 0x803e0e28
#define g_mDoCPd_cpadInfo_addr 0x80398308

#define tww_PADRead_addr 0x80313768

#define g_Counter_addr 0x803db620

#define l_fopScnRq_IsUsingOfOverlap_addr 0x803e9ec0
#define l_fopScnRq_IsUsingOfOverlap (*(int*)l_fopScnRq_IsUsingOfOverlap_addr)

#define g_env_light_addr 0x803d7fa4

#define g_dComIfG_gameInfo_addr 0x803b8108

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

#endif

#ifdef NTSCU

#define tww_strlen ((_strlen)0x8032dd94)
#define tww_printf ((_printf)0x8032bba8)
#define tww_sprintf ((_sprintf)0x8032b904)
#define tww_snprintf ((_snprintf)0x8032b9e4)
#define tww_strcat ((_strcat)0x8032dc6c)
#define tww_strncpy ((_strncpy)0x8032dc98)
#define tww_strcpy ((_strcpy)0x8032dcdc)
#define tww_strcmp ((_strcmp)0x8032db44)
#define tww_free_addr 0x80241330
#define tww_memset_addr 0x802528c4
#define tww_memalign_addr 0x802412f8
#define tww_memcpy_addr 0x80003490
#define tww_draw_console_addr 0x802cac18
#define tww_cDyl_InitAsync_addr 0x80022df8
#define tww_fapGm_Execute_addr 0x800231e4

typedef char (*_strcpy)(char *dest, const char *source);
typedef char (*_strcat)(char *dst, const char *src);
typedef size_t (*_strlen)(const char *str);
typedef int (*_sprintf)(char *str, const char *string, ...);
typedef int (*_printf)(const char *string, ...);
typedef int (*_snprintf)(char *s, size_t n, const char *format, ...);
typedef char (*_strncpy) (char *destination, const char *source, size_t num);
typedef void (*tww_free_t)(void* memory);
#define tww_free ((tww_free_t)tww_free_addr)

typedef void (*tww_memset_t)(void* addr, int value, uint32_t size);
#define tww_memset ((tww_memset_t)tww_memset_addr)

typedef void* (*tww_memalign_t)(int32_t align, uint32_t size);
#define tww_memalign ((tww_memalign_t)tww_memalign_addr)

typedef void* (*tww_memcpy_t)(void* dest, void* src, size_t size);
#define tww_memcpy ((tww_memcpy_t)tww_memcpy_addr)


#define tww_mPadStatus_addr 0x803ed818
#define tww_mPadButton_addr 0x803ed848
#define tww_mPadMStick_addr 0x803ed908
#define tww_mPadSStick_addr 0x803ed948
#define g_mDoCPd_cpadInfo_addr 0x803a4df0

#define tww_PADRead_addr 0x80315a20

#define g_Counter_addr 0x803e8140

#define l_fopScnRq_IsUsingOfOverlap_addr 0x803f69e0
#define l_fopScnRq_IsUsingOfOverlap (*(int*)l_fopScnRq_IsUsingOfOverlap_addr)

#define g_env_light_addr 0x803e4ab4

#define g_dComIfG_gameInfo_addr 0x803c4c08

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

#endif