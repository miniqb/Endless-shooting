#include "MainMenuSceen.h"
#include "ZY_Engine/ZY_Config.h"
#include "GameScene.h"

MainMenuSceen::MainMenuSceen()
{
}

MainMenuSceen::~MainMenuSceen()
{
	releaseMenu();
}

void MainMenuSceen::init()
{
	initMenu();
}

void MainMenuSceen::handleInput(UINT32 KeyChar, int ActionType)
{
	if (menu)
	{
		if (ActionType == KEY_DOWN)
		{
			menu->MenuKeyDown(KeyChar);
		}
		if (KeyChar == VK_RETURN)
		{
			allMenuDeal(menu->GetMenuIndex());
		}
	}
}

void MainMenuSceen::handleInput(int x, int y, int ActionType)
{
	if (ActionType == MOUSE_MOVE)
	{
		menu->MenuMouseMove(x,y);
	}
	else if (ActionType == MOUSE_LCLICK)
	{
		menu->MenuMouseClick(x, y);
		int index = menu->GetMenuIndex();
		allMenuDeal(index);
	}
}

void MainMenuSceen::updateSelf(float dt)
{
	
}

void MainMenuSceen::drawSelf(HDC hdc)
{
	menu->DrawMenu(hdc);
	switch (gameMode)
	{
	case GAME_START:
		drawMain(hdc);
		break;
	case GAME_ABOUT:
		drawAbout(hdc);
		break;
	case GAME_HELP:
		drawHelp(hdc);
		break;
	default:
		break;
	}
}

void MainMenuSceen::initMenu()
{
	//���˵�
	mainMenu = new T_Menu();
	{
		mainMenu->SetMenuBkg(L"res/menu/back.png");
		MENU_INFO info;
		info.align = 1;
		info.focusTextColor = Color::Yellow;
		info.fontName = L"����";
		info.height = 64;
		info.isBold = true;
		info.normalTextColor = Color::White;
		info.width = 180;
		info.space = 10;
		mainMenu->SetMenuInfo(info);
		mainMenu->SetBtnBmp(L"res/menu/main.png", 180, 64);
		mainMenu->SetMoveSound(&sound::menu_over);
		mainMenu->SetClickSound(&sound::menu_click);
		MENUITEM item;
		item.ItemName = L"��ʼ��Ϸ";
		item.pos.x = 100;
		item.pos.y = 100;
		mainMenu->AddMenuItem(item);
		item.pos.x = 200;
		item.pos.y = 200;
		item.ItemName = L"����";
		mainMenu->AddMenuItem(item);
		item.pos.x = 300;
		item.pos.y = 300;
		item.ItemName = L"������Ϸ";
		mainMenu->AddMenuItem(item);
		item.pos.x = 400;
		item.pos.y = 400;
		item.ItemName = L"�˳���Ϸ";
		mainMenu->AddMenuItem(item);
		menu = mainMenu;
	}

	selectMenu = new T_Menu();
	{
		MENU_INFO info;
		info.align = 1;
		info.focusTextColor = Color::Yellow;
		info.fontName = L"����";
		info.height = 100;
		info.isBold = true;
		info.normalTextColor = Color::White;
		info.width = 300;
		info.space = 10;
		selectMenu->SetMenuInfo(info);
		selectMenu->SetMenuBkg(L"res/menu/back.png");
		selectMenu->SetBtnBmp(L"res/menu/other.png", 121, 121);
		selectMenu->SetMoveSound(&sound::menu_over);
		selectMenu->SetClickSound(&sound::menu_click);
		MENUITEM item;
		item.ItemName = L"��ͨģʽ";
		item.pos.x = 100;
		item.pos.y = 100;
		selectMenu->AddMenuItem(item);
		item.pos.x = 200;
		item.pos.y = 200;
		item.ItemName = L"ר��ģʽ";
		selectMenu->AddMenuItem(item);
		item.pos.x = 300;
		item.pos.y = 300;
		item.ItemName = L"��ʦģʽ";
		selectMenu->AddMenuItem(item);
		item.pos.x = 400;
		item.pos.y = 400;
		item.ItemName = L"����";
		selectMenu->AddMenuItem(item);
	}

	//��ʼ�����������ڲ˵�
	T_Menu* ahMenu = new T_Menu();
	{
		int btn_width = 120;
		int btn_height = 120;
		MENU_INFO menuinfo;
		{
			menuinfo.align = 1;
			menuinfo.space = MENU_SPACE;
			menuinfo.width = btn_width;
			menuinfo.height = btn_height;
			menuinfo.fontName = L"΢���ź�";
			menuinfo.isBold = true;
			menuinfo.normalTextColor = Color::White;
			menuinfo.focusTextColor = Color::Yellow;
		}
		ahMenu->SetMenuInfo(menuinfo);
		ahMenu->SetMenuBkg(L"res/menu/back.png");
		ahMenu->SetBtnBmp(L"res/menu/other.png", 121, 121);
		ahMenu->SetMoveSound(&sound::menu_over);
		ahMenu->SetClickSound(&sound::menu_click);

		int x = (wndWidth - btn_width) / 2;
		int y = wndHeight * 4 / 5;;
		MENUITEM mItem;
		wstring menuItems[] = { L"����",L"��ʼ",L"�˳�" };
		for (int i = 0; i < 3; ++i)
		{
			mItem.pos.x = i * (btn_width + MENU_SPACE) + (wndWidth - 3 * btn_width - 2 * MENU_SPACE) / 2;
			mItem.pos.y = y;
			mItem.ItemName = menuItems[i];
			ahMenu->AddMenuItem(mItem);
		}
		aboutMenu = ahMenu;
		helpMenu = ahMenu;
	}

	//����ͷ��
	zqb.LoadImageFile(L".\\res\\headImg\\z.png");
	yjl.LoadImageFile(L".\\res\\headImg\\y.jpg");
	klw.LoadImageFile(L".\\res\\headImg\\k.jpg");
}

void MainMenuSceen::releaseMenu()
{
	//delete helpMenu;
	delete aboutMenu;
	delete mainMenu;
	delete selectMenu;
}

void MainMenuSceen::drawMain(HDC hdc)
{
	RectF rect;
	rect.X = 0;
	rect.Y = 0;
	rect.Width = (float)wndWidth;
	rect.Height = (float)wndHeight / 4.f;
	T_Graph::PaintText(hdc, rect, L"�޾���� 1.0", 36, L"΢���ź�");
}

void MainMenuSceen::drawHelp(HDC hdc)
{
	RectF rect;
	//��͸������
	rect.X = wndWidth * 0.2f;
	rect.Y = wndHeight * 0.1f;
	rect.Width = wndWidth * 0.6f;
	rect.Height = wndHeight * 0.6f;
	T_Graph::PaintBlank(hdc, (int)rect.X, (int)rect.Y,
		(int)rect.Width, (int)rect.Height, RGB(0, 0, 0), 100);
	//��������
	rect.Height = 60;
	rect.Y += 20;
	T_Graph::PaintText(hdc, rect, L"����", 28, L"΢���ź�");
	//����
	rect.Y += rect.Height / 2;
	rect.Height = wndHeight * 0.6f - rect.Height;
	T_Graph::PaintText(hdc, rect, L"w a s d          �ƶ�\n������         ���\n  q          ̩ɽѹ��\n  e          �޵м���",
		20, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentCenter);

}

void MainMenuSceen::drawAbout(HDC hdc)
{
	RectF rect;
	//������͸��
	T_Graph::PaintBlank(hdc, wndWidth * 0.1f, 10, wndWidth * 0.8f, wndHeight * 0.75f, RGB(0, 0, 0), 100);
	//�����ڡ�����
	rect.Width = wndWidth * 0.6f;
	rect.Height = 40;
	rect.X = (wndWidth - rect.Width) / 2;
	rect.Y = 20;
	T_Graph::PaintText(hdc, rect, L"��   ��", 28, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentCenter);
	//ѡ�ΰࡢԭ�༶
	//rect.X += rect.Width * 0.25f;
	rect.Y += rect.Height;
	rect.Height = 60;
	T_Graph::PaintText(hdc, rect,
		L"\n�޾����   1.0�汾\n",
		14, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentCenter);
	//��Ա
	// ��
	rect.Y += rect.Height;
	rect.Height = zqb.GetImageHeight() * 0.05 + 10;
	T_Graph::PaintRegion(zqb.GetBmpHandle(), hdc, rect.X, rect.Y, 0, 0,
		zqb.GetImageWidth(), zqb.GetImageHeight(), 0.05, TRANS_HFLIP_NOROT, 255);
	rect.X += zqb.GetImageWidth() * 0.05;
	T_Graph::PaintText(hdc, rect,
		L"���岨\nѡ�ΰ༶��ѡ��2��   ԭ�༶���������1903��\n8002119079\n�ֹ�������������\n123456\n",
		12, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentNear);

	//��
	rect.X = (wndWidth - rect.Width) / 2;
	rect.Y += rect.Height;
	rect.Height = yjl.GetImageHeight() * 0.05 + 10;
	yjl.PaintRegion(yjl.GetBmpHandle(), hdc, rect.X, rect.Y, 0, 0,
		yjl.GetImageWidth(), yjl.GetImageHeight(), 0.05, TRANS_HFLIP_NOROT, 255);
	rect.X += yjl.GetImageWidth() * 0.05;
	T_Graph::PaintText(hdc, rect,
		L"�����\nѡ�ΰ༶��ѡ��2��   ԭ�༶���������1903��\n8002119067\n�ֹ�������������\n123456\n",
		12, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentNear);

	//��
	rect.X = (wndWidth - rect.Width) / 2;
	rect.Y += rect.Height;
	rect.Height = klw.GetImageHeight() * 0.1 + 10;
	klw.PaintRegion(klw.GetBmpHandle(), hdc, rect.X, rect.Y, 0, 0,
		klw.GetImageWidth(), klw.GetImageHeight(), 0.1, TRANS_HFLIP_NOROT, 255);
	rect.X += klw.GetImageWidth() * 0.1;
	T_Graph::PaintText(hdc, rect,
		L"������\nѡ�ΰ༶��ѡ��2��   ԭ�༶���������1902��\n8002119063\n�ֹ�������������\n123456\n",
		12, L"΢���ź�", Color::White, FontStyle::FontStyleRegular, StringAlignment::StringAlignmentNear);

}

void MainMenuSceen::allMenuDeal(int i)
{
	if (menu == NULL)
	{
		return;
	}
	menu->SetMenuIndex(-1);
	switch (gameMode)
	{
	case GAME_START:
	{
		mainMenuDeal(i);
	}
	break;
	case GAME_RUN:
	{
		selectMenuDeal(i);
	}
	break;
	case GAME_ABOUT:
	{
		aboutMenuDeal(i);
	}
	break;
	case GAME_HELP:
	{
		helpMenuDeal(i);
	}
	break;
	default:
		break;
	}
}

void MainMenuSceen::mainMenuDeal(int index)
{
	switch (index)
	{
	case 0://����Ϸ
	{
		gameMode = GAME_RUN;
		menu = selectMenu;
	}
	break;
	case 1://����
	{
		gameMode = GAME_HELP;
		menu = helpMenu;
	}
	break;
	case 2://����
	{
		gameMode = GAME_ABOUT;
		menu = aboutMenu;
	}
	break;
	case 3://�˳�
	{
		ZY_Engine::Exist();
	}
	break;
	default:
		break;
	}
}

void MainMenuSceen::helpMenuDeal(int index)
{
	switch (index)
	{
	case 0://����
	{
		gameMode = GAME_START;
		menu = mainMenu;
	}
	break;
	case 1://��ʼ
	{
		gameMode = GAME_RUN;
		menu = selectMenu;
	}
	break;
	case 2://�˳�
	{
		ZY_Engine::Exist();
	}
	break;
	default:
		break;
	}
}

void MainMenuSceen::aboutMenuDeal(int index)
{
	switch (index)
	{
	case 0://����
	{
		gameMode = GAME_START;
		menu = mainMenu;
	}
	break;
	case 1://��ʼ
	{
		gameMode = GAME_RUN;
		menu = selectMenu;
	}
	break;
	case 2://�˳�
	{
		ZY_Engine::Exist();
	}
	break;
	default:
		break;
	}
}

void MainMenuSceen::selectMenuDeal(int index)
{
	switch (index)
	{
	case 0://��ͨ
	{
		gameMode = GAME_START;
		GameScene* scene = new GameScene();
		scene->setMusic(&sound::backmusic1);
		scene->setMode(GameScene::NORMAL);
		scene->init();
		zyvar::pEngine->changeScene(scene);
	}
	break;
	case 1://ר��
	{
		gameMode = GAME_RUN;
		GameScene* scene = new GameScene();
		scene->setMusic(&sound::backmusic1);
		scene->setMode(GameScene::EXPERT);
		scene->init();
		zyvar::pEngine->changeScene(scene);
	}
	break;
	case 2://��ʦ
	{
		GameScene* scene = new GameScene();
		scene->setMusic(&sound::backmusic1);
		scene->setMode(GameScene::MASTER);
		scene->init();
		zyvar::pEngine->changeScene(scene);
	}
	break;
	case 3://����
	{
		gameMode = GAME_START;
		menu = mainMenu;
	}
	break;
	default:
		break;
	}
}
