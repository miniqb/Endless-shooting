#include "GameEngine.h"
#include "GameScene.h"
#include "MainMenuSceen.h"

GameEngine::GameEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth, int iHeight, COLORREF bkColor):
	ZY_Engine(hInstance,szWindowClass,szTitle,Icon,SmIcon,iWidth,iHeight,bkColor)
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::GameInit()
{
	Node::SetWindowSize(wndWidth, wndHeight);
	zyvar::pEngine = (ZY_Engine*)pEngine;
	//¼ÓÔØÍ¼Æ¬×ÊÔ´

	BoomGraphs::init();
	BulletGraphs::init();
	MonsterGraphs::init();
	GunGraphs::init();
	PropsGraphs::init();

	scene = new MainMenuSceen();
	scene->init();
	sound::init(m_hWnd);
}

void GameEngine::GameLogic()
{
	//scene->update(this->realFreamTime);
	//((GameScene*)scene)->updateCameraPos();
	//cout << this->realFreamTime << endl;
	scene->update(this->f_IntervalTime);
	//scene->update(this->f_IntervalTime);
	//
}

void GameEngine::GameEnd()
{
	scene->release();
	delete scene;
	scene = nullptr;
	//sound::end();
}

void GameEngine::GamePaint(HDC hdc)
{
	scene->draw(hdc);
}

void GameEngine::GameMouseAction(int x, int y, int ActionType)
{
	scene->handleInput(x, y, ActionType);
}

void GameEngine::GameKeyAction(UINT32 KeyChar, int ActionType)
{
	scene->handleInput(KeyChar, ActionType);
}
