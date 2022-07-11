#include "ZY_Engine.h"

ZY_Engine::ZY_Engine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth, int iHeight, COLORREF bkColor)
	:T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight, bkColor),realFreamTime(0),f_IntervalTime(0)
{
}

ZY_Engine::~ZY_Engine()
{
}

LRESULT ZY_Engine::GameEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (msg)
	{
	case WM_SETFOCUS:
		SetSleep(FALSE);
		return 0;
	case WM_KILLFOCUS:
		SetSleep(TRUE);
		return 0;
	case WM_CREATE:
		m_hWnd = hWnd;
		GameInit();
		return 0;
	case WM_LBUTTONDOWN: //鼠标左键按下的处理
		GameMouseAction(LOWORD(lParam), HIWORD(lParam), MOUSE_LCLICK);
		return 0;
	case WM_MOUSEMOVE: //鼠标移动处理
		GameMouseAction(LOWORD(lParam), HIWORD(lParam), MOUSE_MOVE);
		return 0;
	case WM_KEYDOWN: //键被按下的处理

		// 记录对应的按键状态
		zyvar::keyChars[wParam] = true;
		zyvar::nowKey = wParam;
		// 执行游戏按键行为
		GameKeyAction(wParam, KEY_DOWN);
		// 附加按键行为处理
		SubKeyAction(wParam);

		return 0;
	case WM_KEYUP:  //释放按键处理
		//keys[wParam] = false;
		zyvar::keyChars[wParam] = false;
		GameKeyAction(wParam, KEY_UP);
		return 0;
	case WM_NCLBUTTONDBLCLK:  //禁止双击窗口标题栏最大化窗口 
		if (HTCAPTION == wParam)
		{
			return 0;
		}
	case WM_SYSCOMMAND:
		if (wParam == SC_MAXIMIZE)
		{
			m_bFullScreen = !m_bFullScreen; // 设置全屏显示标志
			if (m_bFullScreen)
			{
				GetWindowRect(hWnd, &m_rcOld);//记住当前窗口的尺寸
				style = GetWindowLong(hWnd, GWL_STYLE);
				ex_style = GetWindowLong(hWnd, GWL_EXSTYLE);
				p_disp->SaveMode();
				//全屏幕显示
				HWND hDesktop;
				RECT rc;
				hDesktop = GetDesktopWindow();	//获取桌面窗口的指针  
				GetWindowRect(hDesktop, &rc);	//得到桌面窗口的矩形
				p_disp->ChangeMode(wndWidth, wndHeight);
				// 设置为WS_DLGFRAME、WS_BORDER或
				//  WS_EX_CLIENTEDGE都可以去掉标题栏
				// 设置扩展风格为WS_EX_WINDOWEDGE，去掉窗口边框
				SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_WINDOWEDGE);
				SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);
				SetWindowPos(hWnd, HWND_TOP, -1, -1,
					rc.right, rc.bottom, SWP_SHOWWINDOW);
			}
		}
		else if (wParam == SC_CLOSE)
		{
			if (IDOK == MessageBox(NULL, L"你确定要退出吗？",
				wndTitle, MB_OKCANCEL | MB_ICONQUESTION))
			{
				DestroyWindow(hWnd);
			}
		}
		else
		{
			//由于WM_SYSCOMMAND消息不是由程序控制的，
			//所以必须将该消息传给DefWindowProc,否则会造成其他消息无法处理
			return DefWindowProc(hWnd, WM_SYSCOMMAND, wParam, lParam);
		}
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_PAINT: //窗口绘制
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		GamePaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY: //程序销毁
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void ZY_Engine::changeScene(Scene* s)
{
	scene->release();
	delete scene;
	scene = s;
}

void ZY_Engine::StartEngine()
{
	MSG msg;
	GameWinInit();						// 初始化游戏窗口
	srand((unsigned)time(NULL));	// 初始化随机数
	timeBeginPeriod(1);
	lastTick = chrono::steady_clock::now();
	// 游戏主循环
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// 如果侦测到WM_QUIT则退出游戏循环
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 确保游戏没有进入睡眠状态
			if (!GetSleep())
			{
				long waitTime = 0l;
				// 判读游戏循环的时间
				nowTick = chrono::steady_clock::now();
				chrono::duration<float> elapsed = nowTick - lastTick;
				realFreamTime = elapsed.count();
				if (realFreamTime > f_IntervalTime)
				{
					lastTick = nowTick;
					//处理游戏逻辑
					recordInput();
					GameLogic();
					if (quickRender == FALSE)
					{
						//在内存中绘制内容
						GamePaint(bufferDC);
#if SHOW_FPS
						if (showFream)
						{
							ShowFream(bufferDC);
						}
#endif // SHOW_FPS
						//获取游戏窗口句柄及绘图设备
						HDC hDC = GetDC(m_hWnd);
						//将内存设备中绘制的内容绘到屏幕上
						BitBlt(hDC, 0, 0, wndWidth, wndHeight, bufferDC, 0, 0, SRCCOPY);
						//释放设备
						ReleaseDC(m_hWnd, hDC);
					}
				}
				else
				{
					waitTime = static_cast<LONG>((f_IntervalTime - realFreamTime) * 1000-2L);
					if (waitTime > 1L)
						Sleep(waitTime);
				}
			}
		}
	}
	//pEngine->GameEnd();  // 游戏结束处理
	GameEnd();
	timeEndPeriod(1);
}

void ZY_Engine::SetShowFream(bool s)
{
	showFream = s;
}

void ZY_Engine::Exist()
{
	SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}

void ZY_Engine::recordInput()
{
	GetWindowRect(m_hWnd, &zyvar::wndRect);
	
	GetCursorPos(&zyvar::mousePos);
	ScreenToClient(m_hWnd, &zyvar::mousePos);
}
