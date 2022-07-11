#include "GameScene.h"
#include "./ZY_Engine/ZY_Config.h"
#include "Props.h"
#include "MainMenuSceen.h"
#include "TinyEngine/T_Util.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	builder.release();
	PropsFactor::release();
	CollisionBody::releaseTrees();
	releaseMenu();
	backmusic->Terminate();
	BlockSprite::setMonsterSum(0);
	BlockSprite::setDeadSum(0);
}

void GameScene::init()
{
	gameMode = GAME_RUN;
	//��ʼ������
	backmusic->Restore();
	backmusic->Play(true);

	//��ʼ����������
	Sprite::SetCamera(_camera);
	TiledMap::SetCamera(_camera);
	Weapons::initCamera(_camera);

	//�����������СΪ���ڴ�С
	_camera->setContentSize(ZY_Size(wndWidth, wndHeight));
	_camera->setAnchorPoint(Vec2(0.5, 0.5));
	_camera->setPosition(Vec2(wndWidth / 2, wndHeight / 2));

	initMonsteBuilder();
	initMenu();
	initMap();
	//��ʼ������ߴ磨���ǵ�ͼ�ߴ磩
	world_rect.origin = Vec2::ZERO;
	world_rect.size = ZY_Size(tmap->getMapPixWidth(), tmap->getMapPixHeight());
	zyvar::worldSize = world_rect.size;

	//��ʼ��AABB��ײ��
	CollisionBody::extendTrees(world_rect.size);
	CollisionBody::extendTrees(world_rect.size);

	//��ʼ��������
	PropsFactor::init();
	//�������
	initPlayer();
}

void GameScene::handleInput(UINT32 KeyChar, int ActionType)
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

void GameScene::handleInput(int x, int y, int ActionType)
{
	if (menu)
	{
		if (ActionType == MOUSE_MOVE)
		{
			menu->MenuMouseMove(x, y);
		}
		else if (ActionType == MOUSE_LCLICK)
		{
			menu->MenuMouseClick(x, y);
			int index = menu->GetMenuIndex();
			allMenuDeal(index);
		}
	}
}

void GameScene::updateCamera()
{
	Vec2 pos = _camera->getTransPosition();
	Vec2 ppos = player->getTransPosition();
	_camera->setPosX(ppos.x);
	if (!world_rect.contain(_camera->getTransRect()))
	{
		_camera->setPosX(pos.x);
	}
	_camera->setPosY(ppos.y);
	if (!world_rect.contain(_camera->getTransRect()))
	{
		_camera->setPosY(pos.y);
	}
}

void GameScene::updateSelf(float dt)
{
	if (player->isDead())
	{
		gameMode = GAME_OVER;
		menu = deadMenu;
	}
	Scene::updateSelf(dt);
	CollisionBody::AdjustTree(2);
	auto mList = builder.getMonsters(dt);
	unsigned int length = mList.size();
	for (size_t i = 0; i < length; i++)
	{
		mList[i]->addCollisionBody(0, false);
		this->addChild(mList[i]);
	}
}

void GameScene::drawSelf(HDC hdc)
{
	Scene::drawSelf(hdc);
	if (gameMode == GAME_OVER)
	{
		RectF rect;
		rect.Width = wndWidth;
		rect.Height = wndHeight;
		rect.X = 0;
		rect.Y = 0;
		T_Graph::PaintText(hdc, rect, L"��Ϸ����", 50,L"����",Color::Red);
	}
	drawHitNumber(hdc);
	if (menu)
		menu->DrawMenu(hdc);
}

void GameScene::initMenu()
{
	//��ʼ���˵�
	runMenu = new T_Menu();
	{
		//menu->SetMenuBkg(L"res/gridback.png");
		MENU_INFO info;
		info.align = 1;
		info.focusTextColor = Color::Red;
		info.fontName = L"����";
		info.height = 30;
		info.isBold = true;
		info.normalTextColor = Color::White;
		info.width = 100;
		info.space = 10;
		runMenu->SetMenuInfo(info);
		runMenu->SetBtnBmp(L"res/menu/pause.png", 94, 85);
		runMenu->SetMoveSound(&sound::menu_over);
		runMenu->SetClickSound(&sound::menu_click);
		MENUITEM item;
		item.ItemName = L"";
		item.pos.x = wndWidth - 120;
		item.pos.y = 0;
		runMenu->AddMenuItem(item);
		menu = runMenu;
		//this->addChild(menu);
	}
	pauseMenu = new T_Menu();
	{
		MENU_INFO info;
		info.align = 1;
		info.focusTextColor = Color::Red;
		info.fontName = L"����";
		info.height = 80;
		info.isBold = true;
		info.normalTextColor = Color::White;
		info.width = 200;
		info.space = 10;
		pauseMenu->SetMenuInfo(info);
		pauseMenu->SetMenuInfo(info);
		pauseMenu->SetBtnBmp(L"res/menu/main.png", 180, 64);
		pauseMenu->SetMoveSound(&sound::menu_over);
		pauseMenu->SetClickSound(&sound::menu_click);
		MENUITEM item;
		item.ItemName = L"������Ϸ";
		item.pos.x = 0.5f * (wndWidth - info.width);
		item.pos.y = 30;
		pauseMenu->AddMenuItem(item);

		item.ItemName = L"�˳���Ϸ";
		item.pos.x = 0.5f * (wndWidth - info.width);
		item.pos.y = 130;
		pauseMenu->AddMenuItem(item);
	}
	deadMenu = new T_Menu();
	{
		MENU_INFO info;
		info.align = 1;
		info.focusTextColor = Color::Red;
		info.fontName = L"����";
		info.height = 80;
		info.isBold = true;
		info.normalTextColor = Color::White;
		info.width = 200;
		info.space = 10;
		deadMenu->SetMenuInfo(info);
		deadMenu->SetMenuInfo(info);
		deadMenu->SetBtnBmp(L"res/menu/main.png", 180, 64);
		deadMenu->SetMoveSound(&sound::menu_over);
		deadMenu->SetClickSound(&sound::menu_click);
		MENUITEM item;
		item.ItemName = L"����";
		item.pos.x = 0.5f * (wndWidth - info.width);
		item.pos.y = wndHeight*0.6;
		deadMenu->AddMenuItem(item);
	}
}

void GameScene::releaseMenu()
{
	delete runMenu;
	delete pauseMenu;
}

void GameScene::allMenuDeal(int index)
{
	if (menu == NULL)
	{
		return;
	}
	//menu->SetMenuIsItemFocused(false);
	switch (gameMode)
	{
	case GAME_RUN:
	{
		runMenuDeal(index);
	}
	break;
	case GAME_PAUSE:
	{
		pauseMenuDeal(index);
	}
	break;
	case GAME_OVER:
	{
		deadMenuDeal(index);
	}
	default:
		break;
	}
}

void GameScene::pauseMenuDeal(int index)
{
	switch (index)
	{
	case 0://������Ϸ
	{
		menu = runMenu;
		gameMode = GAME_RUN;
		this->pauseChildren(false);
	}
	break;
	case 1://�˳���Ϸ
	{
		menu = nullptr;
		Scene* scene = new MainMenuSceen();
		scene->init();
		zyvar::pEngine->changeScene(scene);
	}
	default:
		break;
	}
}

void GameScene::runMenuDeal(int index)
{
	switch (index)
	{
	case 0://��ͣ��Ϸ
	{
		menu = pauseMenu;
		gameMode = GAME_PAUSE;
		this->pauseChildren(true);
	}
	break;
	default:
		break;
	}
	
}

void GameScene::deadMenuDeal(int i)
{
	switch (i)
	{
	case 0://�˳�
	{
		Scene* scene = new MainMenuSceen();
		scene->init();
		zyvar::pEngine->changeScene(scene);
	}
	break;
	default:
		break;
	}
}

void GameScene::initPlayer()
{
	//������Ҷ���
	ALine_Animation* redani = new ALine_Animation(&MonsterGraphs::player, 4, 4, 10);
	player = new PlayerSprite(redani);
	/**��ǹWeaponsFactor
	* ����RevolverFactor
	* ��ǹRifleFactor
	* ����ShotgunFactor
	* ɳBossFactor
	* */

	WeaponsFactor f;
	Weapons* weap = f.getWeapons();
	/**
	ThourthBulletFactor
	��ը��BoomBulletFactor
	ReboundBulletFactor
	TrackBulletFactor
	*/
	weap->setBulletFactor(new BulletFactor());
	player->setWeapons(weap);
	player->setTag(LAYER_PLY);
	player->setPosition(Vec2(100, 300));
	player->setSpeedLen(200);
	player->setBloodReturnTime(5.f);

	//������ײ��
	player->addCollisionBody(1);
	//�����ҵ���������
	this->addChild(player);
	//��ʼ��Ѫ��
	player->initBlood(L"res/other/heart.png");
	player->setMaxHealth(20);
	player->setFullHealth();
	BlockSprite::player = player;
	player->setSpeedUpRate(3.f);
	//��ʼ�����ټ���
	FastMovE* move = new FastMovE();
	move->setKey('E');
	move->setUser(player);
	move->setCool(7.f);
	move->setSpeedUpTime(3);
	player->setPower1(move);
	//��ʼ��̩ɽѹ��
	BodySlaM* move2 = new BodySlaM();
	move2->setKey('Q');
	move2->setUser(player);
	move2->setCool(5.f);
	move2->setMove(0.3, 300);
	player->setPower2(move2);
}

void GameScene::initMonsteBuilder()
{
	//��ʼ������������
	int rate=10, onceSum=5, allSum=30, bossSum=30;
	float strongRate = 1.f;
	switch (mode)
	{
	case NORMAL:
		rate = 6;
		onceSum = 4;
		allSum = 30;
		bossSum = 30;
		break;
	case EXPERT:
		rate = 12;
		onceSum = 5;
		allSum = 35;
		bossSum = 20;
		strongRate = 1.5;
		break;
	case MASTER:
		rate = 20;
		onceSum = 5;
		allSum = 40;
		bossSum = 15;
		strongRate = 2.f;
		break;
	default:
		break;
	}
	builder.setRate(rate);
	builder.setMaxOnceTime(onceSum);
	builder.setMaxAllSum(allSum);
	builder.setBossSum(bossSum);
	builder.setStrongRate(strongRate);
	builder.addFectory(new CdragonFactory());
	builder.addFectory(new BatFactory());
	builder.addFectory(new BirdFactory());
	builder.addFectory(new CdragonFactory());
	builder.addFectory(new ChickenFactory());
	builder.addFectory(new CowFactory());
	builder.addFectory(new DeathFactory());
	builder.addFectory(new DragonFactory());
	builder.addFectory(new Dragon2Factory());
	builder.addFectory(new FireFactory());
	builder.addFectory(new GostFactory());
	builder.addFectory(new LizardFactory());
	builder.addFectory(new MummyFactory());
	builder.addFectory(new SkeletonFactory());
	builder.addFectory(new SnakeFactory());
	builder.addFectory(new StoneFactory());
	builder.addFectory(new VampireFactory());
	builder.addFectory(new WolfFactory());
	builder.addFectory(new ZombiesFactory());
	builder.setCamera(_camera);
	builder.setPause(false);
}

void GameScene::initMap()
{
	switch (mode)
	{
	case NORMAL:
	{
		//������ͼ�����õ�ͼ���洰�ڴ�С
		tmap = new TiledMap("res/map/viliage_ground.json", wndWidth * 3, wndHeight * 3);
		this->addChild(tmap);
		zyvar::obstacles = 2;
		coverMap = new TiledMap("res/map/viliage_surface.json", wndWidth * 3, wndHeight * 3);
		this->addSurfaceNode(coverMap);
	}
		break;
	case EXPERT:
	{
		//������ͼ�����õ�ͼ���洰�ڴ�С
		tmap = new TiledMap("res/map/snow_ground.json", wndWidth * 3, wndHeight * 3);
		this->addChild(tmap);
		zyvar::obstacles = 1;
		coverMap = new TiledMap("res/map/snow_surface.json", wndWidth * 3, wndHeight * 3);
		this->addSurfaceNode(coverMap);
	}
		break;
	case MASTER:
	{
		//������ͼ�����õ�ͼ���洰�ڴ�С
		tmap = new TiledMap("res/map/swamp_ground.json", wndWidth * 3, wndHeight * 3);
		this->addChild(tmap);
		zyvar::obstacles = 2;
		coverMap = new TiledMap("res/map/swamp_surface.json", wndWidth * 3, wndHeight * 3);
		this->addSurfaceNode(coverMap);
	}
		break;
	default:
	{
		//������ͼ�����õ�ͼ���洰�ڴ�С
		tmap = new TiledMap("res/map/viliage_ground.json", wndWidth * 3, wndHeight * 3);
		this->addChild(tmap);
		zyvar::obstacles = 2;
		coverMap = new TiledMap("res/map/viliage_surface.json", wndWidth * 3, wndHeight * 3);
		this->addSurfaceNode(coverMap);
	}
		break;
	}
	//��ȫ�ֱ����ͼָ��
	zyvar::tMap = tmap;
}

void GameScene::drawHitNumber(HDC hdc)
{
	RectF rect;
	rect.Width = 200;
	rect.Height = 30;
	rect.X = wndWidth-230;
	rect.Y = wndHeight-30;
	int sum = BlockSprite::getDeadSum();
	T_Graph::PaintText(hdc, rect, L"��ɱ������", 20, L"����");
	wchar_t str[18]{};

	rect.X += 90;
	swprintf_s(str, TEXT("%d"), sum);
	T_Graph::PaintText(hdc, rect, str, 20, L"����",Color::Red);
	//������ȴ
	rect.X = 60;
	rect.Y = wndHeight - 30;
	rect.Width = 100;
	swprintf_s(str, TEXT("%.1f"), player->getSkillCool(1));
	T_Graph::PaintText(hdc, rect, str, 12, L"����", Color::White);

	rect.X = 10;
	rect.Y = wndHeight - 30;
	T_Graph::PaintText(hdc, rect, L"̩ɽѹ����", 12, L"����", Color::White);


	rect.X = 150;
	rect.Y = wndHeight - 30;
	swprintf_s(str, TEXT("%.1f"), player->getSkillCool(0));
	T_Graph::PaintText(hdc, rect, str, 12, L"����", Color::White);

	rect.X = 120;
	T_Graph::PaintText(hdc, rect, L"���٣�", 12, L"����", Color::White);

}
