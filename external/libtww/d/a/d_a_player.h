#ifndef D_A_PLAYER
#define D_A_PLAYER

#include "../../f_op/f_op_actor_mng.h"
#include "../../addrs.h"

class daPy_demo_c {
public:
    void setDemoType(u16 pType) { mDemoType = pType; }
    int getDemoType() const { return mDemoType; }
    void setDemoMode(u32 mode) { mDemoMode = mode; }
    u32 getDemoMode() const { return mDemoMode; }
    int getParam1() const { return mParam1; }
    void setTimer(s16 time) { mTimer = time; }
    void decTimer() { mTimer--; }
    void setOriginalDemoType() { setDemoType(3); }
    void setSpecialDemoType() { setDemoType(5); }
    void setSystemDemoType() { setDemoType(2); }
    void setStick(f32 stick) { mStick = stick; }
    void setMoveAngle(s16 angle) { mDemoMoveAngle = angle; }
    s16 getMoveAngle() const { return mDemoMoveAngle; }
    f32 getStick() { return mStick; }
    int getParam0() const { return mParam0; }
    void setParam0(int value) { mParam0 = value; }
    void setParam1(int value) { mParam1 = value; }
    void setParam2(int value) { mParam2 = value; }

private:
    /* 0x00 */ u16 mDemoType;
    /* 0x02 */ s16 mDemoMoveAngle;
    /* 0x04 */ s16 mTimer;
    /* 0x06 */ s16 mParam2;
    /* 0x08 */ int mParam0;
    /* 0x0C */ int mParam1;
    /* 0x10 */ u32 mDemoMode;
    /* 0x14 */ f32 mStick;
};  // Size: 0x18

class daPy_py_c : public fopAc_ac_c {
public:
    enum daPy_FLG0 {
        daPyFlg0_UNK4               = 0x00000004,
        daPyFlg0_DEKU_SP_RETURN_FLG = 0x00000010,
        daPyFlg0_CUT_AT_FLG         = 0x00000040,
        daPyFlg0_UNK100             = 0x00000100,
        daPyFlg0_SHIP_DROP          = 0x00000200,
        daPyFlg0_PUSH_PULL_KEEP     = 0x00000800,
        daPyFlg0_HOVER_BOOTS        = 0x00001000,
        daPyFlg0_UNK4000            = 0x00004000,
        daPyFlg0_UNK10000           = 0x00010000,
        daPyFlg0_NO_FALL_VOICE      = 0x00040000,
        daPyFlg0_SCOPE_CANCEL       = 0x00080000,
        daPyFlg0_UNK200000          = 0x00200000,
        daPyFlg0_EQUIP_HEAVY_BOOTS  = 0x02000000,
        daPyFlg0_NO_DRAW            = 0x08000000,
        daPyFlg0_HEAVY_STATE        = 0x40000000,
    };
    
    enum daPy_FLG1 {
        daPyFlg1_EQUIP_DRAGON_SHIELD    = 0x00000001,
        daPyFlg1_NPC_CALL_COMMAND       = 0x00000002,
        daPyFlg1_CASUAL_CLOTHES         = 0x00000008,
        daPyFlg1_FORCE_VOMIT_JUMP       = 0x00000010,
        daPyFlg1_NPC_NOT_CHANGE         = 0x00000040,
        daPyFlg1_UNK80                  = 0x00000080,
        daPyFlg1_CONFUSE                = 0x00000100,
        daPyFlg1_UNK400                 = 0x00000400,
        daPyFlg1_FREEZE_STATE           = 0x00000800,
        daPyFlg1_SHIP_TACT              = 0x00001000,
        daPyFlg1_USE_ARROW_EFFECT       = 0x00002000,
        daPyFlg1_LETTER_READ_EYE_MOVE   = 0x00004000,
        daPyFlg1_UNK8000                = 0x00008000,
        daPyFlg1_FORCE_VOMIT_JUMP_SHORT = 0x00010000,
        daPyFlg1_FOREST_WATER_USE       = 0x00020000,
        daPyFlg1_WATER_DROP             = 0x00080000,
        daPyFlg1_UNK200000              = 0x00200000,
        daPyFlg1_UNK800000              = 0x00800000,
        daPyFlg1_UNK1000000             = 0x01000000,
        daPyFlg1_VINE_CATCH             = 0x02000000,
        daPyFlg1_UNK8000000             = 0x08000000,
        daPyFlg1_LAST_COMBO_WAIT        = 0x20000000,
    };
    
    enum daPy_RFLG0 {
        daPyRFlg0_UNK2                  = 0x00000002,
        daPyRFlg0_ROPE_GRAB_RIGHT_HAND  = 0x00000004,
        daPyRFlg0_GRAB_UP_END           = 0x00000020,
        daPyRFlg0_AUTO_JUMP_LAND        = 0x00000040,
        daPyRFlg0_RIGHT_FOOT_ON_GROUND  = 0x00000400,
        daPyRFlg0_LEFT_FOOT_ON_GROUND   = 0x00000800,
        daPyRFlg0_FRONT_ROLL_CRASH      = 0x00002000,
        daPyRFlg0_UNK4000               = 0x00004000,
        daPyRFlg0_GRAB_UP_START         = 0x00008000,
        daPyRFlg0_ATTENTION_LOCK        = 0x00010000,
        daPyRFlg0_HAMMER_QUAKE          = 0x00020000,
        daPyRFlg0_POISON_CURSE          = 0x00100000,
        daPyRFlg0_GRAB_PUT_START        = 0x00400000,
        daPyRFlg0_TACT_USE              = 0x01000000,
        daPyRFlg0_FAIRY_USE             = 0x02000000,
        daPyRFlg0_UNK8000000            = 0x08000000,
        daPyRFlg0_ARROW_SHOOT           = 0x20000000,
        // 0x00000001 and 0x00000002 set in daPy_lk_c::dProcLastCombo
        // 0x00001000 set in daPy_lk_c::procCrawlMove_init, checked in checkNoCollisionCorret__9daPy_lk_cFv
        // 0x04000000 set in daPy_lk_c::procShipPaddle
    };
    
    enum daPy_FACE {
        
    };
    
    /* 0x290 */ u8 mAttackState;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292[0x294 - 0x292];
    /* 0x294 */ s16 mDamageWaitTimer;
    /* 0x296 */ s16 mQuakeTimer;
    /* 0x298 */ int field_0x298;
    /* 0x29C */ u32 mNoResetFlg0;
    /* 0x2A0 */ u32 mNoResetFlg1;
    /* 0x2A4 */ u32 mResetFlg0;
    /* 0x2A8 */ f32 field_0x2a8;
    /* 0x2AC */ f32 field_0x2ac;
    /* 0x2B0 */ f32 field_0x2b0;
    /* 0x2B4 */ csXyz mBodyAngle;
    /* 0x2BC */ cXyz mHeadTopPos;
    /* 0x2C8 */ cXyz mSwordTopPos;
    /* 0x2D4 */ cXyz field_0x2d4;
    /* 0x2E0 */ cXyz field_0x2e0;
    /* 0x2EC */ cXyz mRopePos;
    /* 0x2F8 */ cXyz field_0x2f8;
    /* 0x304 */ daPy_demo_c mDemo;
    /* 0x31C */ void* vtable;

    u8 getCutType() const { return mAttackState; }
    s16 getDamageWaitTimer() const { return mDamageWaitTimer; }
    s16 getBodyAngleX() { return mBodyAngle.x; }
    s16 getBodyAngleY() { return mBodyAngle.y; }
    void getLeftHandPos() const {}
    void getRightHandPos() const {}
    void getSwordTopPos() const {}
    cXyz getHeadTopPos() const { return mHeadTopPos; }
    cXyz* getHeadTopPosP() { return &mHeadTopPos; }
    f32 getSpeedF() const { return speedF; }
    
    void changeDemoMode(u32) {}
    void changeDemoMoveAngle(s16 angle) { mDemo.setMoveAngle(angle); }
    void changeDemoParam0(int) {}
    void changeOriginalDemo() {
        mDemo.setOriginalDemoType();
        mDemo.setParam0(0);
    }

    void onNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 |= flag; }
    void offNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 &= ~flag; }
    bool checkNoResetFlg0(daPy_FLG0 flag) const { return mNoResetFlg0 & flag; }
    bool getCutAtFlg() const { return checkNoResetFlg0(daPyFlg0_CUT_AT_FLG); }
    void onPushPullKeep() { onNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    void offPushPullKeep() { offNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    bool checkEquipHoverBoots() const { return checkNoResetFlg0(daPyFlg0_HOVER_BOOTS); }
    void onNoFallVoice() { onNoResetFlg0(daPyFlg0_NO_FALL_VOICE); }
    void onScopeCancel() { onNoResetFlg0(daPyFlg0_SCOPE_CANCEL); }
    bool checkEquipHeavyBoots() const { return checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS); }
    void onPlayerNoDraw() { onNoResetFlg0(daPyFlg0_NO_DRAW); }
    void offPlayerNoDraw() { offNoResetFlg0(daPyFlg0_NO_DRAW); }
    void onHeavyState() { onNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    void offHeavyState() { offNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    bool getHeavyState() { return checkNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    bool getHeavyStateAndBoots() { return checkNoResetFlg0(static_cast<daPy_FLG0>(daPyFlg0_HEAVY_STATE | daPyFlg0_EQUIP_HEAVY_BOOTS)); }
    
    void onNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 |= flag; }
    void offNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 &= ~flag; }
    bool checkNoResetFlg1(daPy_FLG1 flag) const { return mNoResetFlg1 & flag; }
    bool checkEquipDragonShield() const { return checkNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD); }
    void onNpcCallCommand() { onNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void onNpcCall() { onNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void offNpcCallCommand() { offNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    bool checkNpcCallCommand() const { return checkNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void onForceVomitJump() { onNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP); }
    void onNpcNotChange() { onNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    void offNpcNotChange() { offNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    bool checkNpcNotChange() const { return checkNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    void onConfuse() { onNoResetFlg1(daPyFlg1_CONFUSE); }
    void offConfuse() { offNoResetFlg1(daPyFlg1_CONFUSE); }
    bool checkConfuse() const { return checkNoResetFlg1(daPyFlg1_CONFUSE); }
    bool checkFreezeState() const { return checkNoResetFlg1(daPyFlg1_FREEZE_STATE); }
    void onUseArrowEffect() { onNoResetFlg1(daPyFlg1_USE_ARROW_EFFECT); }
    void offUseArrowEffect() { offNoResetFlg1(daPyFlg1_USE_ARROW_EFFECT); }
    void onLetterReadEyeMove() { onNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE); }
    void onForceVomitJumpShort() { onNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP_SHORT); }
    bool checkForestWaterUse() const { return checkNoResetFlg1(daPyFlg1_FOREST_WATER_USE); }
    void onWaterDrop() { onNoResetFlg1(daPyFlg1_WATER_DROP); }
    void onVineCatch() { onNoResetFlg1(daPyFlg1_VINE_CATCH); }
    bool checkLastComboWait() const { return checkNoResetFlg1(daPyFlg1_LAST_COMBO_WAIT); }
    
    void onResetFlg0(daPy_RFLG0 flag) { mResetFlg0 |= flag; }
    void offResetFlg0(daPy_RFLG0 flag) { mResetFlg0 &= ~flag; }
    bool checkResetFlg0(daPy_RFLG0 flag) const { return mResetFlg0 & flag; }
    bool getRopeGrabRightHand() const { return checkResetFlg0(daPyRFlg0_ROPE_GRAB_RIGHT_HAND); }
    bool getGrabUpEnd() const { return checkResetFlg0(daPyRFlg0_GRAB_UP_END); }
    bool getAutoJumpLand() const { return checkResetFlg0(daPyRFlg0_AUTO_JUMP_LAND); }
    bool getRightFootOnGround() const { return checkResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND); }
    bool getLeftFootOnGround() const { return checkResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND); }
    bool getFootOnGround() const { return getRightFootOnGround() || getLeftFootOnGround(); }
    bool checkFrontRollCrash() const { return checkResetFlg0(daPyRFlg0_FRONT_ROLL_CRASH); }
    bool getGrabUpStart() const { return checkResetFlg0(daPyRFlg0_GRAB_UP_START); }
    bool checkAttentionLock() const { return checkResetFlg0(daPyRFlg0_ATTENTION_LOCK); }
    bool checkHammerQuake() const { return checkResetFlg0(daPyRFlg0_HAMMER_QUAKE); }
    void onPoisonCurse() { onResetFlg0(daPyRFlg0_POISON_CURSE); }
    bool getGrabPutStart() const { return checkResetFlg0(daPyRFlg0_GRAB_PUT_START); }
    bool checkFairyUse() const { return checkResetFlg0(daPyRFlg0_FAIRY_USE); }
    bool checkTactUse() const { return checkResetFlg0(daPyRFlg0_TACT_USE); }
    bool checkArrowShoot() const { return checkResetFlg0(daPyRFlg0_ARROW_SHOOT); }
    
    bool checkGrabWear() const { return field_0x2b0 < 0.0f; }
};  // Size: 0x320

#endif /* D_A_PLAYER */