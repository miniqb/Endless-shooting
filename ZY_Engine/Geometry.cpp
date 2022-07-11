/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "Geometry.h"
#include <algorithm>



// implementation of Siz

ZY_Size::ZY_Size() : width(0), height(0)
{
}

ZY_Size::ZY_Size(float w, float h) : width(w), height(h)
{
}

ZY_Size::ZY_Size(const ZY_Size& other) : width(other.width), height(other.height)
{
}

ZY_Size::ZY_Size(const Vec2& point) : width(point.x), height(point.y)
{
}

ZY_Size& ZY_Size::operator= (const ZY_Size& other)
{
    setZY_Size(other.width, other.height);
    return *this;
}

ZY_Size& ZY_Size::operator= (const Vec2& point)
{
    setZY_Size(point.x, point.y);
    return *this;
}

ZY_Size ZY_Size::operator+(const ZY_Size& right) const
{
    return ZY_Size(this->width + right.width, this->height + right.height);
}

ZY_Size ZY_Size::operator-(const ZY_Size& right) const
{
    return ZY_Size(this->width - right.width, this->height - right.height);
}

ZY_Size ZY_Size::operator*(float a) const
{
    return ZY_Size(this->width * a, this->height * a);
}

ZY_Size ZY_Size::operator*(const Vec2& a) const
{
    return ZY_Size(this->width * a.x, this->height * a.y);
}

ZY_Size ZY_Size::operator/(float a) const
{
    if (a == 0)
        return ZY_Size::ZERO;
    return ZY_Size(this->width / a, this->height / a);
}

void ZY_Size::setZY_Size(float w, float h)
{
    this->width = w;
    this->height = h;
}

bool ZY_Size::equals(const ZY_Size& target) const
{
    return (std::abs(this->width  - target.width)  < FLT_EPSILON)
        && (std::abs(this->height - target.height) < FLT_EPSILON);
}

const ZY_Size ZY_Size::ZERO = ZY_Size(0, 0);

// implementation of ZY_Rect

ZY_Rect::ZY_Rect()
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

ZY_Rect::ZY_Rect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}
ZY_Rect::ZY_Rect(const Vec2& pos, const ZY_Size& dimension)
{
    setRect(pos.x, pos.y, dimension.width, dimension.height);
}

ZY_Rect::ZY_Rect(const ZY_Rect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

ZY_Rect& ZY_Rect::operator= (const ZY_Rect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void ZY_Rect::setRect(float x, float y, float width, float height)
{
    // CGZY_Rect can support width<0 or height<0
    // CCASSERT(width >= 0.0f && height >= 0.0f, "width and height of ZY_Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool ZY_Rect::equals(const ZY_Rect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
}

float ZY_Rect::getMaxX() const
{
    return origin.x + size.width;
}

float ZY_Rect::getMidX() const
{
    return origin.x + size.width / 2.0f;
}

float ZY_Rect::getMinX() const
{
    return origin.x;
}

float ZY_Rect::getMaxY() const
{
    return origin.y + size.height;
}

float ZY_Rect::getMidY() const
{
    return origin.y + size.height / 2.0f;
}

float ZY_Rect::getMinY() const
{
    return origin.y;
}



bool ZY_Rect::intersectsCircle(const Vec2& center, float radius) const
{
    Vec2 rectangleCenter((origin.x + size.width / 2),
                         (origin.y + size.height / 2));
    
    float w = size.width / 2;
    float h = size.height / 2;
    
    float dx = std::abs(center.x - rectangleCenter.x);
    float dy = std::abs(center.y - rectangleCenter.y);
    
    if (dx > (radius + w) || dy > (radius + h))
    {
        return false;
    }
    
    Vec2 circleDistance(std::abs(center.x - origin.x - w),
                        std::abs(center.y - origin.y - h));
    
    if (circleDistance.x <= (w))
    {
        return true;
    }
    
    if (circleDistance.y <= (h))
    {
        return true;
    }
    
    float cornerDistanceSq = powf(circleDistance.x - w, 2) + powf(circleDistance.y - h, 2);
    
    return (cornerDistanceSq <= (powf(radius, 2)));
}

void ZY_Rect::merge(const ZY_Rect& rect)
{
    float minX = std::min(getMinX(), rect.getMinX());
    float minY = std::min(getMinY(), rect.getMinY());
    float maxX = std::max(getMaxX(), rect.getMaxX());
    float maxY = std::max(getMaxY(), rect.getMaxY());
    setRect(minX, minY, maxX - minX, maxY - minY);
}

bool ZY_Rect::contain(const ZY_Rect& rect)
{
    if (origin.x <= rect.origin.x &&
        origin.y <= rect.origin.y &&
        origin.x + size.width >= rect.getMaxX() &&
        origin.y + size.height >= rect.getMaxY())
        return true;
    return false;
}


ZY_Rect ZY_Rect::unionWithRect(const ZY_Rect & rect) const
{
    float thisLeftX = origin.x;
    float thisRightX = origin.x + size.width;
    float thisTopY = origin.y + size.height;
    float thisBottomY = origin.y;
    
    if (thisRightX < thisLeftX)
    {
        std::swap(thisRightX, thisLeftX);   // This rect has negative width
    }
    
    if (thisTopY < thisBottomY)
    {
        std::swap(thisTopY, thisBottomY);   // This rect has negative height
    }
    
    float otherLeftX = rect.origin.x;
    float otherRightX = rect.origin.x + rect.size.width;
    float otherTopY = rect.origin.y + rect.size.height;
    float otherBottomY = rect.origin.y;
    
    if (otherRightX < otherLeftX)
    {
        std::swap(otherRightX, otherLeftX);   // Other rect has negative width
    }
    
    if (otherTopY < otherBottomY)
    {
        std::swap(otherTopY, otherBottomY);   // Other rect has negative height
    }
    
    float combinedLeftX = std::min(thisLeftX, otherLeftX);
    float combinedRightX = std::max(thisRightX, otherRightX);
    float combinedTopY = std::max(thisTopY, otherTopY);
    float combinedBottomY = std::min(thisBottomY, otherBottomY);
    
    return ZY_Rect(combinedLeftX, combinedBottomY, combinedRightX - combinedLeftX, combinedTopY - combinedBottomY);
}

ZY_Rect ZY_Rect::intersectWithRect(const ZY_Rect& rect) const
{
    float Xs[4] = { origin.x,getMaxX(),rect.origin.x,rect.getMaxX() };
    float Ys[4] = { origin.y,getMaxY(),rect.origin.y,rect.getMaxY() };
    std::sort(Xs, Xs + 4);
    std::sort(Ys, Ys + 4);
    return ZY_Rect(Xs[1], Ys[1], Xs[2] - Xs[1], Ys[2] - Ys[1]);
}

const ZY_Rect ZY_Rect::ZERO = ZY_Rect(0, 0, 0, 0);