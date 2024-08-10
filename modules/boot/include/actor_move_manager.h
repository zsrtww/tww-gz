#pragma once

#include <boot/include/utils/containers/deque.h>
#include "libtww/include/dolphin/mtx/vec.h"
#include "libtww/include/dolphin/gctypes.h"
#include "libtww/include/f_op/f_op_actor.h"

typedef enum {
    ACTORMOVE_POS_YAW,
    ACTORMOVE_POS,
} ActorMoveType;

struct ActorMoveEntry {
    u32 id;
    u16 attempts;
    s16 procName;
    Vec pos;
    s16 yaw;
    ActorMoveType type;
    fopAc_ac_c* actor;
};

class ActorMoveManager {
public:
    inline void SetPosYaw(s16 procName, f32 x, f32 y, f32 z, s16 yaw) {
        AddRequest(procName, x, y, z, yaw, ACTORMOVE_POS_YAW);
    }

    inline void SetPos(s16 procName, f32 x, f32 y, f32 z) { AddRequest(procName, x, y, z, 0, ACTORMOVE_POS); }

    void ProcessRequests();

private:
    u32 mCurId;
    twwgz::containers::deque<ActorMoveEntry> mDeque;

    void AddRequest(s16 procName, f32 x, f32 y, f32 z, s16 yRot, ActorMoveType type);
    void RemoveRequest(u32 id);
    void MoveActor(ActorMoveEntry entry);
};

extern ActorMoveManager gActorMoveMgr;