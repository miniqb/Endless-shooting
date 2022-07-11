#include "PlayerSprite.h"
#include "./ZY_Engine/Scene.h"

PlayerSprite::PlayerSprite() :
	_helpTimer ( 0),
	_helpTime(2),
	_maxHealth(6),
	_weapons(nullptr),
	_helpFlash(0.1f),
	_helpFlashTimer(0),
	BlockSprite()
{
	_health = 6;
	_tag = LAYER_PLY;
}

PlayerSprite::PlayerSprite(ZY_Animation* an) :
	_helpTimer(0),
	_helpTime(2),
	_maxHealth(6),
	_weapons(nullptr),
	_helpFlash(0.1f),
	_bloodReturnTimer(0),
	_bloodReturnTime(1000),
	BlockSprite(an)
{
	_health = 6;
	_tag = LAYER_PLY;
}

void PlayerSprite::initBlood(const wstring& str)
{
	_bloodHearts = new BloodHearts();
	_bloodHearts->setGraph(str);
	((Scene*)(this->_parent))->addSurfaceNode(_bloodHearts);
	_bloodHearts->setMaxHealth(6);
	_bloodHearts->setHealth(6);
	_health = 6;
	_maxHealth = 6;
}

bool PlayerSprite::collisionFuntion(Node* node)
{
	int tag = node->getTag();

	switch (tag)
	{
	case LAYER_PLY_BOMB://碰到子弹会掉血
	{
		int hurt = ((Bullet*)node)->getPower();
		this->getHurt(hurt);
	}
	case LAYER_EXPLOSION://碰到爆炸会掉血和击退
	{
		BoomSprite* boom = ((BoomSprite*)node);
		int hurt = boom->getPower();
		this->getHurt(hurt);
		float fendOfftime = boom->getFendOffTime();
		if (fendOfftime > 0)
		{
			float fendOffSpd = boom->getFendOffSpd();
			Vec2 cVec = this->getTransPosition() - boom->getTransPosition();
			cVec.normalize();
			this->setFendOff(true, cVec * fendOffSpd, fendOfftime);
		}
	}
	default:
		break;
	}
	return true;
}

void PlayerSprite::_updateSelf(float dt)
{
	if (_helpTimer < _helpTime)//是否处于无敌时间
	{
		_helpTimer += dt;
		_helpFlashTimer += dt;
		if (_helpFlashTimer > _helpFlash)
		{
			_visible = !_visible;
			_helpFlashTimer = 0;
		}
	}
	else
	{
		_visible = true;
	}
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
		if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles))
		{
			this->setPosition(resPos);
		}
		
		_collVec.setZero();

		return;
	}

	if (_health > 0)
	{
		//回血
		bloodReturnUpdate(dt);
		//技能更新
		for (size_t i = 0; i < 3; ++i)
		{
			if (_powers[i])
			{
				if (!_powers[i]->updateByPlayer(dt))
					return;
			}
		}

		handleInput(dt);

		if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles))
		{
			this->setPosition(resPos);
		}

		//处理人物朝向和枪械朝向
		judgeDir();

		if (MOUSE_DOWN(VK_LBUTTON))
		{
			vector< Bullet*> buts = _weapons->fire();
			unsigned int length = buts.size();
			for (size_t i = 0; i < length; i++)
			{
				if (buts[i])
				{
					_parent->addChild(buts[i]);
				}
			}
		}
		_animation->setIndexY(_dir);
	}
	else
	{
		_deadAction.update(dt, this, nullptr);
	}
}

void PlayerSprite::getHurt(int hurt)
{
	if (!_isInvincible)
	{
		if (_helpTimer >= _helpTime)
		{
			_complexDraw = true;
			_health -= hurt;
			_bloodHearts->setHealth(max(0, _health));
			_helpTimer = 0;
			this->resetBullet();
			sound::playerHurt.Restore();
			sound::playerHurt.Play();
		}
	}
}

void PlayerSprite::bloodReturnUpdate(float dt)
{
	if(_bloodReturnTimer< _bloodReturnTime)
		_bloodReturnTimer += dt;
	if (_bloodReturnTimer >= _bloodReturnTime)
	{
		_bloodReturnTimer = 0;
		if (_health < _maxHealth)
		{
			_health++;
			_bloodHearts->setHealth(_health);
		}
	}
}

void PlayerSprite::judgeDir()
{
	Vec2 mPos(zyvar::mousePos.x, zyvar::mousePos.y);
	mPos += camera->getTransRect().origin;
	mPos -= this->getTransPosition();
	float r = mPos.getAngle();
	_weapons->setRotation(r);

	float fx = fabsf(mPos.x);
	float fy = fabsf(mPos.y);
	if (fx < fy)
	{
		if (mPos.y > 0)
			_dir = DIR_DOWN;
		else if (mPos.y < 0)
			_dir = DIR_UP;
	}
	else if (fx > fy)
	{
		if (mPos.x > 0)
			_dir = DIR_RIGHT;
		else if (mPos.x < 0)
			_dir = DIR_LEFT;
	}
}

void PlayerSprite::handleInput(float dt)
{
	float len = _speedLen * dt;
	if (_isSpeedUp)
	{
		len *= _speedUpRate;
	}
	bool moveFlag = false;
	Vec2 moveVec;
	if (zyvar::keyChars['W'])
	{
		moveVec.y -= len;
		moveFlag = true;
	}
	if (zyvar::keyChars['S'])
	{
		moveVec.y += len;
		moveFlag = true;
	}
	if (zyvar::keyChars['A'])
	{
		moveVec.x -= len;
		moveFlag = true;
	}
	if (zyvar::keyChars['D'])
	{
		moveVec.x += len;
		moveFlag = true;
	}

	if (!moveVec.isZero())
	{
		moveVec.normalize();
		moveVec *= len;
		this->addPosition(moveVec);
	}

	if (moveFlag)
	{
		sound::playerRun.Restore();
		sound::playerRun.Play();
	}
	else
	{
		sound::playerRun.Stop();
	}
	_animation->pause(!moveFlag);
}

void PlayerSprite::addMaxHealth(int h)
{
	_maxHealth += h;
	_bloodHearts->setMaxHealth(_maxHealth);
}

void PlayerSprite::setMaxHealth(int h)
{
	_maxHealth = h;
	_bloodHearts->setMaxHealth(_maxHealth);
}

void PlayerSprite::setHealth(int h)
{
	if (h > _maxHealth)
	{
		_health = _maxHealth;
	}
	else
	{
		_health = h;
	}
	_bloodHearts->setHealth(_health);
}

void PlayerSprite::setFullHealth()
{
	_health = _maxHealth;
	_bloodHearts->setHealth(_health);
}

void PlayerSprite::setWeapons(Weapons* w)
{
	if (_weapons)
		_weapons->setVisible(false);
	_weapons = w;
	this->addChild(_weapons);
}

void PlayerSprite::changeWeapons(Weapons* w)
{
	if (_weapons)
	{
		BulletFactor* oldFactor = _weapons->getBulletFactor();
		BulletFactor* newFactor = oldFactor->clon();
		_weapons->setAlive(false);
		w->setBulletFactor(newFactor);
		_weapons = w;
		this->addChild(w);
	}
}

void PlayerSprite::changeBullet(BulletFactor* bf)
{
	if (_weapons)
	{
		_weapons->setBulletFactor(bf);
	}
}

void PlayerSprite::resetBullet()
{
	if (_weapons)
	{
		_weapons->setBulletFactor(new BulletFactor());
	}
}

void PlayerSprite::setFendOff(bool f, const Vec2& _fendSp, float _fendTime)
{
	if (!_isInvincible&& _helpTimer >= _helpTime)
	{
		BlockSprite::setFendOff(f, _fendSp, _fendTime);
	}
}

void PlayerDead::update(float dt, BlockSprite* user, BlockSprite* aim)
{
	if (_timer < _fullTime)
	{
		_timer += dt;
		float rf;
		if (_fdir)
			rf = (_timer / _fullTime) * M_PI / 2.f;
		else
		{
			rf = -(_timer / _fullTime) * M_PI / 2.f;
		}
		user->setRotation(rf);
	}
}
