//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ����: 2020-12-20
// ��Ȩ���� 2007-2021 ������
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#ifndef ZYCONFIG_H
#define ZYCONFIG_H
#include <windows.h>
#include <chrono>
#include "Geometry.h"
#include "TiledMap.h"
#include <cstdio>
#include "ManySound.h"
#include "ZY_Engine.h"

#define MOUSE_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
class ZY_Engine;
class zyvar {
public:
	static RECT wndRect;
	static POINT mousePos;
	static bool keyChars[];
	static TiledMap* tMap;
	static int drawSum;
	static Camera* nowCamera;
	static int obstacles;
	static ZY_Size worldSize;
	static BYTE nowKey;
	static ZY_Engine* pEngine;
};

class sound {
public:
	static AudioDX ds;//DirectSound����
	static AudioDXBuffer backmusic1;//��������
	static AudioDXBuffer backmusic2;//��������
	static AudioDXBuffer backmusic3;//��������
	static AudioDXBuffer playerRun;//������Ч
	static ManySound shoot;//ǹ��
	static ManySound boom;//����
	static ManySound monsterDead;//��������
	static AudioDXBuffer playerHurt;//��������
	static AudioDXBuffer speedUp;//�������
	static ManySound bulletBoom;//�ӵ�����

	static AudioDXBuffer menu_over;
	static AudioDXBuffer menu_click;

	static ManySound blast;//��ը����ը��Ч
	static void init(HWND hwnd);
	static void end();

};

class MapCollision {
public:
	static bool TestMapCollision(TiledMap* tmap, const ZY_Rect& rect,bool colls[],int floor);
	static bool TestMapCollision(TiledMap* tmap, const ZY_Rect& rect,int floor);
};


#endif