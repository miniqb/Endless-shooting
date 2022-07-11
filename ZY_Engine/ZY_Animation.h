#pragma once
#ifndef _ZY_ANIMATION_
#define _ZY_ANIMATION_

#include "ZY_Graph.h"
#include "SpritePool.h"
class ZY_Animation
{
public:
	ZY_Animation();
	ZY_Animation(T_Graph* g, int w, int h,int s=0);
	virtual ~ZY_Animation();

public:
	void init(T_Graph* g,int w,int h,int s=0);
	void draw(HDC hdc, const Vec2& destPos, float scaleX, float scaleY);
	void draw(HDC hdc, const Vec2& destPos, float scaleX, float scaleY,float angle,const Vec2& cPos,float alphe,int type);
	virtual void update(float dt);
	void pause(bool p);

public:
	void setSpeed(float s) { _speed = s; }
	void setSlowRate(float s) { _slowRate = s; }
	void setIndexX(float i) { _nextXIndex = i; _xIndex = i; }
	void setIndexY(int i) { _nextYIndex = i; _yIndex = i; }
	void setWidth(int w) { _widthSum = w; }
	void setHeight(int h) { _heightSum = h; }
	void setImage(T_Graph* g) { _image = g; }
	void setStartX(int x) { _startX = x; }

	int getWidthPx() { return _cellWidth; }
	int getHeightPx() { return _cellHeight; }
	int getWidthSum() { return _widthSum; }
	int getHeightSum() { return _heightSum; }

	int getIndexX() { return _xIndex; }

	unsigned int getRound() { return _round; }

	void setTag(int t) { _tag = t; }
	int getTag() { return _tag; }
protected:
	T_Graph* _image;
	int _widthSum;
	int _heightSum;
	float _speed;
	float _xIndex;
	int _yIndex;
	float _nextXIndex;
	int _nextYIndex;
	float _slowRate;
	int _cellWidth;
	int _cellHeight;
	bool _isPause;
	int _startX;
	unsigned int _round;

	int _tag;
};


class ALine_Animation:public ZY_Animation
{
public:
	static SpritePool<ALine_Animation>  aLineAnimPool_Boom;
	static SpritePool<ALine_Animation>  aLineAnimPool_Bullet;

	ALine_Animation();
	ALine_Animation(T_Graph* g, int w, int h, int s = 0);
	virtual ~ALine_Animation();
public:
	virtual void update(float dt) override;
	void nextY()
	{
		++_yIndex;
		if (_yIndex >= _heightSum)
		{
			_yIndex = 0;
		}
	}
};

class MLine_Animation:public ZY_Animation
{
public:
	//±¬Õ¨×¨Êô¶¯»­³Ø
	static SpritePool<MLine_Animation>  mLineAnimPool_Boom;

	MLine_Animation();
	MLine_Animation(T_Graph* g, int w, int h, int s = 0);
	virtual ~MLine_Animation();
public:
	virtual void update(float dt) override;
};

class Static_Animation :public ZY_Animation
{
public:
	//×Óµ¯×¨Êô¶¯»­³Ø
	static SpritePool<Static_Animation> sLineAnimPool_Bullet;

	Static_Animation();
	Static_Animation(T_Graph* g);
	virtual ~Static_Animation() {};
public:
	virtual void update(float dt) override {};
};

#endif // !_ZY_ANIMATION_