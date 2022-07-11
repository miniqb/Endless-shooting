#pragma once
#ifndef _ZY_ENGINE_H_
#define  _ZY_ENGINE_H_

#include "../TinyEngine/T_Engine.h"
#include "ZY_Config.h"
#include "Scene.h"
#include "ZY_Graph.h"
#define SHOW_FPS 1

class ZY_Engine :
    public T_Engine
{
protected:
	Scene *scene;

    chrono::time_point<chrono::steady_clock> nowTick;	//��ǰ֡��ʼʱ��
    chrono::time_point<chrono::steady_clock> lastTick;	//��һ֡��ʼʱ��

	float f_IntervalTime;
	float inline GetInterval() { return f_IntervalTime; }
#if SHOW_FPS
	wchar_t str[8]{ 0 };
	float realFreamTime;                 //ʵ����Ϸ֡ˢ�¼��ʱ��
	bool showFream;                      //�Ƿ���ʾ֡��
	void inline ShowFream(HDC hdc) {
		swprintf_s(str, TEXT("%.1f"), 1.f / realFreamTime);
		RectF rect;
		rect.X = wndWidth - 40.f;
		rect.Y = 0;
		rect.Height = 20.f;
		rect.Width = 40.f;
		ZY_Graph::PaintText(hdc, rect, str, 10, L"����");
	}
public:
	void SetFrame(float iTime) { f_IntervalTime = 1.f / iTime; }
#endif // SHOW_FPS

public:
	// ���캯��
	ZY_Engine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	// ��������
	virtual ~ZY_Engine();
	virtual LRESULT GameEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void changeScene(Scene* s);
public:
	// ������������
	virtual void StartEngine();
	void SetShowFream(bool s);


	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int ActionType = KEY_SYS_NONE) {}
	virtual void GameKeyAction(UINT32 KeyChar, int ActionType = KEY_SYS_NONE) = 0;

	static void Exist();
private:
	void recordInput();
};

#endif // !_ZY_ENGINE_H_

