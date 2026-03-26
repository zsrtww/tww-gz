#include "features/moveactor/include/moveactor.h"
#include "global_data.h"
#include "libtww/include/MSL_C/math.h"
#include "libtww/include/JSystem/JUtility/JUTGamePad.h"
#include "rels/include/defines.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "menus/menu_tools/include/tools_menu.h"

#define ROTATION_SPEED (15)
#define ROTATION_FAST_SPEED (25)
#define ROTATION_VERY_FAST_SPEED (25)
#define CAM_SPEED (1.0)
#define CAM_FAST_SPEED (4)
#define CAM_VERY_FAST_SPEED (60.0)
#define DIST_FROM_ACTOR (600)

#define CONTROL_Y (mPadStatus.stick_y)
#define CONTROL_X (mPadStatus.stick_x)
#define VERTICAL_DISPLACEMENT (mPadStatus.substick_y)
#define HORIZONTAL_DISPLACEMENT -(mPadStatus.substick_x)
#define SPEED_PREDICATE_1 (mPadButton.mButton & CButton::Z)
#define SPEED_PREDICATE_2 (mPadButton.mButton & CButton::R)
#define LOCK_CAMERA (mPadButton.mButton & CButton::L)

#define WHITE_RGBA 0xFFFFFFFF
#define LINE_X_OFFSET 20.0f

// Get 2 vectors at a specific memory address.
// These CAM_TARGET and CAM_POS vectors are special
// because changing their values actually affect the camera in the game.
// There sould be a cleaner way to get these vectors
// but it is not in the decomp files available in gz
#ifdef NTSCJ
#define UNK_POINTER1 *(uintptr_t*)0x803AD380
#endif
#ifdef NTSCU
#define UNK_POINTER1 *(uintptr_t*)0x803B9E80
#endif
#ifdef PAL
#define UNK_POINTER1 *(uintptr_t*)0x803C0B80
#endif

#define UNK_POINTER2 (uintptr_t*)(UNK_POINTER1 + 0x34)
#define CAM_TARGET (Vec*)(*UNK_POINTER2 + 0x288);
#define CAM_POS (Vec*)(*UNK_POINTER2 + 0x294);

namespace MoveActor {

double pitch = 0.0;
double yaw = 0.0;
float angle = 0.0f;
bool enabled = false;

void move(daPy_lk_c* actor) {
    // Avoid crashing by testing this pointer
    if ((uintptr_t*)(UNK_POINTER1) == NULL) {
        return;
    }

    // Fetch the camera position and target
    Vec* cam_target = CAM_TARGET;
    Vec* cam_pos = CAM_POS;

    // Fetch the actor position and angles
    cXyz& actor_pos = actor->current.pos;
    s16& actor_horizontal_angle = actor->shape_angle.y;
    s16& actor_verticle_angle = actor->shape_angle.x;

    // Set Link momentum to 0
    cXyz tmp(0.0f, 0.0f, 0.0f);
    actor->speed = tmp;
    actor->gravity = 0;

    if (!LOCK_CAMERA) {
        angle = (float)actor_horizontal_angle / 65536.f * (2 * M_PI);
    }

    // Fix Camera behind link
    cam_target->x = actor_pos.x;
    cam_target->y = actor_pos.y + 200.f;
    cam_target->z = actor_pos.z;
    cam_pos->z = actor_pos.z - DIST_FROM_ACTOR * cos(angle);
    cam_pos->x = actor_pos.x - DIST_FROM_ACTOR * sin(angle);
    cam_pos->y = actor_pos.y + 200.f;

    // Calculate the pitch and yaw
    yaw = atan2(cam_target->z - cam_pos->z, cam_target->x - cam_pos->x);
    double horizontal = sqrtf((cam_target->x - cam_pos->x) * (cam_target->x - cam_pos->x) +
                              (cam_target->z - cam_pos->z) * (cam_target->z - cam_pos->z));
    pitch = atan2(cam_target->y - cam_pos->y, horizontal);

    // Calculate the translation
    double dy = LOCK_CAMERA ? 0.0f : VERTICAL_DISPLACEMENT;
    double dx = CONTROL_Y * cos(yaw) * cos(pitch) - CONTROL_X * sin(yaw);
    double dz = CONTROL_Y * sin(yaw) * cos(pitch) + CONTROL_X * cos(yaw);

    auto move_speed =
        SPEED_PREDICATE_1 != 0 ? SPEED_PREDICATE_2 != 0 ? CAM_VERY_FAST_SPEED : CAM_FAST_SPEED : CAM_SPEED;
    auto cam_speed = SPEED_PREDICATE_1 != 0 ? SPEED_PREDICATE_2 != 0 ? ROTATION_VERY_FAST_SPEED : ROTATION_FAST_SPEED :
                                              ROTATION_SPEED;

    // Apply the translation with a speed factor
    actor_pos.x += move_speed * dx;
    actor_pos.y += move_speed * dy;
    actor_pos.z += move_speed * dz;

    // Change facing angle with c stick
    if (LOCK_CAMERA) {
        actor_verticle_angle -= -VERTICAL_DISPLACEMENT * cam_speed;
        actor_horizontal_angle -= -HORIZONTAL_DISPLACEMENT * cam_speed;
    } else {
        actor_horizontal_angle -= HORIZONTAL_DISPLACEMENT * cam_speed;
    }

    // Apply in game all the changes made
    l_debug_keep_pos = actor_pos;
    l_debug_current_angle.x = actor_verticle_angle;
    l_debug_current_angle.y = actor_horizontal_angle;
    l_debug_shape_angle.x = actor_verticle_angle;
    l_debug_shape_angle.y = actor_horizontal_angle;
}

KEEP_FUNC void execute() {
    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);
    if (!player_p) {
        return;
    }
    if (g_moveLinkEnabled) {
        // Lock the camera to allow for its movement
        dComIfGp_getPEvtManager()->mCameraPlay = 1;

        // Disable all of Link's collisions
        if ((mPadButton.mButton & CButton::A)) {
            player_p->mAcch.ClrGrndNone();
        } else {
            player_p->mAcch.SetGrndNone();
        }
        player_p->mAcch.SetWallNone();
        player_p->mAcch.SetRoofNone();
        player_p->mAcch.OnLineCheckNone();

        // Disable voiding by setting the ground height to not -inf and telling the game Link is not midair
        player_p->mAcch.m_ground_h = -9999999999.0f;
        player_p->offModeFlg(0x00000002);

        // Disable automatic voiding/crashing in water by setting the wave level to exactly the ground height and
        // telling the game Link is not swimming
        player_p->m35D0 = -9999999999.0f;
        player_p->offModeFlg(0x00040000);

        // Disable drowning
        g_dComIfG_gameInfo.play.field_0x4928 = false;

        enabled = true;

        move(player_p);

        // Disable the X, Y and Z buttons to avoid using items
        mPadButton.mButton = mPadButton.mButton | CButton::Z | CButton::X | CButton::Y;

    } else {
        if (enabled) {
            // Enable all of Link's collisions back
            player_p->mAcch.ClrGrndNone();
            player_p->mAcch.ClrWallNone();
            player_p->mAcch.ClrRoofNone();
            player_p->mAcch.OffLineCheckNone();

            // Enable voiding by telling the game Link is midair
            player_p->onModeFlg(0x00000002);

            // Disable fixed camera and bring back gravity
            dComIfGp_getPEvtManager()->mCameraPlay = 0;
            player_p->gravity = -2.5;

            enabled = false;
        }
    }
}
}  // namespace MoveActor