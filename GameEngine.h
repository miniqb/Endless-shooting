#pragma once
#include "./ZY_Engine/ZY_Engine.h"
class GameEngine :
	public ZY_Engine
{
public:
	// ���캯��
	GameEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	// ��������
	virtual ~GameEngine();

public:
	// ����������(������ϷҪ������Щ������������Ϸ���ܴ���)
	// ��Ϸ��ʼ��
	virtual void GameInit();
	// ��Ϸ�߼�����
	virtual void GameLogic();
	// ��Ϸ��������
	virtual void GameEnd();
	// ����GAME_STATEֵ��ʾ��Ϸ����
	virtual void GamePaint(HDC hdc);
	// ����KM_ACTIONֵ���������Ϊ
	virtual void GameMouseAction(int x, int y, int ActionType);

	virtual void GameKeyAction(UINT32 KeyChar, int ActionType = KEY_SYS_NONE);

	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int ActionType = KEY_SYS_NONE) {}
};

