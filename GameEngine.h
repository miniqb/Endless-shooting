#pragma once
#include "./ZY_Engine/ZY_Engine.h"
class GameEngine :
	public ZY_Engine
{
public:
	// 构造函数
	GameEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	// 析构函数
	virtual ~GameEngine();

public:
	// 纯函数声明(具体游戏要重载这些函数并增加游戏功能代码)
	// 游戏初始化
	virtual void GameInit();
	// 游戏逻辑处理
	virtual void GameLogic();
	// 游戏结束处理
	virtual void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	virtual void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理鼠标行为
	virtual void GameMouseAction(int x, int y, int ActionType);

	virtual void GameKeyAction(UINT32 KeyChar, int ActionType = KEY_SYS_NONE);

	// 根据KM_ACTION值处理按键行为
	virtual void GameKeyAction(int ActionType = KEY_SYS_NONE) {}
};

