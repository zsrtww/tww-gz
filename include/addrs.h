#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define tww_strlen ((_strlen)0x8032b798)
#define tww_printf ((_printf)0x803295ac)
#define tww_sprintf ((_sprintf)0x80329308)
#define tww_snprintf ((_snprintf)0x803293e8)
#define tww_strcat ((_strcat)0x8032b670)
#define tww_strncpy ((_strncpy)0x8032b69c)
#define cdyl_init_async ((_cdyl_init_async)0x80022a88)
#define tww_strcpy ((_strcpy)0x8032b6e0)
#define tww_free_addr 0x8023eac0
#define tww_memset_addr 0x80250054
#define tww_memalign_addr 0x8023ea88
#define tww_memcpy_addr 0x80003490
#define tww_draw_console_addr 0x802c8cd4

typedef char (*_strcpy)(char *dest, const char *source);
typedef char (*_strcat)(char *dst, const char *src);
typedef void (*_cdyl_init_async)();
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