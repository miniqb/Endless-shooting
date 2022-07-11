#pragma once
#include "./ZY_Engine/Sprite.h"
#include "AABB/MersenneTwister.h"
#include "./ZY_Engine/ZY_Config.h"

class SkillPower;
class ActionMode;
struct MonsterInfo
{
    //击退抗性
    float _againstFendRate;
    //击退时间
    float _fendOffTime;
    //每秒击退距离
    float _fendOffSed;
    //碰撞伤害
    int _collPower;
    //速度大小
    float _speedLen;
    //生命值
    int _health;

    SkillPower* powers[3];//目前最多只能有3个能力

    ActionMode* action;
    //是否可飞行
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
    //玩家对象
    static  BlockSprite* player;
protected:
    static int monsterSum;
    static int deadMonsterSum;
    virtual void judgeDir();
    //击退抗性
    float _againstFendRate;
    //碰撞伤害
    int _collPower;
    //速度
    Vec2 _speed;
    //速度大小
    float _speedLen;
    //方向（用来判断显示哪一幅图片）
    int _dir;
    //随机对象
    MersenneTwister _rand;
    //生命值
    int _health;
    //是否无敌
    bool _isInvincible;
    //是否加速
    bool _isSpeedUp;
    //加速率
    float _speedUpRate;
    //每次更新中被动造成的位移累积
    Vec2 _collVec;
    //击退时间
    float _fendOffTimePower;
    //每秒击退距离
    float _fendOffSedPower;
    /*******击退相关，被击退时无法进行动作*******/
    //是否被击退
    bool _isFendOff;
    //击退倒计时
    float _fendOffTimer;
    //击退时间
    float _fendOffTime;
    //每秒击退距离
    Vec2 _fendOffSed;

    /**********能力相关******************/
    SkillPower* _powers[3];//目前有3个能力

    /*******行动方案**************/
    ActionMode* _action;

    //是否可飞行
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
    //绑定按键
    char _key;
    //技能计时器
    float _timer;
    //技能冷却
    float _cooling;
    //使用者
    BlockSprite* _user;

    //下面是玩家专属
    float _inTime=0.2f;
    float _inTimer=0.2f;
};

//快速移动
class FastMovE:public SkillPower
{
public:
    virtual bool updateByPlayer(float dt)override;
    virtual bool updateByMonster(float dt)override;
    void initSkill(float st,float cool);
    void setSpeedUpTime(float t) { _speedUpTime = t; }
   // virtual float getLastCool();
private:
    //加速时长
    float _speedUpTime;
    //加速倒计时
    float _speedTimer;
};

struct BodySlaMInfo
{
    //总位移距离
    float _allMoveLen;
    //位移时间
    float _slaTime;
    //蓄力时间
    float _xuli;
    float _cooling;
};
//泰山压顶
class BodySlaM :public SkillPower
{
public:
    virtual bool updateByPlayer(float dt)override;
    virtual bool updateByMonster(float dt)override;
    void initSkill(const BodySlaMInfo& info);
    void setMove(float s, float l);
private:
    //蓄力时间
    float _xuli = 0.3;
    //一次更新位移距离
    Vec2 _onceMove;
    //总位移距离
    float _allMoveLen = 80;
    //位移时间
    float _slaTime = 1;
    //位移计时器
    float _salmTimer = 0;
    //总技能时间
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

//盘旋
class CurveMove:public ActionMode
{
public:
    virtual void update(float dt, BlockSprite* user, BlockSprite* aim);
};

//死亡
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
