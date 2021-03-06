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

#ifndef __MATH_CCGEOMETRY_H__
#define __MATH_CCGEOMETRY_H__

#include "Vec2.h"
/**
 * @addtogroup base
 * @{
 */


class  ZY_Size
{
public:
    /**Width of the ZY_Size.*/
    float width;
    /**Height of the ZY_Size.*/
    float height;
    
public:
    /**Conversion from Vec2 to ZY_Size.*/
    operator Vec2() const
    {
        return Vec2(width, height);
    }

public:
    /**
    @{
    Constructor.
    @param width Width of the size.
    @param height Height of the size.
    @param other Copy constructor.
    @param point Conversion from a point.
     */
    ZY_Size();
    ZY_Size(float width, float height);
    ZY_Size(const ZY_Size& other);
    explicit ZY_Size(const Vec2& point);
    /**@}*/

    /**
     * @js NA
     * @lua NA
     */
    ZY_Size& operator= (const ZY_Size& other);
    /**
     * @js NA
     * @lua NA
     */
    ZY_Size& operator= (const Vec2& point);
    /**
     * @js NA
     * @lua NA
     */
    ZY_Size operator+(const ZY_Size& right) const;
    /**
     * @js NA
     * @lua NA
     */
    ZY_Size operator-(const ZY_Size& right) const;
    /**
     * @js NA
     * @lua NA
     */
    ZY_Size operator*(float a) const;
    /**
 * @js NA
 * @lua NA
 */
    ZY_Size operator*(const Vec2& a) const;
    /**
     * @js NA
     * @lua NA
     */
    ZY_Size operator/(float a) const;
    /**
    Set the width and height of ZY_Size.
     * @js NA
     * @lua NA
     */
    void setZY_Size(float width, float height);
    /**
    Check if two size is the same.
     * @js NA
     */
    bool equals(const ZY_Size& target) const;
    /**ZY_Size(0,0).*/
    static const ZY_Size ZERO;
};

/**ZY_Rectangle area.*/
class  ZY_Rect
{
public:
    /**Low left point of rect.*/
    Vec2 origin;
    /**Width and height of the rect.*/
    ZY_Size  size;

public:
    /**
    Constructor an empty ZY_Rect.
     * @js NA
     */
    ZY_Rect();
    /**
    Constructor a rect.
     * @js NA
     */
    ZY_Rect(float x, float y, float width, float height);
    /**
     Constructor a rect.
     * @js NA
     */
    ZY_Rect(const Vec2& pos, const ZY_Size& dimension);
    /**
    Copy constructor.
     * @js NA
     * @lua NA
     */
    ZY_Rect(const ZY_Rect& other);
    /**
     * @js NA
     * @lua NA
     */
    ZY_Rect& operator= (const ZY_Rect& other);
    /**
    Set the x, y, width and height of ZY_Rect.
     * @js NA
     * @lua NA
     */
    void setRect(float x, float y, float width, float height);
    /**
    Get the left of the rect.
     * @js NA
     */
    float getMinX() const; /// return the leftmost x-value of current rect
    /**
    Get the X coordinate of center point.
     * @js NA
     */
    float getMidX() const; /// return the midpoint x-value of current rect
    /**
    Get the right of rect.
     * @js NA
     */
    float getMaxX() const; /// return the rightmost x-value of current rect
    /**
    Get the bottom of rect.
     * @js NA
     */
    float getMinY() const; /// return the bottommost y-value of current rect
    /**
    Get the Y coordinate of center point.
     * @js NA
     */
    float getMidY() const; /// return the midpoint y-value of current rect
    /**
    Get top of rect.
     * @js NA
     */
    float getMaxY() const; /// return the topmost y-value of current rect
    /**
    Compare two rects.
     * @js NA
     */
    bool equals(const ZY_Rect& rect) const;
    /**
    Check if the points is contained in the rect.
     * @js NA
     */
    inline bool containsPoint(const Vec2& point) const;
    /**
    Check the intersect status of two rects.
     * @js NA
     */
    inline bool intersectsRect(const ZY_Rect& rect) const;
    /**
    Check the intersect status of the rect and a circle.
     * @js NA
     */
    bool intersectsCircle(const Vec2& center, float radius) const;
    /**
    Get the min rect which can contain this and rect.
     * @js NA
     * @lua NA
     */
    ZY_Rect unionWithRect(const ZY_Rect & rect) const;

    ZY_Rect intersectWithRect(const ZY_Rect& rect) const;
    /**Compute the min rect which can contain this and rect, assign it to this.*/
    void merge(const ZY_Rect& rect);

    bool contain(const ZY_Rect& rect);

    /**An empty ZY_Rect.*/
    static const ZY_Rect ZERO;
};
// end of base group
/// @}
inline bool ZY_Rect::intersectsRect(const ZY_Rect& rect) const
{
    return !(getMaxX() <= rect.getMinX() ||
        rect.getMaxX() <= getMinX() ||
        getMaxY() <= rect.getMinY() ||
        rect.getMaxY() <= getMinY());
}

inline bool ZY_Rect::containsPoint(const Vec2& point) const
{
    return (point.x >= origin.x && point.x <= origin.x + size.width
        && point.y >= origin.y && point.y <= origin.y + size.height);
}
#endif // __MATH_CCGEOMETRY_H__
