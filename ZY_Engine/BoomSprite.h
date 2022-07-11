#pragma once
#include "Sprite.h"

class AudioDXBuffer;
class BoomSprite :
    public Sprite
{
public:
    BoomSprite();
    ~BoomSprite();
    BoomSprite(ZY_Animation* an);

    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;

    void setPower(int p) { _power = p; }
    int getPower() { return _power; }
    void setFendOff(float time, float spd) { _fendOffTime = time, _fendOffSed = spd; }
    float getFendOffTime() { return _fendOffTime; }
    float getFendOffSpd() { return _fendOffSed; }
    void setBoomSound(AudioDXBuffer* s) { _sound = s; }
private:
    //�˺�
    int _power;
    //�������
    //����ʱ��
    float _fendOffTime;
    //ÿ����˾���
    float _fendOffSed;
    bool _isBoomed;
    int _boomTime;
    AudioDXBuffer* _sound;//��ը��Ч
};

class BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1) = 0;
};

//�ӵ���Ч����ը��Ч
class NormalBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

//���汬ը��Ч
class FireBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

//������Ч
class CrackBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

