#include "Bullet.h"
#include <float.h>
#include "../BlockSprite.h"

Bullet::Bullet():
	Sprite(),
	_speed(),
	_basisPower(0),
	_gunPower(0),
	_penetration(0),
	_surviveTime(999),
	_lastHit(nullptr)
{
}

Bullet::Bullet(ZY_Animation* an):
	Sprite(),
	_speed(),
	_basisPower(0),
	_gunPower(0),
	_penetration(0),
	_surviveTime(999),
	_lastHit(nullptr)
{
	init(an);
}

//ͨ����
bool Bullet::collisionFuntion(Node* node)
{
	int tag = node->getTag();
	if (_alive && (tag == LAYER_NPC || tag == LAYER_BOSS ||tag==LAYER_PLY)&& _lastHit != node)
	{
		((BlockSprite*)(node))->getHurt(this->getPower());
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		((BlockSprite*)node)->getHurt(this->getPower());
		_lastHit = node;
		if ((--_penetration) < 0)
		{
			this->setAlive(false);
			return false;
		}
	}
	return true;
}
//ͨ����
void Bullet::_updateSelf(float dt)
{
	this->addPosition(_speed * dt);

	_surviveTime -= dt;

	if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles) || _surviveTime < 0)
	{
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		this->setAlive(false);
	}

}

void Bullet::initBullet(const bulletInfo& info)
{
	_animation = info._ain;
	_basisPower = info._basisPower;
	_penetration = info._penetration;
	_surviveTime = info._surviveTime;
	_speedRate = info._speedRate;
	_tag = info._tag;
	_alive = true;
	_active = true;
	_lastHit = nullptr;
}

Bullet::~Bullet()
{
}

void Bullet::setSpeed(const Vec2& sp)
{
	_speed = sp * _speedRate;
	_speedLen = _speed.length();
}

//��ը��
bool BoomBullet::collisionFuntion(Node* node)
{
	int tag = node->getTag();
	if (_alive && (tag == LAYER_NPC || tag == LAYER_BOSS || tag == LAYER_PLY) && _lastHit != node)
	{
		((BlockSprite*)(node))->getHurt(this->getPower());
		FireBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		((BlockSprite*)node)->getHurt(this->getPower());
		_lastHit = node;
		if ((--_penetration) < 0)
		{
			this->setAlive(false);
			return false;
		}
	}
	return true;
}

//��ը��
void BoomBullet::_updateSelf(float dt)
{
	this->addPosition(_speed * dt);

	_surviveTime -= dt;

	if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles) || _surviveTime < 0)
	{
		FireBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		this->setAlive(false);
	}
}

//����
void TrackBullet::_updateSelf(float dt)
{
	//����
	if (this->_aim == nullptr|| ((BlockSprite*)_aim)->isDead())
	{
		Vec2 mid = this->getTransPosition();
		AABB aabbBox(mid - _detection, mid + _detection);

		vector<Node*> nodes = CollisionBody::query(aabbBox, 0);
		unsigned int length = nodes.size();
		float minLen = FLT_MAX;
		float maxLen = _detection.x * _detection.x;
		for (size_t i = 0; i < length; ++i)
		{
			if (nodes[i]->getTag() == LAYER_NPC)
			{
				Vec2 pos = nodes[i]->getTransPosition();
				float slen = mid.distanceSquared(pos);
				if (slen < maxLen && slen < minLen)
				{
					minLen = slen;
					_aim =nodes[i];
				}
			}
		}
	}
	if (this->_aim && !((BlockSprite*)_aim)->isDead())
	{
		Vec2 butSpd = this->getSpeed();
		Vec2 aimSpd = _aim->getTransPosition() - this->getTransPosition();
		float dir = butSpd.getAngle(aimSpd);
		float maxt = _maxTurn * dt;
		if (dir > maxt)
			dir = maxt;
		else if (dir < -maxt)
			dir = -maxt;
		butSpd.rotate(Vec2::ZERO, dir);
		_speed=butSpd;
		_maxTurn += 1.f * dt;
	}
	this->addPosition(_speed * dt);

	_surviveTime -= dt;

	if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), zyvar::obstacles) || _surviveTime < 0)
	{
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		this->setAlive(false);
	}
}

bool ThourthBullet::collisionFuntion(Node* node)
{
	if (_coolTimer >= _cooling)
	{
		_coolTimer = 0;
		int tag = node->getTag();
		if (_alive && (tag == LAYER_NPC || tag == LAYER_BOSS || tag == LAYER_PLY) && _lastHit != node)
		{
			_coolTimer = _cooling * 0.5;
			((BlockSprite*)(node))->getHurt(this->getPower());
			NormalBoom boomFactor;
			BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
			_parent->addChild(boom);
			((BlockSprite*)node)->getHurt(this->getPower());
			_lastHit = node;
			if ((--_penetration) < 0)
			{
				this->setAlive(false);
				return false;
			}
		}
	}
	return false;
}

//�ᴩ��
void ThourthBullet::_updateSelf(float dt)
{
	if (_coolTimer < _cooling)
		_coolTimer += dt;
	this->addPosition(_speed * dt);

	_surviveTime -= dt;

	if (_surviveTime < 0)
	{
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		this->setAlive(false);
	}
}

//���䵯
bool ReboundBullet::collisionFuntion(Node* node)
{
	int tag = node->getTag();
	if (_alive && (tag == LAYER_NPC || tag == LAYER_BOSS || tag == LAYER_PLY) && _lastHit != node)
	{
		//�����˺��ͱ�ը
		((BlockSprite*)(node))->getHurt(this->getPower());
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		((BlockSprite*)node)->getHurt(this->getPower());
		_lastHit = node;
		//����Ч��
		Vec2 myPos = this->getPosition();
		Vec2 aimPos = node->getPosition();
		Vec2 cVec = myPos - aimPos;
		_speed = cVec.getNormalized() * _speedLen;

		//�����͸���������
		if ((--_penetration) < 0)
		{
			this->setAlive(false);
			return false;
		}
	}
	return true;
}

//���䵯
void ReboundBullet::_updateSelf(float dt)
{
	this->addPosition(_speed * dt);

	_surviveTime -= dt;
	if (_surviveTime < 0)
	{
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		this->setAlive(false);
		return;
	}

	bool dirs[4]{ false };
	if (MapCollision::TestMapCollision(zyvar::tMap, this->getTransRect(), dirs, zyvar::obstacles))
	{
		//����Ч��
		if (dirs[DIR_UP] || dirs[DIR_DOWN])
		{
			_speed.y = -_speed.y;
		}
		if (dirs[DIR_LEFT] || dirs[DIR_RIGHT])
		{
			_speed.x = -_speed.x;
		}
		//��ըЧ��
		NormalBoom boomFactor;
		BoomSprite* boom = boomFactor.getBoom(this->getTransPosition());
		_parent->addChild(boom);
		
		//�����͸���������
		if ((--_penetration) < 0)
		{
			this->setAlive(false);
		}
	}
}
