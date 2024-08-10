#include "actor_move_manager.h"
#include "libtww/include/f_op/f_op_actor_iter.h"
#include "libtww/include/f_op/f_op_actor.h"
#include "libtww/include/m_Do/m_Do_printf.h"

KEEP_VAR ActorMoveManager gActorMoveMgr;

KEEP_FUNC void ActorMoveManager::AddRequest(s16 procName, f32 x, f32 y, f32 z, s16 yaw, ActorMoveType type) {
    mDeque.push_back({mCurId, 0, procName, {x, y, z}, yaw, type});
    mCurId++;
}

KEEP_FUNC void ActorMoveManager::RemoveRequest(u32 id) {
    for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
        if (req->id == id) {
            mDeque.erase(req);
        }
    }
}

KEEP_FUNC bool ActorMoveManager::TryMovingActor(ActorMoveEntry entry) {
    fopAc_ac_c* actor = (fopAc_ac_c*)fopAcM_SearchByName(entry.procName);

    // If actor is NULL at this point, the actor doesn't exist yet and may still be creating
    if (actor != nullptr) {
        switch (entry.type) {
        case ACTORMOVE_POS_YAW:
            actor->current.angle.y = actor->shape_angle.y = entry.yaw;
            // FALLTHROUGH
        case ACTORMOVE_POS:
            actor->current.pos.set(entry.pos.x, entry.pos.y, entry.pos.z);
        }

        return true;
    }

    return false;
}

KEEP_FUNC void ActorMoveManager::ProcessRequests() {
    for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
        if (TryMovingActor(*req)) {
            RemoveRequest(req->id);
        } else {
            req->attempts++;

            // Dont allow attempts to last longer than 5 seconds
            if (req->attempts >= 150) {
                OSReport("Couldn't find actor:%d, deleting move request:%d\n", req->procName, req->id);
                RemoveRequest(req->id);
            }
        }
    }   
}