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



AudioDX sound::ds;//DirectSound����
AudioDXBuffer sound::menu_over;
AudioDXBuffer sound::menu_click;
AudioDXBuffer sound::backmusic1;//��������
AudioDXBuffer sound::backmusic2;//��������
AudioDXBuffer sound::backmusic3;//��������
AudioDXBuffer sound::playerRun;//������Ч
ManySound sound::shoot;//ǹ��
ManySound sound::boom;//����
ManySound sound::monsterDead;//��������
AudioDXBuffer sound::playerHurt;//��������
AudioDXBuffer sound::speedUp;//�������
ManySound sound::bulletBoom;//�ӵ�����
ManySound sound::blast;
void sound::init(HWND hwnd)
{
	//���DirectSound���󴴽�ʧ�ܷ���
	if (!ds.CreateDS(hwnd)) return;
	//����WAVE �ļ���������������д���Ӧ�Ļ�����
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

	//����Ϸ�
	for (int x = sx; x <= ex; ++x)
	{
		if (map->getPositionTypeByIndex(x, sy, floor))
		{
			colls[DIR_UP] = true;
			res = true;
			break;
		}
	}
	//����·�
	for (int x = sx; x <= ex; ++x)
	{
		if (map->getPositionTypeByIndex(x, ey, floor))
		{
			colls[DIR_DOWN] = true;
			res = true;
			break;
		}
	}
	//�����
	for (int y = sy; y <= ey; ++y)
	{
		if (map->getPositionTypeByIndex(sx, y, floor))
		{
			colls[DIR_LEFT] = true;
			res = true;
			break;
		}
	}
	//����ҷ�
	for (int y = sy; y <= ey; ++y)
	{
		if (map->getPositionTypeByIndex(ex, y, floor))
		{
			colls[DIR_RIGHT] = true;
			res = true;
			break;
		}
	}

	//���ʣ�µ�
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

	//�����ε�
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

