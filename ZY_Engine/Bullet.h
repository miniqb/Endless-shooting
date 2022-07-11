#pragma once
#include "BoomSprite.h"
#include "ZY_Config.h"

class FlyEffect;
class CollisionEffect;
struct bulletInfo
{
    ZY_Animation* _ain;
    //伤害：基础
    int _basisPower;
    //最大穿透数量
    int _penetration;
    //最大存在时间
    float _surviveTime;
    float _speedRate;
    int _tag;
};

class Bullet :
    public Sprite
{
public:
    Bullet();
    ~Bullet();
    Bullet(ZY_Animation* an);

    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
    void initBullet(const bulletInfo& info);
public:
    const Vec2& getSpeed() { return _speed; }
    int getPower(){return _basisPower+_gunPower;}
    Node* getLastHit() { return _lastHit; }
    void setSpeedRate(float r) { _speedRate = r; }
protected:
    float _speedLen;
    //子弹速度加成
    float _speedRate;
    //速度
    Vec2 _speed;
    //伤害：基础
    int _basisPower;
    //伤害：枪械附加
    int _gunPower;
    //最大穿透数量
    int _penetration;
    //最大存在时间
    float _surviveTime;

    //上一个打到的对象
    Node* _lastHit;

public:
    //速度
    void setSpeed(const Vec2& sp);
    //伤害：基础
    void setBasisPower(int p) { _basisPower = p; }
    //伤害：最终
    void setPower(int p) { _gunPower = p; }
    //最大穿透数量
    void setPentration(int p) { _penetration = p; }
    //最大存在时间
    void setSurvivrTime(float s) { _surviveTime = s; }
    float getSurvivrTime() { return _surviveTime; }

    //上一个被打的敌人
    void setLastHit(Node* l) { _lastHit = l; }
};
//爆炸弹
class BoomBullet :public Bullet
{
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
};
//导弹
class TrackBullet :public Bullet
{
public:
    void setMaxTurn(float m) { _maxTurn = m; }
    void setDetecTion(float d) { _detection.set(d, d); }
    void setAim(Node* aim) { _aim = aim; }
    virtual void _updateSelf(float dt)override;
private:
    //目标物
    Node* _aim = nullptr;
    //最大转弯角度
    float _maxTurn = 0;
    //检测范围
    Vec2 _detection;

};
//贯穿弹
class ThourthBullet :public Bullet
{
    //伤害冷却
    float _cooling;
    float _coolTimer = 0;;
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
    void setCooling(float c) { _cooling = c,_coolTimer=c; }
};
//反射弹
class ReboundBullet :public Bullet
{
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
};