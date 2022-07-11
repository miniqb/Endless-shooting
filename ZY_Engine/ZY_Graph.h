#pragma once
#ifndef _ZY_GRAPH_
#define _ZY_GRAPH_

#include "../TinyEngine/T_Graph.h"
#include "Vec2.h"

class ZY_Graph :
    public T_Graph
{
public:
	ZY_Graph();					// T_Graph��Ĭ�Ϲ��캯��
	ZY_Graph(LPTSTR fileName);	// ʹ��ָ���ļ�����T_Graph����
	virtual ~ZY_Graph() {};			// T_Graph�����������

public:
	using T_Graph::PaintRegion;
	using T_Graph::PaintFrame;

	static void PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos,
		const Vec2& srcPos, int regionWidth, int regionHeight, BYTE alpha = 255);

	/**
	*  ����һ�����ڴ���ص�λͼ
	*  @param hdc �豸������
	*  @param width λͼ��
	*  @param height λͼ��
	*  @param color λͼ��ɫ
	*/
	static HBITMAP CreateBlankBitmap(HDC hdc, int width, int height, COLORREF color);

	/**
	*  ��Ŀ����Ļ�ϵ�ָ������Դͼ���ָ������֧������Ƕ���ת�����졢�������ҷ�ת��͸�������á��Լ����š�
	*  @param in_hbitmap Դλͼ���
	*  @param destDC Ŀ����ĻDC
	*  @param destPos Ŀ��λ��
	*  @param srcX Ҫ���Ƶ�Դͼ���������Ͻ�x����
	*  @param srcY Ҫ���Ƶ�Դͼ���������Ͻ�y����
	*  @param regionWidth Ҫ���Ƶ�Դͼ�������
	*  @param regionHeight Ҫ���Ƶ�Դͼ�������
	*  @param ratioX ˮƽ���Ŷ�
	*  @param ratioY ��ֱ���Ŷ�
	*  @param angle ����ת������ʱ����ת�ĽǶȣ���λΪ���ȣ�
	*  @param anchorPoint ��ת����λ�ã����Դͼ���������ͬʱ�õ��λ�ô���ͼ���λ��
	*  @param rotType ��תѡ��
	*  @param alpha ��͸����
	*/
	static void PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos,
		int srcX, int srcY, int regionWidth, int regionHeight,
		const float ratioX, const float ratioY, float angle, const Vec2& anchorPoint, int rotType = 0, BYTE alpha = 255);

	/**
*  ��Ŀ����Ļ�ϵ�ָ������Դͼ���ָ������֧������Ƕ���ת�����졢�������ҷ�ת��͸�������á��Լ����š�
*  @param in_hbitmap Դλͼ���
*  @param destDC Ŀ����ĻDC
*  @param destP Ŀ��λ��
*  @param FrameCount Ҫ���Ƶ�֡����
*  @param srcY Ҫ���Ƶ�Դͼ���������Ͻ�y����
*  @param regionWidth Ҫ���Ƶ�Դͼ�������
*  @param regionHeight Ҫ���Ƶ�Դͼ�������
*  @param ratioX ˮƽ���Ŷ�
*  @param ratioY ��ֱ���Ŷ�
*  @param angle ����ת������ʱ����ת�ĽǶȣ���λΪ���ȣ�
*  @param pivot ��ת����λ�ã����Դͼ���������ͬʱ�õ��λ�ô���ͼ���λ��
*  @param rotType ��תѡ��
*  @param alpha ��͸����
*/
	static void PaintFrame(HBITMAP in_hbitmap, HDC destDC, Vec2 destP,
		int FrameCount, int RowFrames, int wFrame, int hFrame,
		float angle = 0,
		float ratioX = 1, float ratioY = 1,  const Vec2& anchorPoint=Vec2(0.5,0.5),int rotType = 0, BYTE alpha = 255);

	//����������������������һ��ʵ�ַ�����������ͬ�����Ǻ�ʱ������һ�㲻��ʹ��
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
	//��ǹ
	static T_Graph pistol;
	//����
	static T_Graph revolver;
	//��ǹ
	static T_Graph rifle;
	//����
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