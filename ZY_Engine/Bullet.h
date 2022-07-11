#pragma once
#include "BoomSprite.h"
#include "ZY_Config.h"

class FlyEffect;
class CollisionEffect;
struct bulletInfo
{
    ZY_Animation* _ain;
    //�˺�������
    int _basisPower;
    //���͸����
    int _penetration;
    //������ʱ��
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
    //�ӵ��ٶȼӳ�
    float _speedRate;
    //�ٶ�
    Vec2 _speed;
    //�˺�������
    int _basisPower;
    //�˺���ǹе����
    int _gunPower;
    //���͸����
    int _penetration;
    //������ʱ��
    float _surviveTime;

    //��һ���򵽵Ķ���
    Node* _lastHit;

public:
    //�ٶ�
    void setSpeed(const Vec2& sp);
    //�˺�������
    void setBasisPower(int p) { _basisPower = p; }
    //�˺�������
    void setPower(int p) { _gunPower = p; }
    //���͸����
    void setPentration(int p) { _penetration = p; }
    //������ʱ��
    void setSurvivrTime(float s) { _surviveTime = s; }
    float getSurvivrTime() { return _surviveTime; }

    //��һ������ĵ���
    void setLastHit(Node* l) { _lastHit = l; }
};
//��ը��
class BoomBullet :public Bullet
{
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
};
//����
class TrackBullet :public Bullet
{
public:
    void setMaxTurn(float m) { _maxTurn = m; }
    void setDetecTion(float d) { _detection.set(d, d); }
    void setAim(Node* aim) { _aim = aim; }
    virtual void _updateSelf(float dt)override;
private:
    //Ŀ����
    Node* _aim = nullptr;
    //���ת��Ƕ�
    float _maxTurn = 0;
    //��ⷶΧ
    Vec2 _detection;

};
//�ᴩ��
class ThourthBullet :public Bullet
{
    //�˺���ȴ
    float _cooling;
    float _coolTimer = 0;;
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
    void setCooling(float c) { _cooling = c,_coolTimer=c; }
};
//���䵯
class ReboundBullet :public Bullet
{
public:
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
};