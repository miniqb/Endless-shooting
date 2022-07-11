#include "MonsterBulider.h"

std::vector<BlockSprite*> MonsterBulider::getMonsters(float dt)
{
    std::vector<BlockSprite*> monsters;
    if (!_isPause)
    {
        _timer += dt;
        if (_timer >= _refreshTime)
        {
            _timer = 0;
            int size = _factorys.size();
            if (size > 0)
            {
                int deadSum = BlockSprite::getMonsterSum();
                int cj = max(_maxAllSum - deadSum, 0);
                int sum = min(cj, _maxOnceSum);
                for (size_t i = 0; i < sum; i++)
                {
                   // float upRaate = 1 + ((float)cj / (float)_maxOnceSum);
                    int upRate = min(_maxRate, deadSum / _monsterUpSum);
                    if (_rand.integer(0, _maxRate- upRate) < _nowRate)
                    {
                        BlockSprite* m = _factorys[_rand.integer(0, size - 1)]->getMonster();
                        if (getBoss())   m->strongSelf();
                        strongMonster(m);
                        monsters.push_back(m);

                        if (m->canFly())
                        {
                            Vec2 pos;
                            int minx = -50;
                            int maxx = zyvar::worldSize.width + 50;
                            int miny = -50;
                            int maxy = zyvar::worldSize.height + 50;
                            pos.x = _rand.integer(minx, maxx);
                            pos.y= _rand.integer(miny, maxy);
                            ZY_Rect rect = _camera->getTransRect();
                            m->setPosition(pos);
                            ZY_Rect mRect = m->getTransRect();
                            while (rect.intersectsRect(mRect))
                            {
                                pos.x = _rand.integer(minx, maxx);
                                pos.y = _rand.integer(miny, maxy);
                                m->setPosition(pos);
                                mRect = m->getTransRect();
                            }
                        }
                        else
                        {
                            Vec2 pos;
                            ZY_Size mSize = m->getTransRect().size;
                            mSize = mSize* 0.5;
                            int minx = 32 + mSize.width;
                            int maxx = zyvar::worldSize.width - 32 + mSize.width;
                            int miny = 32 + mSize.height;
                            int maxy = zyvar::worldSize.height - 32 + mSize.height;
                            pos.x = _rand.integer(minx, maxx);
                            pos.y = _rand.integer(miny, maxy);
                            m->setPosition(pos);
                            ZY_Rect mRect = m->getTransRect();
                            ZY_Rect rect = _camera->getTransRect();
                            while (rect.intersectsRect(mRect)||MapCollision::TestMapCollision(zyvar::tMap,mRect,zyvar::obstacles))
                            {
                                pos.x = _rand.integer(minx, maxx);
                                pos.y = _rand.integer(miny, maxy);
                                m->setPosition(pos);
                                mRect = m->getTransRect();
                            }
                        }
                    }
                }
            }
        }
    }
    return monsters;
}

void MonsterBulider::strongMonster(BlockSprite* m)
{
    m->setHealth(m->getHealth() * _strongRate);
}

void MonsterBulider::release()
{
    int length = _factorys.size();
    for (size_t i = 0; i < length; i++)
    {
        delete _factorys[i];
    }
}

bool MonsterBulider::getBoss()
{
    if (BlockSprite::getDeadSum() >= _boosApparSum + _lastDeadSum)
    {
        _lastDeadSum = BlockSprite::getDeadSum();
        return true;
    }
    return false;
}
