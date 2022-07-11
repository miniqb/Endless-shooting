#pragma once
#include "Bullet.h"
#include "../AABB/MersenneTwister.h"
#include "bulletFactor.h"

struct WeaponsInfo
{
	int _power = 2;//伤害
	float _cooling = 0.8;//冷却
	float _speedLen = 500.f;//速度
	float _stable = 0.001;//稳定性
	int _onceSum = 1;//单发数量
};
class Weapons:public Node
{
public:
	Weapons();
	~Weapons();
	void init(T_Graph* g, BulletFactor* pool);
public:
	vector<Bullet*> fire();
	void init(const WeaponsInfo& info);
	virtual void updateSelf(float dt)override;
	virtual void drawSelf(HDC hdc)override;
	int getPower() { return _power; }
	
	void setPower(int p) { _power = p; }
	void setCooling(float c) { _cooling = c; }
	void setBulletFactor(BulletFactor* f);
	BulletFactor* getBulletFactor() { return _factor; }
	void setOnceSum(int s) { _onceSum = s; }
	void releaseBulletFactor();
	static void initCamera(Camera* c);
private:
	MersenneTwister _rand;
	//伤害
	int _power;

	//冷却时间
	float _cooling;
	//计时器
	float _timing;

	//初始子弹速度大小
	float _speedLen;

	//子弹稳定性
	float _stable;

	//一次发射子弹数
	int _onceSum;

	//武器图片
	T_Graph* _graph;

	//子弹工场
	BulletFactor* _factor;

	int _bulletSum;
	//camera缓存，提高访问速度
	static Camera* camera;
};

//手枪
class WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//左轮
class RevolverFactor:public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//步枪
class RifleFactor :public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//霰弹
class ShotgunFactor :public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//
class BossFactor :public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};