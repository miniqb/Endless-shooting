#pragma once
#include "Bullet.h"

class BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new BulletFactor(); }
};

//��ը������
class BoomBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new BoomBulletFactor(); }
};

//��������
class TrackBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new TrackBulletFactor(); }

};

//�ᴩ������
class ThourthBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new ThourthBulletFactor(); }

};

//���䵯����
class ReboundBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new ReboundBulletFactor(); }

};

//�����ӵ�����
class NpcBulletFactor :public BulletFactor
{
public:
	virtual Bullet* getBullet();
	virtual BulletFactor* clon() { return new NpcBulletFactor(); }
};