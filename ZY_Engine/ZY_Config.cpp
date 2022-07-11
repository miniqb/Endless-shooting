#include "ZY_Config.h"

RECT zyvar::wndRect{};
POINT zyvar::mousePos{};
bool zyvar::keyChars[256] = {false};
TiledMap* zyvar::tMap = nullptr;
int zyvar::drawSum = 0;
Camera* zyvar::nowCamera;
int zyvar::obstacles = 0;
ZY_Size zyvar::worldSize;
BYTE zyvar::nowKey;
ZY_Engine* zyvar::pEngine;



AudioDX sound::ds;//DirectSound对象
AudioDXBuffer sound::menu_over;
AudioDXBuffer sound::menu_click;
AudioDXBuffer sound::backmusic1;//背景音乐
AudioDXBuffer sound::backmusic2;//背景音乐
AudioDXBuffer sound::backmusic3;//背景音乐
AudioDXBuffer sound::playerRun;//行走音效
ManySound sound::shoot;//枪声
ManySound sound::boom;//地裂
ManySound sound::monsterDead;//怪物死亡
AudioDXBuffer sound::playerHurt;//人物受伤
AudioDXBuffer sound::speedUp;//人物加速
ManySound sound::bulletBoom;//子弹击中
ManySound sound::blast;
void sound::init(HWND hwnd)
{
	//如果DirectSound对象创建失败返回
	if (!ds.CreateDS(hwnd)) return;
	//加载WAVE 文件，并将声音数据写入对应的缓冲区
	backmusic1.LoadWave(ds, L".\\sound\\back_music1.wav");
	playerRun.LoadWave(ds, L".\\sound\\player_run.wav");
	shoot.init(ds, L".\\sound\\fire.wav", 50);
	boom.init(ds, L".\\sound\\boom.wav",10);
	monsterDead.init(ds, L".\\sound\\monster_dead.wav",20);
	playerHurt.LoadWave(ds, L".\\sound\\player_hurt.wav");
	speedUp.LoadWave(ds, L".\\sound\\speedup.wav");
	bulletBoom.init(ds, L".\\sound\\bullet_hurt.wav",50);
	blast.init(ds, L".\\sound\\blast.wav", 50);
	menu_over.LoadWave(ds, L".\\sound\\mouseover.wav");
	menu_click.LoadWave(ds, L".\\sound\\mousedown.wav");
	//GameState = GAME_START;


}

void sound::end()
{
	ds.ReleaseAll();
}

bool MapCollision::TestMapCollision(TiledMap* map, const ZY_Rect& rect, bool colls[],int floor)
{
	Vec2 lowPos = map->getMapIndexXY(rect.origin);
	Vec2 upPos = map->getMapIndexXY(rect.origin + rect.size);

	int sx = (int)lowPos.x;
	int sy = (int)lowPos.y;
	int ex = (int)upPos.x;
	int ey = (int)upPos.y;

	bool res = false;

	//检测上方
	for (int x = sx; x <= ex; ++x)
	{
		if (map->getPositionTypeByIndex(x, sy, floor))
		{
			colls[DIR_UP] = true;
			res = true;
			break;
		}
	}
	//检测下方
	for (int x = sx; x <= ex; ++x)
	{
		if (map->getPositionTypeByIndex(x, ey, floor))
		{
			colls[DIR_DOWN] = true;
			res = true;
			break;
		}
	}
	//检测左方
	for (int y = sy; y <= ey; ++y)
	{
		if (map->getPositionTypeByIndex(sx, y, floor))
		{
			colls[DIR_LEFT] = true;
			res = true;
			break;
		}
	}
	//检测右方
	for (int y = sy; y <= ey; ++y)
	{
		if (map->getPositionTypeByIndex(ex, y, floor))
		{
			colls[DIR_RIGHT] = true;
			res = true;
			break;
		}
	}

	//检测剩下的
	if (!res)
	{
		for (int y = sy+1; y < ey; ++y)
		{
			for (int x = sx+1; x < ex; ++x)
			{
				if (map->getPositionTypeByIndex(x, y, floor))
				{
					res = true;
					return res;
				}
			}
		}
	}

	return res;
}

bool MapCollision::TestMapCollision(TiledMap* map, const ZY_Rect& rect, int floor)
{
	Vec2 lowPos = map->getMapIndexXY(rect.origin);
	Vec2 upPos = map->getMapIndexXY(rect.origin + rect.size);

	int sx = (int)lowPos.x;
	int sy = (int)lowPos.y;
	int ex = (int)upPos.x;
	int ey = (int)upPos.y;

	//检测矩形的
	for (int y = sy; y <= ey; ++y)
	{
		for (int x = sx; x <= ex; ++x)
		{
			if (map->getPositionTypeByIndex(x, y, floor))
			{
				return true;
			}
		}
	}
	return false;
}

