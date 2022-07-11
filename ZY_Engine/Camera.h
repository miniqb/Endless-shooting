#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Node.h"

class Camera :
    public Node
{
    static Camera* camera;
private :
    Camera();
public:
    ~Camera();

public:
    static Camera* GetInstance();

    bool InCamera(const Vec2& pos);
    bool InCamera(const ZY_Rect& rect);
    bool InCamera(Node* node);
};

#endif // !_CAMERA_H_