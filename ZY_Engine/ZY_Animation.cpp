#include "ZY_Animation.h"

ZY_Animation::ZY_Animation():
	_image(nullptr),
	_widthSum(0),
	_heightSum(0),
	_xIndex(0),
	_yIndex(0),
	_cellWidth(0),
	_cellHeight(0),
	_slowRate(1.f),
	_speed(0),
	_isPause(false),
	_startX(0),
	_tag(0),
	_round(0),
	_nextXIndex(0),
	_nextYIndex(0)
{
}

ZY_Animation::ZY_Animation(T_Graph* g, int w, int h, int s):
	ZY_Animation()
{
		init(g, w, h, s);
}

ZY_Animation::~ZY_Animation()
{
}

void ZY_Animation::init(T_Graph* g, int w, int h,int s)
{
	_image = g;
	if (_image != nullptr)
	{
		int imWidth = _image->GetImageWidth();
		if (w) _cellWidth = imWidth / w;
		int imHeight = _image->GetImageHeight();
		if (h)_cellHeight = imHeight / h;
	}
	_widthSum = w;
	_heightSum = h;
	_speed = s;
	_xIndex = 0;
	_yIndex = 0;
	_round = 0;
	_nextXIndex = 0;
	_nextYIndex = 0;
}

void ZY_Animation::draw(HDC hdc, const Vec2& destPos, float scaleX, float scaleY)
{
	int intX = (int)_xIndex;
	T_Graph::PaintRegion(_image->GetBmpHandle(), hdc, destPos.x, destPos.y,intX*_cellWidth,_yIndex*_cellHeight,_cellWidth,_cellHeight,scaleX);
	
}

void ZY_Animation::draw(HDC hdc, const Vec2& destPos, float scaleX, float scaleY, float angle, const Vec2& cPos, float alphe,int type)
{
	int intX = (int)_xIndex;
	ZY_Graph::PaintRegion(_image->GetBmpHandle(), hdc, destPos, intX * _cellWidth, _yIndex * _cellHeight, _cellWidth, _cellHeight, scaleX, scaleY, angle, cPos, type, alphe);
}

void ZY_Animation::update(float dt)
{
}


void ZY_Animation::pause(bool p)
{
	_isPause = p;
}

ALine_Animation::ALine_Animation():
	ZY_Animation()
{
}

ALine_Animation::ALine_Animation(T_Graph* g, int w, int h, int s):
	ZY_Animation(g, w, h, s)
{
}

ALine_Animation::~ALine_Animation()
{
}

void ALine_Animation::update(float dt)
{
	if (!_isPause)
	{
		_xIndex = _nextXIndex;
		_yIndex = _nextYIndex;
		_nextXIndex += _speed * dt * _slowRate;
		if ((int)_nextXIndex >= _widthSum)
		{
			_nextXIndex = _startX;
			++_round;
		}
	}
}

MLine_Animation::MLine_Animation():
	ZY_Animation()
{
}

MLine_Animation::MLine_Animation(T_Graph* g, int w, int h, int s) :
	ZY_Animation(g, w, h, s)
{
}

MLine_Animation::~MLine_Animation()
{
}

void MLine_Animation::update(float dt)
{
	if (!_isPause)
	{
		_xIndex = _nextXIndex;
		_yIndex = _nextYIndex;
		_nextXIndex += _speed * dt * _slowRate;
		if ((int)_nextXIndex >= _widthSum)
		{
			_nextXIndex = _startX;
			if (++_nextYIndex >= _heightSum)
			{
				_nextYIndex = 0;
				++_round;
			}
		}
	}
}

Static_Animation::Static_Animation():
	ZY_Animation()
{
}

Static_Animation::Static_Animation(T_Graph* g)
{
	_cellWidth = g->GetImageWidth();
	_cellHeight = g->GetImageHeight();
	_image = g;
}

//±¬Õ¨×¨Êô
SpritePool<ALine_Animation> ALine_Animation::aLineAnimPool_Boom(50);
SpritePool<ALine_Animation> ALine_Animation::aLineAnimPool_Bullet(50);
SpritePool<MLine_Animation> MLine_Animation::mLineAnimPool_Boom(50);
SpritePool<Static_Animation> Static_Animation::sLineAnimPool_Bullet(50);

//×Óµ¯×¨Êô