#include "equip_priority.h"
#include <algorithm>

int16_t g_item_equipe_order[NUM_ITEM_EQUIPS] = {0};

const GZSettingID g_item_equip_setting_ids[] = {
    STNG_ITEM_EQUIP_TELESCOPE,       STNG_ITEM_EQUIP_SAIL,
    STNG_ITEM_EQUIP_WIND_WAKER,      STNG_ITEM_EQUIP_GRAPPLING_HOOK,
    STNG_ITEM_EQUIP_BOOMERANG,       STNG_ITEM_EQUIP_DEKU_LEAF,
    STNG_ITEM_EQUIP_TINGLE_TUNER,    STNG_ITEM_EQUIP_PROGRESSIVE_PICTO_BOX,
    STNG_ITEM_EQUIP_IRON_BOOTS,      STNG_ITEM_EQUIP_MAGIC_ARMOR,
    STNG_ITEM_EQUIP_PROGRESSIVE_BOW, STNG_ITEM_EQUIP_BOMBS,
    STNG_ITEM_EQUIP_HOOKSHOT,        STNG_ITEM_EQUIP_SKULL_HAMMER,
};

/**
 * @brief Fetches the order of the item equips from the settings and validates them.
 */
void fetchOrder() {
    // First populate the order array with -1 to signify that the item equip has not been set
    for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
        g_item_equipe_order[i] = -1;
    }
    // Fetch the settings for each item equip
    for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
        auto stng = GZStng_get(g_item_equip_setting_ids[i]);
        if (stng != nullptr) {
            g_item_equipe_order[i] = static_cast<ItemEquipSettings*>(stng->data)->order;
        }
    }
    // Validate the order array by checking if all values are unique and under NUM_ITEM_EQUIPS
    for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
        if (g_item_equipe_order[i] == -1) {
            continue;
        }
        if (g_item_equipe_order[i] >= NUM_ITEM_EQUIPS) {
            g_item_equipe_order[i] = -1;
        }
        for (int j = i + 1; j < NUM_ITEM_EQUIPS; j++) {
            if (g_item_equipe_order[j] == -1) {
                continue;
            }
            if (g_item_equipe_order[i] == g_item_equipe_order[j]) {
                g_item_equipe_order[j] = -1;
            }
        }
    }
    // Finally, set the order of the item equips that have not been set to the smallest available value not in the array
    int16_t order = 0;
    for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
        if (g_item_equipe_order[i] == -1) {
            while (std::find(std::begin(g_item_equipe_order), std::end(g_item_equipe_order), order) != std::end(g_item_equipe_order)) {
                order++;
            }
            g_item_equipe_order[i] = order;
        }
    }
}
