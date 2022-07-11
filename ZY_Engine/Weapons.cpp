#include "Weapons.h"

Weapons::Weapons():
	Node(),
	_power(0),
	_cooling(0.2),
	_timing(0),
	_graph(nullptr),
	_speedLen(1800),
	_stable(0.0001),
	_factor(nullptr),
	_onceSum(0)
{
	_anchorPoint.set(0, 0.5f);
}

Weapons::~Weapons()
{
	if (_factor)
		delete _factor;
}

void Weapons::init(T_Graph* g, BulletFactor* f)
{
	_graph = g;
	this->setContentSize(ZY_Size(g->GetImageWidth(), g->GetImageHeight()));
	this->_factor = f;
}

std::vector<Bullet*> Weapons::fire()
{
	Bullet* bullet = nullptr;
	vector<Bullet*> bullets(_onceSum);
	if (_factor&& _timing <= 0)
	{
		_timing = _cooling;
		for (int i = 0; i < _onceSum; ++i)
		{
			bullet = _factor->getBullet();
			if (bullet)
			{
				Vec2 mPos = Vec2::forAngle(_rotation + _rand.normal(0, _stable));
				bullet->setSpeed(mPos*_speedLen);
				float width = this->getContentSize().width;
				Vec2 fPos = Vec2::forAngle(_rotation) * width;
				bullet->setPosition(fPos + this->getTransPosition());
				bullet->addCollisionBody(1,false,false);
				bullet->setPower(_power);
			}
			bullets[i] = bullet;
		}
		sound::shoot.play();
	}

	return bullets;
}

void Weapons::init(const WeaponsInfo& info)
{
	_power = info._power;
	_cooling = info._cooling;
	_speedLen = info._speedLen;
	_stable = info._stable;
	_onceSum = info._onceSum;
}

void Weapons::updateSelf(float dt)
{
	if (_timing > 0)
		_timing-=dt;
}

void Weapons::drawSelf(HDC hdc)
{
	//Vec2 pos=
	Vec2 pos = getTransPosition() - camera->getTransRect().origin;
	int type = TRANS_NONE;
	float r = M_PI * 0.5;
	if (_rotation > r || _rotation < -r)
		type = TRANS_VFLIP_NOROT;
	ZY_Graph::PaintRegion(_graph->GetBmpHandle(), hdc, pos, 0, 0, _graph->GetImageWidth(), _graph->GetImageHeight(), _scaleX, _scaleY, _rotation, _anchorPoint, type);
}

void Weapons::setBulletFactor(BulletFactor* f)
{
	releaseBulletFactor();
	_factor = f;
}

void Weapons::releaseBulletFactor()
{
	if (_factor)
	{
		delete _factor;
		_factor = nullptr;
	}
}

void Weapons::initCamera(Camera* c)
{
	camera = c;
}

//camera缓存，提高访问速度
Camera* Weapons::camera = nullptr;

//手枪
Weapons* WeaponsFactor::getWeapons()
{
	Weapons* weapon = new Weapons;
	weapon->init(&GunGraphs::pistol, new BulletFactor());
	weapon->setScale(0.6, 0.6);
	WeaponsInfo info;
	info._power = 2;//伤害
	info._cooling = 0.4;//冷却
	info._speedLen = 500.f;//速度
	info._stable = 0.001;//稳定性
	info._onceSum = 1;//单发数量

	weapon->init(info);
	weapon->setPosition(Vec2(0, 10));
	return weapon;
}

//初始化左轮
Weapons* RevolverFactor::getWeapons()
{
	Weapons* weapon = new Weapons;
	weapon->init(&GunGraphs::revolver, new BulletFactor());

	WeaponsInfo info;
	info._power = 24;//伤害
	info._cooling = 0.8;//冷却
	info._speedLen = 700.f;//速度
	info._stable = 0.08;//稳定性
	info._onceSum = 1;//单发数量

	weapon->init(info);
	weapon->setPosition(Vec2(0, 10));
	return weapon;
}

//步枪
Weapons* RifleFactor::getWeapons()
{
	Weapons* weapon = new Weapons;
	weapon->init(&GunGraphs::rifle, new BulletFactor());
	weapon->setScale(0.5, 0.5);
	WeaponsInfo info;
	info._power = 2;//伤害
	info._cooling = 0.1;//冷却
	info._speedLen = 600.f;//速度
	info._stable = 0.1;//稳定性
	info._onceSum = 1;//单发数量

	weapon->init(info);
	weapon->setPosition(Vec2(0, 10));
	return weapon;
}

//霰弹
Weapons* ShotgunFactor::getWeapons()
{
	Weapons* weapon = new Weapons;
	weapon->init(&GunGraphs::shotgun, new BulletFactor());
	weapon->setScale(0.5, 0.5);
	WeaponsInfo info;
	info._power = 3;//伤害
	info._cooling = 1;//冷却
	info._speedLen = 800.f;//速度
	info._stable = 0.3;//稳定性
	info._onceSum = 7;//单发数量
	weapon->setPosition(Vec2(0, 10));
	weapon->init(info);
	return weapon;
}

//
Weapons* BossFactor::getWeapons()
{
	Weapons* weapon = new Weapons;
	weapon->init(&GunGraphs::boss, new BulletFactor());
	weapon->setScale(0.5, 0.5);
	WeaponsInfo info;
	info._power = 1;//伤害
	info._cooling = 0.2;//冷却
	info._speedLen = 1200.f;//速度
	info._stable = 0.2;//稳定性
	info._onceSum = 3;//单发数量
	weapon->setPosition(Vec2(0, 10));
	weapon->init(info);
	return weapon;
}