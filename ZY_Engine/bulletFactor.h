#pragma once
#include "Bullet.h"

class BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new BulletFactor(); }
};

//爆炸弹工厂
class BoomBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new BoomBulletFactor(); }
};

//导弹工厂
class TrackBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new TrackBulletFactor(); }

};

//贯穿弹工厂
class ThourthBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new ThourthBulletFactor(); }

};

//反射弹工厂
class ReboundBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new ReboundBulletFactor(); }

};

//敌人子弹工厂
class NpcBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new NpcBulletFactor(); }
};