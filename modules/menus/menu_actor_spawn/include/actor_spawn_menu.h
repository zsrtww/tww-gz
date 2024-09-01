#include "menu.h"

#define MAX_ACTORS 10

struct ActorSpawnData {
    Cursor cursor;
    s16 l_actorID;
    uint32_t l_actorParams = 0xFFFFFFFF;
    int8_t l_actorType = -1;
    uint8_t l_paramIdx;
};

struct ActorSpawn {
    s16 id;
    uint32_t params;
    int8_t type;
};

enum {
    ACTOR_NAME_INDEX,
    ACTOR_PARAM_INDEX,
    ACTOR_SUBTYPE_INDEX,
    ACTOR_SPAWN_INDEX,
};

class ActorSpawnMenu : public Menu {
public:
    ActorSpawnMenu(ActorSpawnData&);
    virtual ~ActorSpawnMenu();
    virtual void draw();

private:
    s16& mActorID;
    uint32_t& mActorParams;
    int8_t& mActorType;
    uint8_t& mParamIdx;
    bool mParamsSelected;
    ActorSpawn mActorQueue[MAX_ACTORS];

    Line lines[4];
};
