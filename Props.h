#pragma once
#include "./ZY_Engine/Sprite.h"
#include "./ZY_Engine/Weapons.h"
class Props :
    public Sprite
{
public:
    static const int BULLET = 0;
    static const int WEAPON = 1;
    Props();
    ~Props();
    virtual void updateSelf(float dt);
    virtual bool collisionFuntion(Node* node);
    void setType(int t) { _type = t; }
    void setBulletType(BulletFactor* bf) { _bullet = bf; _type = BULLET; }
    void setWeaponType(WeaponsFactor* w) { _weapon = w; _type = WEAPON; }
    int getType() { return _type; }
private:
    int _type=0;
    WeaponsFactor* _weapon = nullptr;
    BulletFactor* _bullet = nullptr;
    //存在时间
    float _exitTime=15;
    //闪烁时间
    float _lastTime=12;
    float _timer = 0;

    float _flashTime = 0.15f;
    float _flashTimer = 0.15f;
};

class PropsFactor
{
public:
    static PropsFactor* weaponsProp[4];
    static PropsFactor* bulletProp[4];
    static void init();
    static void release();
    virtual Props* getProps() = 0;
};

class BoomPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class NotePropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class ReboundPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class ThroughPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class RevolverPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class RiflePropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class ShotgunPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};

class BossPropsFactor :public PropsFactor
{
public:
    virtual Props* getProps();
};