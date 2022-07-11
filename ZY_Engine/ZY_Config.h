//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2020-12-20
// 版权所有 2007-2021 万立中
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
	static AudioDX ds;//DirectSound对象
	static AudioDXBuffer backmusic1;//背景音乐
	static AudioDXBuffer backmusic2;//背景音乐
	static AudioDXBuffer backmusic3;//背景音乐
	static AudioDXBuffer playerRun;//行走音效
	static ManySound shoot;//枪声
	static ManySound boom;//地裂
	static ManySound monsterDead;//怪物死亡
	static AudioDXBuffer playerHurt;//人物受伤
	static AudioDXBuffer speedUp;//人物加速
	static ManySound bulletBoom;//子弹击中

	static AudioDXBuffer menu_over;
	static AudioDXBuffer menu_click;

	static ManySound blast;//爆炸弹爆炸音效
	static void init(HWND hwnd);
	static void end();

};

class MapCollision {
public:
	static bool TestMapCollision(TiledMap* tmap, const ZY_Rect& rect,bool colls[],int floor);
	static bool TestMapCollision(TiledMap* tmap, const ZY_Rect& rect,int floor);
};


#endif