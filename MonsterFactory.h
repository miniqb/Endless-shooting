#pragma once
#include "BlockSprite.h"
class MonsterFactory
{
protected:
	MersenneTwister _rander;
public:
	virtual BlockSprite* getMonster() = 0;
};

class BatFactory:public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class BirdFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class CdragonFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class ChickenFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class CowFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class DeathFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class DragonFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class Dragon2Factory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class FireFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class GostFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class LizardFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class MummyFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class SkeletonFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class SnakeFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class StoneFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class VampireFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class WolfFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};

class ZombiesFactory :public MonsterFactory
{
public:
	virtual BlockSprite* getMonster();
};