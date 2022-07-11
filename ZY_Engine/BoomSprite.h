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
    //伤害
    int _power;
    //击退相关
    //击退时间
    float _fendOffTime;
    //每秒击退距离
    float _fendOffSed;
    bool _isBoomed;
    int _boomTime;
    AudioDXBuffer* _sound;//爆炸音效
};

class BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1) = 0;
};

//子弹无效果爆炸特效
class NormalBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

//火焰爆炸特效
class FireBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

//地裂特效
class CrackBoom :public BoomSpriteFactor
{
public:
    virtual BoomSprite* getBoom(const Vec2& pos,int l=1)override;
};

