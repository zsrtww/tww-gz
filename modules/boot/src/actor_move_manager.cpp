#include "actor_move_manager.h"
#include "libtww/include/d/d_procname.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "libtww/include/f_op/f_op_actor_iter.h"
#include "libtww/include/m_Do/m_Do_printf.h"

KEEP_VAR ActorMoveManager gActorMoveMgr;

KEEP_FUNC void ActorMoveManager::AddRequest(s16 procName, f32 x, f32 y, f32 z, s16 yaw, ActorMoveType type) {
    mDeque.push_back({mCurId, 0, procName, {x, y, z}, yaw, type, nullptr});
    mCurId++;
}

KEEP_FUNC void ActorMoveManager::RemoveRequest(u32 id) {
    for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
        if (req->id == id) {
            mDeque.erase(req);
        }
    }
}

KEEP_FUNC void ActorMoveManager::MoveActor(ActorMoveEntry entry) {
    fopAc_ac_c* actor = entry.actor;

    switch (entry.type) {
    case ACTORMOVE_POS_YAW:
        actor->current.angle.y = actor->shape_angle.y = entry.yaw;
        // FALLTHROUGH
    case ACTORMOVE_POS:
        actor->current.pos.set(entry.pos.x, entry.pos.y, entry.pos.z);

        if (entry.procName == PROC_PLAYER) {
            l_debug_keep_pos.x = entry.pos.x;
            l_debug_keep_pos.y = entry.pos.y;
            l_debug_keep_pos.z = entry.pos.z;
        }
    }
    
}

KEEP_FUNC fopAc_ac_c* ActorMoveManager::CheckForActor(ActorMoveEntry entry) {
    return (fopAc_ac_c*)fopAcM_SearchByName(entry.procName);
}

KEEP_FUNC void ActorMoveManager::ProcessRequests() {
    for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
        req->attempts++;

        // Dont allow attempts to last longer than 5 seconds
        if (req->attempts >= 150) {
            OSReport("Couldn't find actor:%d, deleting move request:%d\n", req->procName, req->id);
            RemoveRequest(req->id);
            return;
        }

        // Separating the check and set phases introduces a purposeful 1 frame delay.
        // This is necessary, for whatever reason, for 
        if (req->actor == nullptr) {
            req->actor = CheckForActor(*req);
        } else {
            MoveActor(*req);
        }
    }   
}