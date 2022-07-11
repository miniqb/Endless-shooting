#include "Sprite.h"

void Sprite::SetCamera(Camera* c)
{
	camera = c;
}

Sprite::Sprite():
	_animation(nullptr),
	_complexDraw(false)
{
	this->setAnchorPoint(Vec2(0.5, 0.5));
}

Sprite::Sprite(LPTSTR fileName):
	Sprite()
{
	init(fileName);
	
}

Sprite::Sprite(ZY_Animation* an):
	Sprite()
{
	init(an);
}

Sprite::~Sprite()
{
	if (_animation)
		delete _animation;
}

void Sprite::init(LPTSTR fileName)
{
}

void Sprite::init(ZY_Animation* an)
{
	_alive = true;
	_animation = an;
	setContentSize(ZY_Size(_animation->getWidthPx(), _animation->getHeightPx()));
}

void Sprite::setAnimation(ZY_Animation* an)
{
	init(an);
}

void Sprite::drawSelf(HDC hdc)
{
	if (camera->InCamera(getTransRect())) {
		
		//_frame->PaintImage(hdc, pos->x, pos->y, _contentSize->width, _contentSize->height,255);
		if (_animation)
		{
			if (_complexDraw)
			{
				Vec2 pos = _transPosition - camera->getTransRect().origin;
				_animation->draw(hdc, pos, _scaleX, _scaleY, _rotation, _anchorPoint, _alpha, TRANS_NONE);
			}
			else
			{
				Vec2 pos = _transRect.origin - camera->getTransRect().origin;
				_animation->draw(hdc, pos, _scaleX, _scaleY);
			}
			
		}

		//++zyvar::drawSum;
	}
}

void Sprite::updateSelf(float dt)
{
	if (_animation) _animation->update(dt);
	_updateSelf(dt);
}

Camera* Sprite::camera = nullptr;
