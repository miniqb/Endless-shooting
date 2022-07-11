#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Camera.h"
#include "ZY_Animation.h"

class ZY_Animation;
class Sprite :
    public Node
{
public:
    Sprite();
    Sprite(LPTSTR fileName);
    Sprite(ZY_Animation* an);
    ~Sprite();

    static void SetCamera(Camera* c);
    void init(LPTSTR fileName);
    void init(ZY_Animation* an);
    ZY_Animation* getAnimatin() { return _animation; }
    void setAnimation(ZY_Animation* an);
    bool isComplexDraw() { return _complexDraw; }
    static Camera* getCamera() { return camera; }
protected:
    //camera缓存，提高访问速度
    static Camera* camera;

    ZY_Animation* _animation;
    virtual void drawSelf(HDC hdc)override;
    virtual void updateSelf(float dt)override;
    virtual void _updateSelf(float dt) {};
   
    void setComplexDraw(bool c) { _complexDraw = c; }

    bool _complexDraw;


};

#endif // !_SPRITE_H_

