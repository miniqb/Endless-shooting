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
	case WM_LBUTTONDOWN: //���������µĴ���
		GameMouseAction(LOWORD(lParam), HIWORD(lParam), MOUSE_LCLICK);
		return 0;
	case WM_MOUSEMOVE: //����ƶ�����
		GameMouseAction(LOWORD(lParam), HIWORD(lParam), MOUSE_MOVE);
		return 0;
	case WM_KEYDOWN: //�������µĴ���

		// ��¼��Ӧ�İ���״̬
		zyvar::keyChars[wParam] = true;
		zyvar::nowKey = wParam;
		// ִ����Ϸ������Ϊ
		GameKeyAction(wParam, KEY_DOWN);
		// ���Ӱ�����Ϊ����
		SubKeyAction(wParam);

		return 0;
	case WM_KEYUP:  //�ͷŰ�������
		//keys[wParam] = false;
		zyvar::keyChars[wParam] = false;
		GameKeyAction(wParam, KEY_UP);
		return 0;
	case WM_NCLBUTTONDBLCLK:  //��ֹ˫�����ڱ�������󻯴��� 
		if (HTCAPTION == wParam)
		{
			return 0;
		}
	case WM_SYSCOMMAND:
		if (wParam == SC_MAXIMIZE)
		{
			m_bFullScreen = !m_bFullScreen; // ����ȫ����ʾ��־
			if (m_bFullScreen)
			{
				GetWindowRect(hWnd, &m_rcOld);//��ס��ǰ���ڵĳߴ�
				style = GetWindowLong(hWnd, GWL_STYLE);
				ex_style = GetWindowLong(hWnd, GWL_EXSTYLE);
				p_disp->SaveMode();
				//ȫ��Ļ��ʾ
				HWND hDesktop;
				RECT rc;
				hDesktop = GetDesktopWindow();	//��ȡ���洰�ڵ�ָ��  
				GetWindowRect(hDesktop, &rc);	//�õ����洰�ڵľ���
				p_disp->ChangeMode(wndWidth, wndHeight);
				// ����ΪWS_DLGFRAME��WS_BORDER��
				//  WS_EX_CLIENTEDGE������ȥ��������
				// ������չ���ΪWS_EX_WINDOWEDGE��ȥ�����ڱ߿�
				SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_WINDOWEDGE);
				SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);
				SetWindowPos(hWnd, HWND_TOP, -1, -1,
					rc.right, rc.bottom, SWP_SHOWWINDOW);
			}
		}
		else if (wParam == SC_CLOSE)
		{
			if (IDOK == MessageBox(NULL, L"��ȷ��Ҫ�˳���",
				wndTitle, MB_OKCANCEL | MB_ICONQUESTION))
			{
				DestroyWindow(hWnd);
			}
		}
		else
		{
			//����WM_SYSCOMMAND��Ϣ�����ɳ�����Ƶģ�
			//���Ա��뽫����Ϣ����DefWindowProc,��������������Ϣ�޷�����
			return DefWindowProc(hWnd, WM_SYSCOMMAND, wParam, lParam);
		}
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_PAINT: //���ڻ���
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		GamePaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY: //��������
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
	GameWinInit();						// ��ʼ����Ϸ����
	srand((unsigned)time(NULL));	// ��ʼ�������
	timeBeginPeriod(1);
	lastTick = chrono::steady_clock::now();
	// ��Ϸ��ѭ��
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �����⵽WM_QUIT���˳���Ϸѭ��
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ȷ����Ϸû�н���˯��״̬
			if (!GetSleep())
			{
				long waitTime = 0l;
				// �ж���Ϸѭ����ʱ��
				nowTick = chrono::steady_clock::now();
				chrono::duration<float> elapsed = nowTick - lastTick;
				realFreamTime = elapsed.count();
				if (realFreamTime > f_IntervalTime)
				{
					lastTick = nowTick;
					//������Ϸ�߼�
					recordInput();
					GameLogic();
					if (quickRender == FALSE)
					{
						//���ڴ��л�������
						GamePaint(bufferDC);
#if SHOW_FPS
						if (showFream)
						{
							ShowFream(bufferDC);
						}
#endif // SHOW_FPS
						//��ȡ��Ϸ���ھ������ͼ�豸
						HDC hDC = GetDC(m_hWnd);
						//���ڴ��豸�л��Ƶ����ݻ浽��Ļ��
						BitBlt(hDC, 0, 0, wndWidth, wndHeight, bufferDC, 0, 0, SRCCOPY);
						//�ͷ��豸
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
	//pEngine->GameEnd();  // ��Ϸ��������
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
