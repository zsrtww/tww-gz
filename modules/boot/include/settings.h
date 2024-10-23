#pragma once

#include <stdint.h>
#include "utils/lines.h"
#include "utils/containers/deque.h"

#define CURSOR_RGBA g_cursorColor
#define FONT_OPTIONS_COUNT (sizeof(g_font_opt) / sizeof(g_font_opt[0]))

#define LOAD_AREA 0
#define LOAD_FILE 1

#define ACTIVE_FUNC(id) []() { return GZStng_getData(id, false); }

#define DEFAULT_CUSTOM_SAVE_SPAWN true

extern ListMember g_font_opt[7];

// WARNING
// The order is important, DO NOT add entries in the middle of the enum.
// Add them at the end, even if it should be with an other group.
// Changes in the order is only allowed when the
// version number GZ_SAVE_VERSION_NUMBER is changed.
enum GZSettingID : uint32_t {
    // Miscellaneous
    STNG_DROP_SHADOWS,
    STNG_CURSOR_COLOR,
    STNG_FONT,
    STNG_EQUIP_PRIORITY,
    STNG_LAND_SPEED,
    STNG_WATER_SPEED,
    STNG_ANGLE_VALUES_IN_DECIMAL,
    STNG_CUSTOM_SAVE_SPAWNS,
    // Cheats
    STNG_CHEATS_INFINITE_AIR,
    STNG_CHEATS_INFINITE_ARROWS,
    STNG_CHEATS_INFINITE_BOMBS,
    STNG_CHEATS_INFINITE_HEARTS,
    STNG_CHEATS_REFILL_HEALTH,
    STNG_CHEATS_INFINITE_MAGIC,
    STNG_CHEATS_REFILL_MAGIC,
    STNG_CHEATS_INFINITE_RUPEES,
    STNG_CHEATS_MOON_JUMP,
    STNG_CHEATS_STORAGE,
    STNG_CHEATS_NORMAL_COLLISION,
    STNG_CHEATS_CHEST_STORAGE,
    STNG_CHEATS_DOOR_CANCEL,
    STNG_CHEATS_QUARTER_HEART,
    STNG_CHEATS_FAST_MOVEMENT,
    STNG_CHEATS_UPCHARGE,
    // Item Equips
    STNG_ITEM_EQUIP_TELESCOPE,
    STNG_ITEM_EQUIP_SAIL,
    STNG_ITEM_EQUIP_WIND_WAKER,
    STNG_ITEM_EQUIP_GRAPPLING_HOOK,
    STNG_ITEM_EQUIP_BOOMERANG,
    STNG_ITEM_EQUIP_DEKU_LEAF,
    STNG_ITEM_EQUIP_TINGLE_TUNER,
    STNG_ITEM_EQUIP_PROGRESSIVE_PICTO_BOX,
    STNG_ITEM_EQUIP_IRON_BOOTS,
    STNG_ITEM_EQUIP_MAGIC_ARMOR,
    STNG_ITEM_EQUIP_PROGRESSIVE_BOW,
    STNG_ITEM_EQUIP_BOMBS,
    STNG_ITEM_EQUIP_HOOKSHOT,
    STNG_ITEM_EQUIP_SKULL_HAMMER,
    // Tools
    STNG_TOOLS_DEBUG,
    STNG_TOOLS_TIME_DISP,
    STNG_TOOLS_STAGE_INFO,
    STNG_TOOLS_TELEPORT,
    STNG_TOOLS_AREA_RELOAD,
    STNG_TOOLS_MAP_SELECT,
    STNG_TOOLS_ZH,
    STNG_TOOLS_INPUT_VIEWER,
    STNG_TOOLS_FRAME_COUNT,
    STNG_TOOLS_FRAME_ADVANCE,
    STNG_TOOLS_ESS_CHECKER,
    STNG_TOOLS_DEADZONE_CHECKER,
    STNG_TOOLS_DISABLE_SVCHECK,
    STNG_TOOLS_INTRO_SKIP,
    STNG_TOOLS_VOID,
    // Watches
    STNG_WATCHES,
    // Combos
    STNG_CMD_STORE_POSITION,
    STNG_CMD_LOAD_POSITION,
    STNG_CMD_MOON_JUMP,
    STNG_CMD_STORAGE,
    STNG_CMD_NORMAL_COLLISION,
    STNG_CMD_CHEST_STORAGE,
    STNG_CMD_DOOR_CANCEL,
    STNG_CMD_QUARTER_HEART,
    STNG_CMD_FAST_MOVEMENT,
    STNG_CMD_UPCHARGE,
    STNG_CMD_AREA_RELOAD,
    STNG_CMD_REFILL_HEALTH,
    STNG_CMD_REFILL_MAGIC,
    STNG_CMD_TOGGLE_TIMER,
    STNG_CMD_RESET_TIMER,
    STNG_CMD_VOID,
    // Sprites
    STNG_SPRITES_MENU,
    STNG_SPRITES_FIFO,
    STNG_SPRITES_DEBUG_INFO,
    STNG_SPRITES_TIME_DISP,
    STNG_SPRITES_VIEWER,
    STNG_SPRITES_COUNT,
    STNG_SPRITES_ZH_INFO,
    STNG_SPRITES_STAGE_INFO,
    // Combos
    // TODO

    // New Adds
};

struct GZSettingEntry {
    GZSettingID id;
    size_t size;
    void* data;
};

extern twwgz::containers::deque<GZSettingEntry*> g_settings;

/**
 * If the setting is not yet in the list, adds it.
 * Otherwise, deletes the old data, and replaces it by the provided one.
 */
void GZStng_add(GZSettingID id, void* data, size_t size);
/**
 * Removes a setting from the list.
 */
void GZStng_remove(GZSettingID id);
/**
 * Returns a setting entry if it is in the list. nullptr otherwise.
 */
GZSettingEntry* GZStng_get(GZSettingID id);
/**
 * Returns a list of all the ids of the settings in the list.
 */
twwgz::containers::deque<GZSettingID>* GZStng_getList();

template <typename T>
T GZStng_getData(GZSettingID id, T defaultValue) {
    auto* stng = GZStng_get(id);
    return stng ? *static_cast<T*>(stng->data) : defaultValue;
}

enum cursor_colors {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

void GZ_initFont();

inline bool GZ_checkDropShadows() {
    auto* stng = GZStng_get(STNG_DROP_SHADOWS);
    return stng && *static_cast<bool*>(stng->data);
}
