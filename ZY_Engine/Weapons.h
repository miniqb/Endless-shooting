#pragma once
#include "Bullet.h"
#include "../AABB/MersenneTwister.h"
#include "bulletFactor.h"

struct WeaponsInfo
{
	int _power = 2;//�˺�
	float _cooling = 0.8;//��ȴ
	float _speedLen = 500.f;//�ٶ�
	float _stable = 0.001;//�ȶ���
	int _onceSum = 1;//��������
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
	//�˺�
	int _power;

	//��ȴʱ��
	float _cooling;
	//��ʱ��
	float _timing;

	//��ʼ�ӵ��ٶȴ�С
	float _speedLen;

	//�ӵ��ȶ���
	float _stable;

	//һ�η����ӵ���
	int _onceSum;

	//����ͼƬ
	T_Graph* _graph;

	//�ӵ�����
	BulletFactor* _factor;

	int _bulletSum;
	//camera���棬��߷����ٶ�
	static Camera* camera;
};

//��ǹ
class WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//����
class RevolverFactor:public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//��ǹ
class RifleFactor :public WeaponsFactor
{
public:
	virtual Weapons* getWeapons();
};

//����
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