#pragma once
#include "./ZY_Engine/Node.h"
#include "MonsterFactory.h"
#include "./AABB/MersenneTwister.h"
class MonsterBulider
{
    MersenneTwister _rand;
    std::vector<MonsterFactory*> _factorys;
    float _refreshTime = 0.2f;
    float _timer = 0;
    int _maxRate = 500;
    int _nowRate = 10;
    bool _isPause = true;
    int _maxOnceSum = 5;
    int _maxAllSum = 30;
    Camera* _camera;
    int _lastDeadSum = 0;
    int _boosApparSum = 30;
    int _monsterUpSum = 50;
    float _strongRate = 1.f;
public:
    std::vector<BlockSprite*> getMonsters(float dt);
    void setRate(int r) { _nowRate = r; }
    void setMaxRate(int r) { _maxRate = r; }
    void setMaxOnceTime(int m) { _maxOnceSum = m; }
    void setBossSum(int b) { _boosApparSum = b; }
    void setMaxAllSum(int m) { _maxAllSum = m; }
    void setMonsterUpSum(int s) { _monsterUpSum = s; }
    void addFectory(MonsterFactory* f) { _factorys.push_back(f); }
    void setStrongRate(float r) { _strongRate = r; }
    void strongMonster(BlockSprite* m);
    void release();
    void setCamera(Camera* c) { _camera = c; }
    void setPause(bool p) { _isPause = p; }
    bool getBoss();
};

