#include "Node.h"
#include <algorithm>
#include"../TinyEngine/T_Config.h"
	void Node::SetWindowSize(int w, int h)
	{
		wndWidth = w;
		wndHeight = h;
		wndRect.setRect(0, 0, w, h);
	}

	Node::Node() :
		_tag(-1),
		_rotation(0),
		_anchorPoint(0, 0),
		_contentSize(0, 0),
		_contentSizeDirty(true),
		_position(0, 0),
		_scaleX(1.f),
		_scaleY(1.f),
		_visible(true),
		_zOrder(0),
		_transRect(),
		_zOrderDirty(true),
		_parent(nullptr),
		_transPosition(0, 0),
		_transPositionDirty(true),
		_pDirty(true),
		_collisionBody(nullptr),
		_transRectDirty(true),
		_alive(true),
		_active(true),
		_alpha(255),
		_pauseChlidren(false)
	{
	}

	Node::~Node()
	{
	}

	void Node::release()
	{
		_chlidrenList.clear();
		if (_collisionBody)	delete _collisionBody;
	}

	void Node::draw(HDC hdc)
	{
		if (_visible)
		{

			sortAllChildren();
			for (std::vector<Node*>::iterator iter = _chlidrenList.begin(); iter != _chlidrenList.end(); iter++)
			{
				(*iter)->draw(hdc);
			}
			drawSelf(hdc);
		}
	}

	void Node::drawSelf(HDC hdc)
	{
	}

	void Node::update(float dt)
	{
		if (_active)
		{
			if (_collisionBody)
				_collisionBody->update();
			updateSelf(dt);
			_chlidrenList.insert(_chlidrenList.end(), _tempList.begin(), _tempList.end());
			std::vector<Node*> vec;
			_tempList.swap(vec);
			if (!_pauseChlidren)
			{
				for (std::vector<Node*>::iterator iter = _chlidrenList.begin(); iter != _chlidrenList.end();)
				{
					if ((*iter)->isAlive())
					{
						(*iter)->update(dt);
						++iter;
					}
					else
					{
						(*iter)->clearSelf();
						delete(*iter);
						iter = _chlidrenList.erase(iter);
					}
				}
			}

		}
	}

	void Node::updateSelf(float dt)
	{

	}

	const ZY_Size& Node::getContentSize()
	{
		if (_contentSizeDirty)
		{
			_contentSize.width *= _scaleX;
			_contentSize.height *= _scaleY;
			_contentSizeDirty = false;
		}
		return _contentSize;
	}

	const Vec2& Node::getTransPosition()
	{
		if (_parent)
		{
			if (_transPositionDirty || _parent->_pDirty)
			{
				_transPosition = getPosition() + _parent->getTransPosition();
				_parent->_pDirty = false;
				_transPositionDirty = false;
				_transRectDirty = true;
			}
		}
		else
		{
			if (_transPositionDirty)
			{
				_transPosition = getPosition();
				_transPositionDirty = false;
			}
		}
		return _transPosition;
	}

	const ZY_Rect& Node::getTransRect()
	{
		if (_transRectDirty||(_parent&&_parent->_pDirty))
		{
			_transRect.origin = getTransPosition() - getContentSize() * _anchorPoint;
			_transRect.size = _contentSize;
			_transRectDirty = false;
		}
		return _transRect;
	}

	void Node::addChild(Node* child)
	{
		if (child->getParent() == nullptr)
		{
			this->_tempList.push_back(child);
			child->_parent = this;
		}
	}

	void Node::addChild(Node* child, int z)
	{
		if (child->getParent() == nullptr)
		{
			this->_tempList.push_back(child);
			child->_parent = this;
			child->_zOrder = z;
			_zOrderDirty = true;
		}
	}

	void Node::removeChild(Node* child, bool isdelete)
	{
		for (std::vector<Node*>::iterator iter = _chlidrenList.begin(); iter != _chlidrenList.end(); ++iter)
		{
			if (*iter == child) {
				_chlidrenList.erase(iter);
				child->_parent = nullptr;
				if (isdelete)
				{
					delete child;
				}
				break;
			}
		}
	}

	void Node::removeAllChildren(bool isdelete)
	{
		if (isdelete)
		{
			for (std::vector<Node*>::iterator iter = _chlidrenList.begin(); iter != _chlidrenList.end(); iter++)
			{
				if (*iter)
					delete* iter;
			}
		}
		_chlidrenList.clear();
	}

	Node* Node::getParent()
	{
		return _parent;
	}

	void Node::removeFromParent()
	{
		if (_parent != nullptr)
		{
			_parent->removeChild(this, false);
		}
	}

	void Node::addCollisionBody( unsigned int group, bool deteSelf,bool in)
	{
		if (_collisionBody == nullptr)
		{
			_collisionBody = new CollisionBody(group, this);
		}
		else
		{
			_collisionBody->setParent(this);
		}
		if(in)
			_collisionBody->addIntoTrees();
		_collisionBody->setDetectionSelf(deteSelf);
	}

	void Node::setAlive(bool a)
	{
		 _alive = a;
	}

	void Node::clearSelf()
	{
		if (_collisionBody)
		{
			_collisionBody->removeFromTrees();
			delete _collisionBody;
		}
		_parent = nullptr;
	}

	void Node::sortAllChildren()
	{
		if (_zOrderDirty&& _chlidrenList.size())
		{
			sort(_chlidrenList.begin(), _chlidrenList.end(), [](Node* a, Node* b) -> bool { return a->getZOrder() > b->getZOrder(); });
			_zOrderDirty = false;
		}
	}

	int Node::wndHeight = 0;
	int Node::wndWidth = 0;
	ZY_Rect Node::wndRect = ZY_Rect();
