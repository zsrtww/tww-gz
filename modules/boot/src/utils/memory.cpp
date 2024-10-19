#include "utils/memory.h"
#include <cstdio>
#include "pos_settings.h"
#include "settings.h"
#include "rels/include/defines.h"
#include "tools.h"

char l_watchesFormats[][8][5] = {{
                                     "%u",
                                     "%i",
                                     "%u",
                                     "%i",
                                     "%u",
                                     "%i",
                                     "%.2f",
                                     "%s",
                                 },
                                 {
                                     "%02X",
                                     "%02X",
                                     "%04X",
                                     "%04X",
                                     "%08X",
                                     "%08X",
                                     "%.2f",
                                     "%s",
                                 }};

KEEP_FUNC void GZ_drawWatches() {
    auto* stng = GZStng_get(STNG_WATCHES);
    if (!stng) {
        stng = new GZSettingEntry{STNG_WATCHES, 0, nullptr};
        g_settings.push_back(stng);
    }

    MemoryWatch* watches = stng ? static_cast<MemoryWatch*>(stng->data) : nullptr;
    size_t n_watches = stng ? stng->size / sizeof(MemoryWatch) : 0;

    for (size_t i = 0; i < n_watches; i++) {
        if (watches[i].visible) {
            char rendered_value[32];
            uint32_t address = watches[i].address;
            char* format = l_watchesFormats[watches[i].hex][watches[i].type];
            if (watches[i].offset > 0x0000 && *(uint32_t*)watches[i].address != 0) {
                address = (*(uint32_t*)watches[i].address + watches[i].offset);
            }
            switch (watches[i].type) {
            case MEM_TYPE_U8:
                snprintf(rendered_value, sizeof(rendered_value), format, *(uint8_t*)address);
                break;
            case MEM_TYPE_S8:
                snprintf(rendered_value, sizeof(rendered_value), format, *(int8_t*)address);
                break;
            case MEM_TYPE_U16:
                snprintf(rendered_value, sizeof(rendered_value), format, *(uint16_t*)address);
                break;
            case MEM_TYPE_S16:
                snprintf(rendered_value, sizeof(rendered_value), format, *(int16_t*)address);
                break;
            case MEM_TYPE_U32:
                snprintf(rendered_value, sizeof(rendered_value), format, *(uint32_t*)address);
                break;
            case MEM_TYPE_S32:
                snprintf(rendered_value, sizeof(rendered_value), format, *(int32_t*)address);
                break;
            case MEM_TYPE_F32:
                snprintf(rendered_value, sizeof(rendered_value), format, *(float*)address);
                break;
            case MEM_TYPE_STR:
                snprintf(rendered_value, sizeof(rendered_value), format, (char*)address);
                break;
            }
            Font::GZ_drawStr(rendered_value, watches[i].x, watches[i].y, 0xFFFFFFFF, GZ_checkDropShadows());
        }
    }
}
