#include "ZY_Graph.h"
ZY_Graph::ZY_Graph():T_Graph()
{

}
ZY_Graph::ZY_Graph(LPTSTR fileName): T_Graph(fileName)
{

}

void ZY_Graph::PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos,const Vec2& srcPos,  int regionWidth, int regionHeight, BYTE alpha)
{
	HDC memDC = CreateCompatibleDC(destDC);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, in_hbitmap);
	BLENDFUNCTION dc_bf{};
	dc_bf.BlendOp = AC_SRC_OVER;
	dc_bf.BlendFlags = 0;
	dc_bf.SourceConstantAlpha = 255;
	dc_bf.AlphaFormat = AC_SRC_ALPHA;

	SetStretchBltMode(destDC, COLORONCOLOR);

	AlphaBlend(destDC, (int)roundf(destPos.x), (int)roundf(destPos.y), regionWidth, regionHeight, memDC, (int)roundf(srcPos.x), (int)roundf(srcPos.y), regionWidth, regionHeight, dc_bf);
	SelectObject(memDC, oldBitmap);
	DeleteObject(oldBitmap);
	DeleteDC(memDC);
}

HBITMAP ZY_Graph::CreateBlankBitmap(HDC hdc, int width, int height, COLORREF color)
{
	HBITMAP aimBitmap = CreateCompatibleBitmap(hdc, width, height);
	HBRUSH brush = CreateSolidBrush(color);
	HDC memHdc = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memHdc, aimBitmap);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = height;
	rect.right = width;

	FillRect(memHdc, &rect, brush);
	SelectObject(memHdc, oldBitmap);
	DeleteObject(brush);
	DeleteDC(memHdc);

	return aimBitmap;
}

void ZY_Graph::PaintRegion(HBITMAP in_hbitmap, HDC destDC, const Vec2& destP, int srcX, int srcY,
	int regionWidth, int regionHeight, const float ratioX, const float ratioY,
	float angle, const Vec2& anchorPoint, int rotType, BYTE alpha)
{
	//׼����4���㣬����ת����ε�4�����λ��
	Vec2 pos[4];
	//�������ź�ߴ�
	Vec2 realSize(regionWidth*ratioX, regionHeight*ratioY);
	//������ת����λ�ã����0��0�㣩
	const Vec2 pivot = realSize * anchorPoint;
	//��ʼ��4����λ�ã�Ϊ���ź�δ��תλ�ã����0��0�㣩
	pos[1].x = realSize.x;
	pos[2].y = realSize.y;
	pos[3].x = realSize.x;
	pos[3].y = realSize.y;
	//��ת4�������������õ���ת���λ���Լ���ת���aabb��
	pos[0].rotate(pivot, angle);
	Vec2 minPos(pos[0]);
	Vec2 maxPos(pos[0]);
	for (size_t i = 1; i < 4; ++i)
	{
		pos[i].rotate(pivot, angle);
		if (pos[i].x < minPos.x) minPos.x = pos[i].x;
		if (pos[i].y < minPos.y) minPos.y = pos[i].y;
		if (pos[i].x > maxPos.x) maxPos.x = pos[i].x;
		if (pos[i].y > maxPos.y) maxPos.y = pos[i].y;
	}

	//������ת���������ת����κ����Ͻ�λ��
	Vec2 aimPos(pivot - minPos);
	//Vec2 aimPos((minPos.x + maxPos.x) / 2, (minPos.y + maxPos.y) / 2);
	//Vec2 aimPos((minPos.x + maxPos.x) / 2, (minPos.y + maxPos.y) / 2);

	//����ת���ι�λ
	for (size_t i = 0; i < 4; ++i)
	{
		pos[i] = pos[i] - minPos;
	}
	//������ת����κеĳߴ�
	maxPos = maxPos - minPos;
	int w = (int)roundf(maxPos.x);
	int h = (int)roundf(maxPos.y);

	//����͸��λͼ,���ڼ�¼�ı���״���λͼ��ͬʱ����͸���ȣ�Ϊ�˱�֤�������Ӱ�죬���һ��
	HBITMAP blankBmp = T_Graph::CreateBlankBitmap(w, h, NULL);
	//�����ڴ�DC
	HDC memDC = CreateCompatibleDC(destDC);
	HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, blankBmp);

	//��������Ŀ��λͼ��DC
	HDC memDC2 = CreateCompatibleDC(destDC);
	HBITMAP oldBmp2 = (HBITMAP)SelectObject(memDC2, in_hbitmap);

	//���һ��ת����һ�ǻ���POINT���ͣ����ǿ��Խ����������ҷ�ת
	POINT points[3]{};
	switch (rotType)
	{
	case TRANS_NONE:
		for (size_t i = 0; i < 3; ++i)
		{
			points[i].x = (LONG)pos[i].x;
			points[i].y = (LONG)pos[i].y;
		}
		break;
	case TRANS_HFLIP_NOROT:
		points[0].x = (LONG)pos[1].x;
		points[0].y = (LONG)pos[1].y;
		points[1].x = (LONG)pos[0].x;
		points[1].y = (LONG)pos[0].y;
		points[2].x = (LONG)pos[3].x;
		points[2].y = (LONG)pos[3].y;
		break;
	case TRANS_VFLIP_NOROT:
		points[0].x = (LONG)pos[2].x;
		points[0].y = (LONG)pos[2].y;
		points[1].x = (LONG)pos[3].x;
		points[1].y = (LONG)pos[3].y;
		points[2].x = (LONG)pos[0].x;
		points[2].y = (LONG)pos[0].y;
		break;
	default:
		for (size_t i = 0; i < 3; ++i)
		{
			points[i].x = (LONG)pos[i].x;
			points[i].y = (LONG)pos[i].y;
		}
		break;
	}

	//������ת���ͼ���µ�λͼ��
	PlgBlt(memDC, points, memDC2, srcX, srcY, regionWidth, regionHeight, NULL, 0, 0);

	BLENDFUNCTION dc_bf{};
	dc_bf.BlendOp = AC_SRC_OVER;
	dc_bf.BlendFlags = 0;
	dc_bf.SourceConstantAlpha = alpha;
	dc_bf.AlphaFormat = AC_SRC_ALPHA;

	//SetStretchBltMode(destDC, COLORONCOLOR);
	//aimPos = destP + aimPos - pivot;
	//float aimh = ratioY * h;
	//float aimw = ratioX * w;
	//�������λ��
	aimPos = destP - aimPos;
	AlphaBlend(destDC,aimPos.x,aimPos.y, w, h, memDC, 0, 0, w, h, dc_bf);

	SelectObject(memDC, oldBmp);
	SelectObject(memDC2, oldBmp2);
	DeleteDC(memDC);
	DeleteDC(memDC2);
	DeleteObject(blankBmp);
	DeleteObject(oldBmp);
	DeleteObject(oldBmp2);
}

void ZY_Graph::PaintRegion2(HBITMAP in_hbitmap, HDC destDC, const Vec2& destPos, int wndW, int wndH,
	int srcX, int srcY, int regionWidth, int regionHeight, const Vec2& ratio, float angle, const Vec2& pivot, int rotType, BYTE alpha)
{
	Vec2 pos[4];
	pos[1].x = (float)regionWidth;
	pos[2].y = (float)regionHeight;
	pos[3].x = (float)regionWidth;
	pos[3].y = (float)regionHeight;

	for (size_t i = 0; i < 3; ++i)
	{
		pos[i].rotate(pivot, angle);
		pos[i] += destPos;
	}

	//����͸��λͼ,���ڼ�¼�ı���״���λͼ��ͬʱ����͸���ȣ�Ϊ�˱�֤�������Ӱ�죬���һ��
	HBITMAP blankBmp = T_Graph::CreateBlankBitmap(wndW, wndH, NULL);
	//�����ڴ�DC
	HDC memDC = CreateCompatibleDC(destDC);
	HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, blankBmp);

	//��������Ŀ��λͼ��DC
	HDC memDC2 = CreateCompatibleDC(destDC);
	HBITMAP oldBmp2 = (HBITMAP)SelectObject(memDC2, in_hbitmap);

	POINT points[3]{};
	switch (rotType)
	{
	case TRANS_NONE:
		for (size_t i = 0; i < 3; ++i)
		{
			points[i].x = (LONG)pos[i].x;
			points[i].y = (LONG)pos[i].y;
		}
		break;
	case TRANS_HFLIP_NOROT:
		points[0].x = (LONG)pos[1].x;
		points[0].y = (LONG)pos[1].y;
		points[1].x = (LONG)pos[0].x;
		points[1].y = (LONG)pos[0].y;
		points[2].x = (LONG)pos[3].x;
		points[2].y = (LONG)pos[3].y;
		break;
	case TRANS_VFLIP_NOROT:
		points[0].x = (LONG)pos[2].x;
		points[0].y = (LONG)pos[2].y;
		points[1].x = (LONG)pos[3].x;
		points[1].y = (LONG)pos[3].y;
		points[2].x = (LONG)pos[0].x;
		points[2].y = (LONG)pos[0].y;
		break;
	default:
		for (size_t i = 0; i < 3; ++i)
		{
			points[i].x = (LONG)pos[i].x;
			points[i].y = (LONG)pos[i].y;
		}
		break;
	}

	//������ת���ͼ���µ�λͼ��
	PlgBlt(memDC, points, memDC2, srcX, srcY, regionWidth, regionHeight, NULL, 0, 0);

	BLENDFUNCTION dc_bf{};
	dc_bf.BlendOp = AC_SRC_OVER;
	dc_bf.BlendFlags = 0;
	dc_bf.SourceConstantAlpha = 255;
	dc_bf.AlphaFormat = AC_SRC_ALPHA;

	//SetStretchBltMode(destDC, COLORONCOLOR);

	AlphaBlend(destDC, 0, 0, wndW, wndH, memDC, 0, 0, wndW, wndH, dc_bf);

	SelectObject(memDC, oldBmp);
	SelectObject(memDC2, oldBmp2);
	DeleteDC(memDC);
	DeleteDC(memDC2);
	DeleteObject(blankBmp);
	DeleteObject(oldBmp);
	DeleteObject(oldBmp2);

}

void ZY_Graph::PaintFrame(HBITMAP in_hbitmap, HDC destDC, Vec2 destP, int FrameCount, int RowFrames, int wFrame, int hFrame, float angle, float ratioX, float ratioY, const Vec2& anchorPoint, int rotType, BYTE alpha)
{
	int col = FrameCount % RowFrames;
	int row = (FrameCount - col) / RowFrames;
	PaintRegion(in_hbitmap, destDC, destP, col * wFrame, row * hFrame, wFrame, hFrame, ratioX, ratioY, angle, anchorPoint,rotType,alpha);
}

void ZY_Graph::PaintFrame2(HBITMAP in_hbitmap, HDC destDC, Vec2 destP, int wndW, int wndH, int FrameCount, int RowFrames, int wFrame, int hFrame, float angle, float ratio, int rotType, BYTE alpha)
{
	int col = FrameCount % RowFrames;
	int row = (FrameCount - col) / RowFrames;
	PaintRegion2(in_hbitmap, destDC, destP, wndW, wndH, col * wFrame, row * hFrame, wFrame, hFrame, Vec2(ratio, ratio), angle, Vec2(wFrame / 2.f, hFrame / 2.f), rotType, alpha);

}

T_Graph OtherGraphs::heart;
void OtherGraphs::init()
{
	heart.LoadImageFile(L"res/other/heart.png");
}

T_Graph BoomGraphs::bulletBoom;
T_Graph BoomGraphs::creak;
T_Graph BoomGraphs::explosion;
void BoomGraphs::init()
{
	bulletBoom.LoadImageFile(L"res/boom/bulletBoom.png");
	creak.LoadImageFile(L"res/boom/crack.png");
	explosion.LoadImageFile(L"res/boom/explosion.png");
}


T_Graph BulletGraphs::bullet;
T_Graph BulletGraphs::fire;
T_Graph BulletGraphs::note;
T_Graph BulletGraphs::rebound;
T_Graph BulletGraphs::through;
T_Graph BulletGraphs::boom;
T_Graph BulletGraphs::split;
T_Graph BulletGraphs::npc;
void BulletGraphs::init()
{
	bullet.LoadImageFile(L"res/bullet/bullet.png");
	fire.LoadImageFile(L"res/bullet/fire.png");
	note.LoadImageFile(L"res/bullet/note.png");
	rebound.LoadImageFile(L"res/bullet/rebound.png");
	through.LoadImageFile(L"res/bullet/through.png");
	boom.LoadImageFile(L"res/bullet/boom.png");
	split.LoadImageFile(L"res/bullet/split.png");
	npc.LoadImageFile(L"res/bullet/npc.png");
}


 T_Graph MonsterGraphs::player;
 T_Graph MonsterGraphs::bat;
 T_Graph MonsterGraphs::bird;
 T_Graph MonsterGraphs::cdragon;
 T_Graph MonsterGraphs::chicken;
 T_Graph MonsterGraphs::cow;
 T_Graph MonsterGraphs::death;
 T_Graph MonsterGraphs::dragon;
 T_Graph MonsterGraphs::dragon2;
 T_Graph MonsterGraphs::fire;
 T_Graph MonsterGraphs::gost;
 T_Graph MonsterGraphs::lizard;
 T_Graph MonsterGraphs::mummy;
 T_Graph MonsterGraphs::skeleton;
 T_Graph MonsterGraphs::snake;
 T_Graph MonsterGraphs::stone;
 T_Graph MonsterGraphs::vampire;
 T_Graph MonsterGraphs::wolf;
 T_Graph MonsterGraphs::zombies;
void MonsterGraphs::init()
{
	player.LoadImageFile(L"res/monster/player.png");
	bat.LoadImageFile(L"res/monster/m_bat.png");
	bird.LoadImageFile(L"res/monster/m_bird.png");
	cdragon.LoadImageFile(L"res/monster/m_cdragon.png");
	chicken.LoadImageFile(L"res/monster/m_chicken.png");
	cow.LoadImageFile(L"res/monster/m_cow.png");
	death.LoadImageFile(L"res/monster/m_death.png");
	dragon.LoadImageFile(L"res/monster/m_dragon.png");
	dragon2.LoadImageFile(L"res/monster/m_dragon2.png");
	fire.LoadImageFile(L"res/monster/m_fire.png");
	gost.LoadImageFile(L"res/monster/m_gost.png");
	lizard.LoadImageFile(L"res/monster/m_lizard.png");
	mummy.LoadImageFile(L"res/monster/m_mummy.png");
	skeleton.LoadImageFile(L"res/monster/m_skeleton.png");
	snake.LoadImageFile(L"res/monster/m_snake.png");
	stone.LoadImageFile(L"res/monster/m_stone.png");
	vampire.LoadImageFile(L"res/monster/m_vampire.png");
	wolf.LoadImageFile(L"res/monster/m_wolf.png");
	zombies.LoadImageFile(L"res/monster/m_zombies.png");
}

T_Graph GunGraphs::pistol;
T_Graph GunGraphs::revolver;
T_Graph GunGraphs::rifle;
T_Graph GunGraphs::shotgun;
T_Graph GunGraphs::boss;

void GunGraphs::init()
{
	pistol.LoadImageFile(L"res/gun/pistol.png");
	revolver.LoadImageFile(L"res/gun/revolver.png");
	rifle.LoadImageFile(L"res/gun/rifle.png");
	shotgun.LoadImageFile(L"res/gun/shotgun.png");
	boss.LoadImageFile(L"res/gun/boss.png");

}

T_Graph PropsGraphs::boom;
T_Graph PropsGraphs::note;
T_Graph PropsGraphs::rebound;
T_Graph PropsGraphs::through;
T_Graph PropsGraphs::rifle;
T_Graph PropsGraphs::shotgun;
T_Graph PropsGraphs::revolver;
T_Graph PropsGraphs::boss;
void PropsGraphs::init()
{
	boom.LoadImageFile(L"res/props/boom.png");
	note.LoadImageFile(L"res/props/note.png");
	rebound.LoadImageFile(L"res/props/rebound.png");
	through.LoadImageFile(L"res/props/through.png");
	rifle.LoadImageFile(L"res/props/rifle.png");
	shotgun.LoadImageFile(L"res/props/shotgun.png");
	revolver.LoadImageFile(L"res/props/revolver.png");
	boss.LoadImageFile(L"res/props/boss.png");
}

T_Graph MenuGraphs::main;
T_Graph MenuGraphs::other;
T_Graph MenuGraphs::pause;
void MenuGraphs::init()
{
	main.LoadImageFile(L"res/menu/main.png");
	other.LoadImageFile(L"res/menu/other.png");
	pause.LoadImageFile(L"res/menu/pause.png");
}
