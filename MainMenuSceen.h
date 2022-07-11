#pragma once
#include "./ZY_Engine/Scene.h"
#include "TinyEngine/T_Menu.h"
class MainMenuSceen :
    public Scene
{
public:
	MainMenuSceen();
	~MainMenuSceen();

	virtual void init()override;
	virtual void handleInput(UINT32 KeyChar, int ActionType);
	virtual void handleInput(int x, int y, int ActionType);//Êó±êÊÂ¼þ
protected:
	virtual void updateSelf(float dt) override;
	virtual void drawSelf(HDC hdc) override;

private:
	void initMenu();
	void drawMain(HDC hdc);
	void drawHelp(HDC hdc);
	void drawAbout(HDC hdc);
	
	void releaseMenu();
	void allMenuDeal(int i);
	void mainMenuDeal(int i);
	void helpMenuDeal(int i);
	void aboutMenuDeal(int i);
	void selectMenuDeal(int i);

	T_Menu* menu;
	T_Menu* helpMenu;
	T_Menu* aboutMenu;
	T_Menu* mainMenu;
	T_Menu* selectMenu;

	T_Graph zqb;
	T_Graph yjl;
	T_Graph klw;

	int gameMode;
};

