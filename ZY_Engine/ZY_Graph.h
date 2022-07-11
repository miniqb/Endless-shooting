#pragma once
#ifndef _ZY_GRAPH_
#define _ZY_GRAPH_

#include "../TinyEngine/T_Graph.h"
#include "Vec2.h"

class ZY_Graph :
    public T_Graph
{
public:
	ZY_Graph();					// T_Graph类默认构造函数
	ZY_Graph(LPTSTR fileName);	// 使用指定文件创建T_Graph对象
	virtual ~ZY_Graph() {};			// T_Graph类的析构函数

public:
	using T_Graph::PaintRegion;
	using T_Graph::PaintFrame;

	static void PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos,
		const Vec2& srcPos, int regionWidth, int regionHeight, BYTE alpha = 255);

	/**
	*  创建一个与内存相关的位图
	*  @param hdc 设备上下文
	*  @param width 位图宽
	*  @param height 位图高
	*  @param color 位图颜色
	*/
	static HBITMAP CreateBlankBitmap(HDC hdc, int width, int height, COLORREF color);

	/**
	*  在目标屏幕上的指定绘制源图像的指定区域，支持任意角度旋转、拉伸、上下左右翻转、透明度设置、以及缩放。
	*  @param in_hbitmap 源位图句柄
	*  @param destDC 目标屏幕DC
	*  @param destPos 目标位置
	*  @param srcX 要绘制的源图像区域左上角x坐标
	*  @param srcY 要绘制的源图像区域左上角y坐标
	*  @param regionWidth 要绘制的源图像区域宽
	*  @param regionHeight 要绘制的源图像区域高
	*  @param ratioX 水平缩放度
	*  @param ratioY 垂直缩放度
	*  @param angle 绕旋转中心逆时针旋转的角度（单位为弧度）
	*  @param anchorPoint 旋转中心位置，相对源图像绘制区域，同时该点的位置代表图像的位置
	*  @param rotType 翻转选项
	*  @param alpha 不透明度
	*/
	static void PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos,
		int srcX, int srcY, int regionWidth, int regionHeight,
		const float ratioX, const float ratioY, float angle, const Vec2& anchorPoint, int rotType = 0, BYTE alpha = 255);

	/**
*  在目标屏幕上的指定绘制源图像的指定区域，支持任意角度旋转、拉伸、上下左右翻转、透明度设置、以及缩放。
*  @param in_hbitmap 源位图句柄
*  @param destDC 目标屏幕DC
*  @param destP 目标位置
*  @param FrameCount 要绘制的帧计数
*  @param srcY 要绘制的源图像区域左上角y坐标
*  @param regionWidth 要绘制的源图像区域宽
*  @param regionHeight 要绘制的源图像区域高
*  @param ratioX 水平缩放度
*  @param ratioY 垂直缩放度
*  @param angle 绕旋转中心逆时针旋转的角度（单位为弧度）
*  @param pivot 旋转中心位置，相对源图像绘制区域，同时该点的位置代表图像的位置
*  @param rotType 翻转选项
*  @param alpha 不透明度
*/
	static void PaintFrame(HBITMAP in_hbitmap, HDC destDC, Vec2 destP,
		int FrameCount, int RowFrames, int wFrame, int hFrame,
		float angle = 0,
		float ratioX = 1, float ratioY = 1,  const Vec2& anchorPoint=Vec2(0.5,0.5),int rotType = 0, BYTE alpha = 255);

	//以下是上面两个方法的另一种实现方法，功能相同，但是耗时更长，一般不会使用
	static void PaintRegion2(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos, int wndW, int wndH,
		int srcX, int srcY, int regionWidth, int regionHeight,
		const Vec2& ratio, float angle, const Vec2& pivot, int rotType = 0, BYTE alpha = 255);
	static void PaintFrame2(HBITMAP in_hbitmap, HDC destDC, Vec2 destP, int wndW, int wndH,
		int FrameCount, int RowFrames, int wFrame, int hFrame,
		float angle = 0,
		float ratio = 1, int rotType = 0, BYTE alpha = 255);
};

class OtherGraphs
{
public:
	static T_Graph heart;
	//static T_Graph bullet;
	//static T_Graph gun;
	//
	static void init();
};

class PropsGraphs
{
public:
	static T_Graph boom;
	static T_Graph note;
	static T_Graph rebound;
	static T_Graph through;
	static T_Graph rifle;
	static T_Graph shotgun;
	static T_Graph revolver;
	static T_Graph boss;

	static void init();
};

class BoomGraphs
{
public:
	static T_Graph bulletBoom;
	static T_Graph creak;
	static T_Graph explosion;
	static void init();
};

class BulletGraphs
{
public:
	static T_Graph bullet;
	static T_Graph fire;
	static T_Graph note;
	static T_Graph rebound;
	static T_Graph through;
	static T_Graph boom;
	static T_Graph split;
	static T_Graph npc;
	static void init();
};

class MonsterGraphs
{
public:
	static T_Graph player;
	static T_Graph bat;
	static T_Graph bird;
	static T_Graph cdragon;
	static T_Graph chicken;
	static T_Graph cow;
	static T_Graph death;
	static T_Graph dragon;
	static T_Graph dragon2;
	static T_Graph fire;
	static T_Graph gost;
	static T_Graph lizard;
	static T_Graph mummy;
	static T_Graph skeleton;
	static T_Graph snake;
	static T_Graph stone;
	static T_Graph vampire;
	static T_Graph wolf;
	static T_Graph zombies;
	static void init();
};

class GunGraphs
{
public:
	//手枪
	static T_Graph pistol;
	//左轮
	static T_Graph revolver;
	//步枪
	static T_Graph rifle;
	//霰弹
	static T_Graph shotgun;
	//
	static T_Graph boss;

	static void init();
};

class MenuGraphs
{
public:
	static T_Graph main;
	static T_Graph other;
	static T_Graph pause;
	static void init();
};
#endif // !_ZY_GRAPH_