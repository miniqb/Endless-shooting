#pragma once
#include "./ZY_Engine/Sprite.h"
#include "AABB/MersenneTwister.h"
#include "./ZY_Engine/ZY_Config.h"

class SkillPower;
class ActionMode;
struct MonsterInfo
{
    //���˿���
    float _againstFendRate;
    //����ʱ��
    float _fendOffTime;
    //ÿ����˾���
    float _fendOffSed;
    //��ײ�˺�
    int _collPower;
    //�ٶȴ�С
    float _speedLen;
    //����ֵ
    int _health;

    SkillPower* powers[3];//Ŀǰ���ֻ����3������

    ActionMode* action;
    //�Ƿ�ɷ���
    bool _canFly;
    float _speedUpRate;
    int _tag;
};
class BlockSprite :
    public Sprite
{
public:
    static int getMonsterSum();
    static int getDeadSum();
    static void setMonsterSum(int s);
    static void setDeadSum(int s);
    BlockSprite();
    BlockSprite(ZY_Animation* an);
    ~BlockSprite();
    void initMonster(const MonsterInfo& info);
    virtual bool collisionFuntion(Node* node)override;
    virtual void _updateSelf(float dt)override;
    virtual void getHurt(int hurt);
    void lostProp();
public:
    static void setPlayer(BlockSprite* p);
    void setSpeed(const Vec2& s) { _speed = s; }
    void setInvincible(bool i) { _isInvincible = i; }
    void setSpeedUp(bool s) { _isSpeedUp = s; }
    bool isInvincible() { return _isInvincible; }
    bool isSpeedUp() { return _isSpeedUp; }
    bool  isDead() { return _health <= 0; }
    float getSpeedLen() { return _speedLen; }
    void setSpeedLen(float s) { _speedLen = s; }
    void setCollPower(int s) { _collPower = s; }
    int getCollPower() { return _collPower; }
    void setCanFly(bool f) { _canFly = f; }
    void setPower1(SkillPower* ps) { _powers[0] = ps; }
    void setPower2(SkillPower* ps) { _powers[1] = ps; }
    void setPower3(SkillPower* ps) { _powers[2] = ps; }
    void setSpeedUpRate(float s) { _speedUpRate = s; }
    void addCollVec(const Vec2& m) { _collVec += m; }
    void setAgnFendRate(float a) { _againstFendRate = a; }
    float getAgnFendRate() { return _againstFendRate; }
    bool canFly() { return _canFly; }
    void setHealth(int h) { _health = h; }
    int getHealth() { return _health; }
    void strongSelf();
    //��Ҷ���
    static  BlockSprite* player;
protected:
    static int monsterSum;
    static int deadMonsterSum;
    virtual void judgeDir();
    //���˿���
    float _againstFendRate;
    //��ײ�˺�
    int _collPower;
    //�ٶ�
    Vec2 _speed;
    //�ٶȴ�С
    float _speedLen;
    //���������ж���ʾ��һ��ͼƬ��
    int _dir;
    //�������
    MersenneTwister _rand;
    //����ֵ
    int _health;
    //�Ƿ��޵�
    bool _isInvincible;
    //�Ƿ����
    bool _isSpeedUp;
    //������
    float _speedUpRate;
    //ÿ�θ����б�����ɵ�λ���ۻ�
    Vec2 _collVec;
    //����ʱ��
    float _fendOffTimePower;
    //ÿ����˾���
    float _fendOffSedPower;
    /*******������أ�������ʱ�޷����ж���*******/
    //�Ƿ񱻻���
    bool _isFendOff;
    //���˵���ʱ
    float _fendOffTimer;
    //����ʱ��
    float _fendOffTime;
    //ÿ����˾���
    Vec2 _fendOffSed;

    /**********�������******************/
    SkillPower* _powers[3];//Ŀǰ��3������

    /*******�ж�����**************/
    ActionMode* _action;

    //�Ƿ�ɷ���
    bool _canFly;
public:
    virtual void setFendOff(bool f, const Vec2& _fendSp=Vec2::ZERO, float _fendTime=0);
};


class SkillPower
{
public:
    virtual bool updateByPlayer(float dt) { return true; };
    virtual bool updateByMonster(float dt) { return true; };
    void setKey(char key) { _key = key; }
    BlockSprite* getUser() { return _user; }
    void setUser(BlockSprite* b) { _user = b; }
    void setCool(float f) { _cooling = f; }
    float getLastCool() { return max(_cooling - _timer, 0); }
protected:
    //�󶨰���
    char _key;
    //���ܼ�ʱ��
    float _timer;
    //������ȴ
    float _cooling;
    //ʹ����
    BlockSprite* _user;

    //���������ר��
    float _inTime=0.2f;
    float _inTimer=0.2f;
};

//�����ƶ�
class FastMovE:public SkillPower
{
public:
    virtual bool updateByPlayer(float dt)override;
    virtual bool updateByMonster(float dt)override;
    void initSkill(float st,float cool);
    void setSpeedUpTime(float t) { _speedUpTime = t; }
   // virtual float getLastCool();
private:
    //����ʱ��
    float _speedUpTime;
    //���ٵ���ʱ
    float _speedTimer;
};

struct BodySlaMInfo
{
    //��λ�ƾ���
    float _allMoveLen;
    //λ��ʱ��
    float _slaTime;
    //����ʱ��
    float _xuli;
    float _cooling;
};
//̩ɽѹ��
class BodySlaM :public SkillPower
{
public:
    virtual bool updateByPlayer(float dt)override;
    virtual bool updateByMonster(float dt)override;
    void initSkill(const BodySlaMInfo& info);
    void setMove(float s, float l);
private:
    //����ʱ��
    float _xuli = 0.3;
    //һ�θ���λ�ƾ���
    Vec2 _onceMove;
    //��λ�ƾ���
    float _allMoveLen = 80;
    //λ��ʱ��
    float _slaTime = 1;
    //λ�Ƽ�ʱ��
    float _salmTimer = 0;
    //�ܼ���ʱ��
    float _allMoveTime;
};

class ActionMode
{
public:
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim) {};
};

class FireSkill :public SkillPower
{
public:
    virtual bool updateByPlayer(float dt)override { return true; };
    virtual bool updateByMonster(float dt)override;
    void setFireSpeed(float sp) { _fireSpeed = sp; _timer = 0; }
private:
    float _fireSpeed=100;
};

class LinearMove:public ActionMode
{
public:
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim);
};

//����
class CurveMove:public ActionMode
{
public:
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim);
};

//����
class DeadAction :public ActionMode
{
protected:
    float _fullTime = 0.3f;
    float _disTime = 0.5f;
    float _timer = 0;
    bool _fdir;
public:
    DeadAction();
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim);
};
