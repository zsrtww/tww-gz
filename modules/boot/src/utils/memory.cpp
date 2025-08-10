#include "utils/memory.h"
#include <cstdio>
#include "watches.h"
#include "pos_settings.h"
#include "settings.h"
#include "libtww/include/JSystem/JKernel/JKRHeap.h"
#include "libtww/include/m_Do/m_Do_ext.h"
#include "rels/include/defines.h"
#include "tools.h"

KEEP_FUNC void GZ_drawWatches() {
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].visible) {
            char rendered_value[13];
            switch (g_watches[i].type) {
            case MEM_TYPE_U32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%08X" : "%u",
                             *(uint32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%08X" : "%u",
                             *(uint32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_U16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%04X" : "%u",
                             *(uint16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%04X" : "%u",
                             *(uint16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_U8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%02X" : "%u",
                             *(uint8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%02X" : "%u",
                             *(uint8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_S32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%08X" : "%i",
                             *(int32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%08X" : "%i",
                             *(int32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_S16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%04X" : "%i",
                             *(int16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%04X" : "%i",
                             *(int16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_S8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%02X" : "%i",
                             *(int8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), g_watches[i].hex ? "%02X" : "%i",
                             *(int8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_F32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), "%.4f",
                             *(float*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), "%.4f", *(float*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            case MEM_TYPE_STR:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), "%s",
                             (char*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), "%s", (char*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF, g_dropShadows);
                break;
            }
        }
    }
}
