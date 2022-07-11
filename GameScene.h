#pragma once
#include "./ZY_Engine/Scene.h"
#include "./ZY_Engine/TiledMap.h"
#include "BlockSprite.h"
#include "PlayerSprite.h"
#include "./ZY_Engine/Bullet.h"
#include "MonsterFactory.h"
#include "MonsterBulider.h"
#include "TinyEngine/T_Menu.h"
class GameScene :
    public Scene
{
public:
	GameScene();
	~GameScene();

	static const int NORMAL = 0;
	static const int EXPERT = 1;
	static const int MASTER = 2;

	virtual void init()override;
	virtual void handleInput(UINT32 KeyChar, int ActionType);
	virtual void handleInput(int x, int y, int ActionType);// Û±Í ¬º˛
	void updateCamera();
	void setMusic(AudioDXBuffer* m) { backmusic = m; }
	void setMode(int m) { mode = m; }
protected:
	virtual void updateSelf(float dt) override;
	virtual void drawSelf(HDC hdc) override;

private:
	void initMenu();
	void releaseMenu();
	void allMenuDeal(int i);
	void pauseMenuDeal(int i);
	void runMenuDeal(int i);
	void deadMenuDeal(int i);
	void initPlayer();

	void initMonsteBuilder();
	void initMap();
	void drawHitNumber(HDC hdc);

	PlayerSprite* player;
	ZY_Rect world_rect;
	TiledMap* tmap;
	TiledMap* coverMap;
	MonsterBulider builder;
	T_Menu* menu;
	T_Menu* runMenu;
	T_Menu* pauseMenu;
	T_Menu* deadMenu;

	AudioDXBuffer* backmusic;//±≥æ∞“Ù¿÷
	int gameMode;

	int mode;
};

