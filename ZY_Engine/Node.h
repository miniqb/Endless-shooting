#pragma once
#ifndef _NODE_H_
#define _NODE_H_

#include "Geometry.h"
#include <Windows.h>
#include <vector>
#include "CollisionBody.h"
 
class CollisionBody;
class Node
{
protected:
	static int wndWidth;
	static int wndHeight;
	static ZY_Rect wndRect;
public:
	static void SetWindowSize(int w, int h);
public:
	Node();
	virtual ~Node();
	void release();

	void draw(HDC hdc);

	void update(float dt);

	void setTag(int t) { _tag = t; }
	int getTag() { return _tag; }
	void setAnchorPoint(const Vec2& ap) { _anchorPoint = ap;  _pDirty = true; _transRectDirty = true; }
	const Vec2& getAnchorPoint() { return _anchorPoint; }
	void setContentSize(const ZY_Size& size) { _contentSize = size;  _transRectDirty = true;   _contentSizeDirty = true;  _pDirty = true; }
	const ZY_Size& getContentSize();
	void setPosition(const Vec2& p) { _position = p; _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }
	void setPosX(float x) { _position.x = x;  _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }
	void setPosY(float y) { _position.y = y;  _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }
	void addPosition(const Vec2& p) { _position += p;  _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }
	virtual const Vec2& getPosition() { return _position; }
	const Vec2& getTransPosition();
	void setScaleX(float x) { _scaleX = x; _contentSizeDirty = true;  _transRectDirty = true; }
	float getScaleX() { return _scaleX; }
	void setScaleY(float y) { _scaleY = y; _contentSizeDirty = true;  _transRectDirty = true; }
	float getScaleY() { return _scaleY; }
	void setScale(float x, float y) { _scaleX = x, _scaleY = y; _contentSizeDirty = true;  _transRectDirty = true; }
	void setRotation(float r) { _rotation = r; }
	float getRotation() { return _rotation; }
	void setVisible(bool v) { _visible = v; }
	bool IsVisble() { return _visible; }
	void setZOrder(int z) { _zOrder = z; }
	int getZOrder() { return _zOrder; }
	void setActive(bool a) { _active = a; }
	bool isActive() { return _active; }
	const ZY_Rect& getTransRect();
	void addPositionX(float x) { _position.x += x; _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }
	void addPositionY(float y){ _position.y += y; _transPositionDirty = true;  _pDirty = true;  _transRectDirty = true; }

	void addChild(Node* child);
	void addChild(Node* child, int z);
	void removeChild(Node* child, bool isdelete = true);
	void removeAllChildren(bool isdelete = true);
	Node* getParent();
	void removeFromParent();

	virtual bool collisionFuntion(Node* node) { return true; };
	void addCollisionBody(unsigned int group,bool deteSelf=false, bool in = true);
	CollisionBody* getCollisionBody() { return _collisionBody; }

	void setAlive(bool a);
	virtual void clearSelf();
	bool isAlive() { return _alive; }

	void setAlpha(int a) { _alpha = a; }
	void addAlpha(int s){_alpha+=s;}
	int getAlpha() { return _alpha; }

	void pauseChildren(bool p) { _pauseChlidren = p; }
protected:

	void sortAllChildren();
	virtual void drawSelf(HDC hdc);
	virtual void updateSelf(float dt);
protected:
	int _tag;
	//��ת�Ƕ�
	float _rotation;
	/**
	 * ê��
	 */
	Vec2 _anchorPoint;;
	/**
	 * ���δ�С
	 */
	ZY_Size _contentSize;
	/**
	 * ��С�Ƿ�ı�
	 */
	bool _contentSizeDirty;
	/**
	 * λ��
	 */
	Vec2 _position;
	/**
	 * X�����ųߴ�
	 */
	float _scaleX;
	/**
	 * Y�����ųߴ�
	 */
	float _scaleY;
	/**
	 * �Ƿ�ɼ�
	 */
	bool _visible;
	/**
	 * �ڵ���ʾ˳��
	 */
	int _zOrder;
	bool _zOrderDirty;

	ZY_Rect _transRect;
	bool _transRectDirty;
	//�ӽڵ�
	std::vector<Node*> _chlidrenList;
	std::vector<Node*> _tempList;
	//���ڵ�
	Node* _parent;

	//����λ��
	Vec2 _transPosition;
	bool _transPositionDirty;

	bool _pDirty;

	CollisionBody* _collisionBody;

	bool _alive;

	bool _active;

	int _alpha;

	bool _pauseChlidren;
};
#endif // !_NODE_H_