#include "Camera.h"

Camera::Camera():
    Node()
{
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
    return camera;
}

bool Camera::InCamera(const Vec2& pos)
{
    return getTransRect().containsPoint(pos);
}

bool Camera::InCamera(const ZY_Rect& rect)
{
    return getTransRect().intersectsRect(rect);
}

bool Camera::InCamera(Node* node)
{
    return getTransRect().intersectsRect(node->getTransRect());
}

Camera* Camera::camera = new Camera();