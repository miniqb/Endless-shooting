#pragma once
#include "./ZY_Engine/Sprite.h"
#include "./ZY_Engine/Bullet.h"
#include "./ZY_Engine/Weapons.h"
#include "./ZY_Engine/BloodHearts.h"
#include "BlockSprite.h"
class PlayerDead :public DeadAction
{
public:
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim);
};
class PlayerSprite :
    public BlockSprite
{
public:
    PlayerSprite();
    PlayerSprite(ZY_Animation* an);
    void initBlood(const wstring& str);
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
    virtual void getHurt(int hurt)override;
    void bloodReturnUpdate(float dt);
    void addMaxHealth(int h);
    void setMaxHealth(int h);
    void setHealth(int h);
    void setFullHealth();
    void setWeapons(Weapons* w);
    void changeWeapons(Weapons* w);
    void changeBullet(BulletFactor* bf);
    void resetBullet();
    void setBloodReturnTime(float b) { _bloodReturnTime = b; }
    float getSkillCool(int index) { return _powers[index]->getLastCool(); }
    //void replaceChild(Node* old, Node* new_);
    virtual void setFendOff(bool f, const Vec2& _fendSp = Vec2::ZERO, float _fendTime = 0);
private:
    virtual void judgeDir()override;
    void handleInput(float dt);
    //受伤后无敌时间
    float _helpTime;
    //计时器
    float _helpTimer;
    //无敌闪烁
    float _helpFlash;

    float _helpFlashTimer;

    Weapons* _weapons;
    BloodHearts* _bloodHearts;//血条
    int _maxHealth;

    //自动回血
    float _bloodReturnTimer;
    float _bloodReturnTime;

    PlayerDead _deadAction;
};

