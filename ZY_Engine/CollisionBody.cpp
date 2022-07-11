#include "CollisionBody.h"

void CollisionBody::releaseTrees()
{
	Trees.clear();
}

CollisionBody::CollisionBody():
	_parent(nullptr),
	_group(0),
	_detectionSelf(false)
{
}

CollisionBody::CollisionBody(int group, Node* p) :
	_group(group),
	_parent(p),
	_detectionSelf(false)
{
}

CollisionBody::~CollisionBody()
{
	removeFromTrees();
}

void CollisionBody::AdjustTree(int stander)
{
	int len = Trees.size();
	for (size_t i = 0; i < len; ++i)
	{
		if(Trees[i].computeMaximumBalance()> stander)
			Trees[i].rebuild();
	}
}

unsigned int CollisionBody::getGroupSum()
{
	return Trees.size();
}

void CollisionBody::extendTrees(const ZY_Size& size, float thickness)
{
	Trees.push_back(Tree(thickness));
	Trees.back().setBoxSize(size);
}

std::vector<Node*> CollisionBody::query(const AABB& aabb,int group)
{
	return Trees[group].query(aabb);
}

void CollisionBody::addIntoTrees()
{
	if (_group < Trees.size() && _parent != nullptr)
	{
		AABB aabbBox;
		ZY_Rect rect = _parent->getTransRect();
		aabbBox.lowerBound = rect.origin;
		aabbBox.upperBound = rect.origin + rect.size;
		Trees[_group].insertParticle(_parent, aabbBox.lowerBound, aabbBox.upperBound);
	}
}

void CollisionBody::removeFromTrees()
{
	if (_parent)
	{
		Trees[_group].removeParticle(_parent);
		_parent = nullptr;
	}
}

void CollisionBody::update()
{
	AABB aabbBox;
	ZY_Rect rect = _parent->getTransRect();
	aabbBox.lowerBound = rect.origin;
	aabbBox.upperBound = rect.origin + rect.size;
	unsigned int length = Trees.size();
	Trees[_group].updateParticle(_parent, aabbBox.lowerBound, aabbBox.upperBound);
	for (size_t i = 0; i < length; ++i)
	{
		if (!_detectionSelf && i == _group)
			continue;

		if (Trees[i].getNodeCount())
		{
			std::vector<Node*> otherNodes = Trees[i].query(_parent, aabbBox);
			unsigned int size = otherNodes.size();
			for (size_t j = 0; j < size; ++j)
			{
				if (!_parent->collisionFuntion(otherNodes[j]))
				{
					break;
				}
			}
		}

	}
}

std::vector<Tree> CollisionBody::Trees;
