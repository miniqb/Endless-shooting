#pragma once

#ifndef _COLLISION_BODY_
#define  _COLLISION_BODY_

#include "../AABB/AABB2.h"
#include "Node.h"
class Node;
class Tree;
class AABB;
class CollisionBody
{
	static std::vector<Tree> Trees;
public:
	static void releaseTrees();
	CollisionBody();
	CollisionBody(int group,Node* p);
	~CollisionBody();

	static void AdjustTree(int stander);
	static unsigned int getGroupSum();
	static void extendTrees(const ZY_Size& size,float thickness=0);
	static std::vector<Node*> query(const AABB& aabb, int group);

	void addIntoTrees();
	void removeFromTrees();

	Node* getParent() { return _parent; };
	void setParent(Node* p) { _parent = p; };

	void update();
	unsigned int getGroup() { return _group; }
	void setDetectionSelf(bool d) { _detectionSelf = d; }
private:
	unsigned int _group;
	
	Node* _parent;

	bool _detectionSelf;
};

#endif // !_COLLISION_BODY_