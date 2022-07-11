#include "BoomSprite.h"
#include "ZY_Config.h"
#include "../BlockSprite.h"
#include "../AABB/MersenneTwister.h"

BoomSprite::BoomSprite():
	Sprite(),
	_power(0),
	_fendOffTime(0),
	_fendOffSed(0),
	_boomTime(1),
	_sound(nullptr)
{
}

BoomSprite::~BoomSprite()
{
}

BoomSprite::BoomSprite(ZY_Animation* an):
	Sprite(an),
	_power(0),
	_fendOffTime(0),
	_fendOffSed(0),
	_boomTime(1)
{
}

bool BoomSprite::collisionFuntion(Node* node)
{
	int tag = node->getTag();
	if (tag == LAYER_NPC || tag == LAYER_BOSS||tag==LAYER_PLY)
	{
		Vec2 cVec = node->getTransPosition() - this->getTransPosition();
		if (cVec.isZero())
		{
			MersenneTwister rand;
			cVec = Vec2::forAngle(rand.normal() * M_PI);
		}
		else
			cVec.normalize();
		cVec *= this->_fendOffSed;
		((BlockSprite*)(node))->setFendOff(true, cVec, _fendOffTime);
		((BlockSprite*)(node))->getHurt(_power);
	}
	return true;
}

void BoomSprite::_updateSelf(float dt)
{
	if (_boomTime == 1)
	{
		if (_sound)
		{
			_sound->Restore();
			_sound->Play();
		}
	}
	_boomTime--;
	if (_collisionBody&&_boomTime<0)
	{
		_collisionBody->removeFromTrees();
		delete _collisionBody;
		_collisionBody = nullptr;
	}

	if (_animation->getRound() >= 1)
	{
		this->setAlive(false);
	}
}

BoomSprite* NormalBoom::getBoom(const Vec2& pos,int l)
{
	BoomSprite* boom = new BoomSprite(new MLine_Animation(&BoomGraphs::bulletBoom,8,3,40));
	boom->setAlive(true);
	boom->setBoomSound(sound::bulletBoom.getSound());
	boom->setPower(0);
	boom->setFendOff(0, 0);
	boom->setTag(LAYER_EXPLOSION);
	boom->setPosition(pos);
	return boom;
}

BoomSprite* FireBoom::getBoom(const Vec2& pos,int l)
{
	BoomSprite* boom = new BoomSprite(new MLine_Animation(&BoomGraphs::explosion, 7, 1, 20));
	boom->setAlive(true);
	boom->setBoomSound(sound::blast.getSound());
	boom->setPower(6);
	boom->setFendOff(0.2,200);
	boom->setTag(LAYER_EXPLOSION);
	boom->setPosition(pos);
	boom->addCollisionBody(l,false,false);
	return boom;
}

BoomSprite* CrackBoom::getBoom(const Vec2& pos,int l)
{
	BoomSprite* boom = new BoomSprite(new MLine_Animation(&BoomGraphs::creak, 2, 1, 1));
	boom->setAlive(true);
	boom->setPower(30);
	boom->setFendOff(0.5, 500);
	boom->setBoomSound(sound::bulletBoom.getSound());
	boom->setTag(LAYER_EXPLOSION);
	boom->setPosition(pos);
	boom->addCollisionBody(l, false, false);
	return boom;
}
