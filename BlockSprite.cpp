#include "BlockSprite.h"
#include "./ZY_Engine/Bullet.h"
#include "./ZY_Engine/bulletFactor.h"
#include "Props.h"
int BlockSprite::monsterSum = 0;
int BlockSprite::deadMonsterSum = 0;

int BlockSprite::getMonsterSum()
{
	return monsterSum;
}
int BlockSprite::getDeadSum()
{
	return deadMonsterSum;
}
void BlockSprite::setMonsterSum(int s)
{
	monsterSum = s;
}
void BlockSprite::setDeadSum(int s)
{
	deadMonsterSum = s;
}

BlockSprite::BlockSprite():
	_collPower(0),
	_speed(),
	_speedLen(),
	_dir(0),
	_rand(),
	_health(0),
	_isInvincible(false),
	_isSpeedUp(false),
	_speedUpRate(0),
	_collVec(),
	_isFendOff(false),
	_fendOffTimer(0),
	_fendOffTime(0),
	_fendOffSed(),
	_canFly(false),
	_action(nullptr),
	_fendOffTimePower(0),
	_fendOffSedPower(0),
	_againstFendRate(0),
	Sprite()
{
	for (size_t i = 0; i <3; i++)
	{
		_powers[i] = nullptr;
	}
	_tag = LAYER_NPC;
	++monsterSum;
}

BlockSprite::BlockSprite(ZY_Animation* an):
	_collPower(0),
	_speed(),
	_speedLen(),
	_dir(0),
	_rand(),
	_health(0),
	_isInvincible(false),
	_isSpeedUp(false),
	_speedUpRate(0),
	_collVec(),
	_isFendOff(false),
	_fendOffTimer(0),
	_fendOffTime(0),
	_fendOffSed(),
	_canFly(false),
	_action(nullptr),
	_fendOffTimePower(0),
	_fendOffSedPower(0),
	_againstFendRate(0),
	Sprite(an)
{
	for (size_t i = 0; i < 3; i++)
	{
		_powers[i] = nullptr;
	}
	_tag = LAYER_NPC;
	++monsterSum;
}
BlockSprite::~BlockSprite()
{
	if (_action)
		delete _action;
	for (size_t i = 0; i < 3; i++)
	{
		if (_powers[i])
			delete _powers[i];
	}
	--monsterSum;
}
void BlockSprite::initMonster(const MonsterInfo& info)
{
	//击退抗性
	_againstFendRate = info._againstFendRate;
	//碰撞伤害
	_collPower = info._collPower;
	//速度大小
	_speedLen = info._speedLen;
	//生命值
	_health = info._health;

	_speedUpRate = info._speedUpRate;
	for (size_t i = 0; i < 3; i++)
	{
		_powers[i] = info.powers[i];
		if(_powers[i])
			_powers[i]->setUser(this);
	}
	_action = info.action;
	//是否可飞行
	_canFly = info._canFly;
	_fendOffSedPower = info._fendOffSed;
	_fendOffTimePower = info._fendOffTime;
	_tag = info._tag;
}
bool BlockSprite::collisionFuntion(Node* node)
{
	if (node->isAlive())
	{
		int tag = node->getTag();

		switch (tag)
		{
		case LAYER_PLY://碰到子弹会掉血
		{
			Vec2 pPos = player->getTransPosition();
			Vec2 cVec = pPos - this->getTransPosition();
			if (cVec.isZero())
				cVec = Vec2::forAngle(_rand.normal() * M_PI);
			else
				cVec.normalize();
			player->setFendOff(true, cVec * _fendOffSedPower, _fendOffTimePower);
			player->getHurt(_collPower);
		}
		break;
		default:
			break;
		}
	}
	return true;
}

void BlockSprite::_updateSelf(float dt)
{
	//如果死亡就去掉碰撞体积
	if (_collisionBody && _health <= 0)
	{
		delete _collisionBody;
		_collisionBody = nullptr;
	}
	
	//备份初始位置
	Vec2 resPos = this->getTransPosition();

	if (_isFendOff)//如果被击退
	{
		_fendOffTimer += dt;
		if (_fendOffTimer >= _fendOffTime)
		{
			_isFendOff = false;
		}
		_collVec += _fendOffSed * dt;
		this->addPosition(_collVec);

		if (!_canFly &&MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles))
		{
			this->setPosition(resPos);
		}
		_collVec.setZero();
		return;
	}

	//技能更新
	if (_health > 0)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (_powers[i])
			{
				if (!_powers[i]->updateByMonster(dt))
				{
					return;
				}
			}
		}
	}

	//行为更新
	if (_action) _action->update(dt, this, player);

	//位置更新
	_speed *= dt;
	if (_isSpeedUp)
		_speed *= _speedUpRate;
	ZY_Rect rect = this->getTransRect();
	rect.origin.x += _speed.x;
	if (!_canFly && MapCollision::TestMapCollision(zyvar::tMap, rect, zyvar::obstacles))
	{
		rect.origin.x -= _speed.x;
		_speed.x = 0;
	}
	rect.origin.y += _speed.y;
	if (!_canFly && MapCollision::TestMapCollision(zyvar::tMap, rect, zyvar::obstacles))
	{
		_speed.y = 0;
	}
	this->addPosition(_speed);

	judgeDir();
	_animation->setIndexY(_dir);
}

void BlockSprite::getHurt(int hurt)
{
	if (_health > 0) 
	{
		_health -= hurt;
		if (_health <= 0)
		{
			++deadMonsterSum;
			sound::monsterDead.play();
			DeadAction* act = new DeadAction();
			if (_action)
				delete _action;
			_action = act;
			_complexDraw = true;
			_speed.setZero();
			lostProp();
		}
	}
}

void BlockSprite::lostProp()
{
	if (_rand.integer(0, 100)<10)
	{
		Props* prop = nullptr;
		if (_rand.integer(0,8))
		{
			prop = PropsFactor::bulletProp[_rand.integer(0, 3)]->getProps();
		}
		else
		{
			prop = PropsFactor::weaponsProp[_rand.integer(0, 3)]->getProps();
		}
		_parent->addChild(prop);
		prop->setPosition(this->getTransPosition());
		prop->addCollisionBody(0, false, false);
	}
}

void BlockSprite::setPlayer(BlockSprite* p)
{
	player = p;
}

void BlockSprite::strongSelf()
{
	//击退抗性
	_againstFendRate = 1;
	//碰撞伤害
	_collPower *= 1.5;
	//生命值
	_health *= 10;
	this->setScale(3, 3);
}

void BlockSprite::judgeDir()
{
	float fx = fabsf(_speed.x);
	float fy = fabsf(_speed.y);
	if (fx < fy)
	{
		if (_speed.y > 0)
			_dir = DIR_DOWN;
		else if (_speed.y < 0)
			_dir = DIR_UP;
	}
	else if(fx > fy)
	{
		if (_speed.x > 0)
			_dir = DIR_RIGHT;
		else if (_speed.x < 0)
			_dir = DIR_LEFT;
	}
}

void BlockSprite::setFendOff(bool f, const Vec2& _fendSp, float _fendTime)
{
	if (!_isInvincible)
	{
		_isFendOff = f;
		_fendOffSed = _fendSp;
		_fendOffTime = _fendTime * (1.f - _againstFendRate);
		_fendOffTimer = 0;
	}
}

bool FastMovE::updateByPlayer(float dt)
{
	//加速进行
	if (_user->isSpeedUp())
	{
		_speedTimer += dt;
		if (_speedTimer > _speedUpTime)
		{
			_user->setInvincible(false);
			_user->setSpeedUp(false);
			_timer = 0;
		}
	}

	//技能冷却
	if (_timer < _cooling)
		_timer += dt;
	if (_timer >= _cooling)
	{
		if (zyvar::keyChars[_key])
		{
			_user->setInvincible(true);
			_user->setSpeedUp(true);
			sound::speedUp.Restore();
			sound::speedUp.Play();
			_speedTimer = 0;
		}
	}
	return true;
}
bool FastMovE::updateByMonster(float dt)
{
	//加速进行
	if (_user->isSpeedUp())
	{
		_speedTimer += dt;
		if (_speedTimer > _speedUpTime)
		{
			_user->setSpeedUp(false);
			_timer = 0;
		}
		return true;
	}

	//技能冷却
	if (_timer < _cooling)
		_timer += dt;
	if (_timer >= _cooling)
	{
		_user->setSpeedUp(true);
		_speedTimer = 0;
	}
	return true;
}
void FastMovE::initSkill(float st, float cool)
{
	_speedUpTime = st;
	_cooling = cool;
	_speedTimer = 0;
	_timer = 0;
}

bool BodySlaM::updateByPlayer(float dt)
{
	bool res = true;
	//位移进行
	if (_salmTimer < _slaTime)
	{
		_salmTimer += dt;
		Vec2 resPos = _user->getTransPosition();
		_user->addPosition(_onceMove * dt);
		if (MapCollision::TestMapCollision(zyvar::tMap, _user->getTransRect(), zyvar::obstacles))
		{
			_user->setPosition(resPos);
		}
		if (_salmTimer >= _slaTime)
		{
			_timer = 0;
			_inTimer = 0;
			CrackBoom boomFactor;
			BoomSprite* boom = boomFactor.getBoom(_user->getTransPosition());
			_user->getParent()->addChild(boom);
			//下面代码产生爆炸
		}
		return false;
	}

	//技能冷却
	if (_timer < _cooling)
		_timer += dt;
	if (_timer >= _cooling && zyvar::keyChars[_key])
	{
		Vec2 aimPos(zyvar::mousePos.x, zyvar::mousePos.y);
		aimPos+= Sprite::getCamera()->getTransRect().origin;
		Vec2 myPos = _user->getTransPosition();
		Vec2 moveVec = aimPos - myPos;
		float len = moveVec.lengthSquared();
		if (len <= _allMoveLen * _allMoveLen*_user->getScaleX()*_user->getScaleY())
		{
			_onceMove = moveVec / _slaTime;
		}
		else
		{
			_onceMove = moveVec.getNormalized() * _allMoveLen / _slaTime;
		}
		_user->setInvincible(true);
		_salmTimer = 0;
		_timer = 0;
	}

	if (_inTimer < _inTime)//技能结束后多点无敌时间
	{
		_inTimer += dt;
		if(_inTimer>=_inTime)
			_user->setInvincible(false);
	}

	return true;
}
bool BodySlaM::updateByMonster(float dt)
{
	//位移进行
	if (_salmTimer < _allMoveTime)
	{
		_salmTimer += dt;
		if (_salmTimer <= _xuli&&_salmTimer+dt>=_xuli)
		{
			Vec2 playerPos = BlockSprite::player->getTransPosition();
			Vec2 userPos = _user->getTransPosition();
			Vec2 moveVec = playerPos - userPos;
				_onceMove = moveVec / _slaTime;
				_user->setInvincible(true);
		}
		else if (_salmTimer>_xuli)
		{
			Vec2 resPos = _user->getTransPosition();
			_user->addPosition(_onceMove * dt);
			if (!_user->canFly()&& MapCollision::TestMapCollision(zyvar::tMap, _user->getTransRect(), zyvar::obstacles))
			{
				_user->setPosition(resPos);
			}
			if (_salmTimer >= _allMoveTime)//结束时爆炸
			{
				_timer = 0;
				_user->setInvincible(false);
				CrackBoom boomFactor;
				BoomSprite* boom = boomFactor.getBoom(_user->getTransPosition(), 0);
				boom->setScale(_user->getScaleX(), _user->getScaleY());
				boom->setPower(4);
				_user->getParent()->addChild(boom);
				//下面代码产生爆炸
			}
		}
		return false;
	}

	//技能冷却
	if (_timer < _cooling)
		_timer += dt;
	if (_timer >= _cooling)
	{
		Vec2 playerPos = BlockSprite::player->getTransPosition();
		Vec2 userPos = _user->getTransPosition();
		Vec2 moveVec = playerPos - userPos;
		float len = moveVec.lengthSquared();
		if (len * 0.8 <= double(_allMoveLen) * double(_allMoveLen))
		{
			_salmTimer = 0;
		}
	}
	return true;
}


void BodySlaM::initSkill(const BodySlaMInfo& info)
{
	_onceMove.setZero();
	_allMoveLen = info._allMoveLen;
	_slaTime = info._slaTime;
	_xuli = info._xuli;
	_allMoveTime = _slaTime + _xuli;
	_salmTimer = _allMoveTime+1.f;
	_cooling = info._cooling;
}

void BodySlaM::setMove(float s, float l)
{
	_slaTime = s;
	_allMoveLen = l;
}

void LinearMove::update(float dt, BlockSprite* user, BlockSprite* aim)
{
	if (aim)
	{
		Vec2 cVec = aim->getTransPosition() - user->getTransPosition();
		cVec.normalize();
		cVec *= user->getSpeedLen();
		user->setSpeed(cVec);
	}

}

void CurveMove::update(float dt, BlockSprite* user, BlockSprite* aim)
{
	Vec2 myPos = user->getTransPosition();
	Vec2 aimPos = aim->getTransPosition();
	Vec2 cVec = aimPos - myPos;
	float cLen = cVec.getLengthSq();
	Vec2 spd;
	if (cLen>=10000.f||cLen<160000.f)
	{
		spd = cVec.rotateByAngle(Vec2::ZERO, M_PI * 0.33f);
		spd.normalize();
		spd *= user->getSpeedLen();
	}
	else
	{
		spd = cVec.getNormalized();
		spd *= user->getSpeedLen();
	}
	user->setSpeed(spd);
}

BlockSprite* BlockSprite::player;

void DeadAction::update(float dt, BlockSprite* user, BlockSprite* aim)
{
	_timer += dt;
	if (_timer < _fullTime)
	{
		float rf;
		if (_fdir)
			rf = (_timer / _fullTime) * M_PI / 2.f;
		else
		{
			rf = -(_timer / _fullTime) * M_PI / 2.f;
		}
		user->setRotation(rf);
	}
	else if (_timer < _fullTime + _disTime)
	{
		user->addAlpha(-255 * dt / _disTime);
	}
	else
	{
		user->setAlive(false);
	}


}

DeadAction::DeadAction()
{
	if (rand() % 2)
		_fdir = true;
	else
	{
		_fdir = false;
	}
}

bool FireSkill::updateByMonster(float dt)
{
	//技能冷却
	if (_timer < _cooling)
		_timer += dt;
	if (_timer >= _cooling)
	{
		_timer = 0;
		NpcBulletFactor factor;
		Bullet* but = factor.getBullet();
		but->setPosition(_user->getTransPosition());
		Vec2 cVec = BlockSprite::player->getTransPosition() - _user->getTransPosition();
		cVec.normalize();
		cVec *= _fireSpeed;
		but->setSpeed(cVec);
		but->setScale(_user->getScaleX(), _user->getScaleY());
		but->addCollisionBody(0, false, false);
		_user->getParent()->addChild(but);
	}
	return true;
}
