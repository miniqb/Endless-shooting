#include "MonsterFactory.h"

BlockSprite* BatFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 1;
    //生命值
    info._health = 50;
    //速度
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.5;
    //抗击退力 （0~1）
    info._againstFendRate = 0.1f;
    //行动模式（盘旋、径直）
    ActionMode* act = new CurveMove();//盘旋
    //ActionMode* act = new LinearMove();//径直
    info.action = act;

    /****************能力一：泰山压顶*****************/
    info.powers[0] = nullptr;
    info.powers[1] = nullptr;
    //能力三：加速
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(2, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::bat, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* BirdFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 1;
    //生命值
    info._health = 90;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 10;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 1.f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 300;
    //位移时间
    bfo._slaTime = 1;
    //蓄力时间
    bfo._xuli = 1;
    //冷却时间
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    FireSkill* fireSkill = new FireSkill();
    //设置发射间隔
    fireSkill->setCool(3.f);
    //设置子弹速度
    fireSkill->setFireSpeed(100);
    info.powers[1] = fireSkill;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(2, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::bird, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* CdragonFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 2;
    //生命值
    info._health = 110;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 50;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 1.f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 300;
    //位移时间
    bfo._slaTime = 1;
    //蓄力时间
    bfo._xuli = 1;
    //冷却时间
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::cdragon, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* ChickenFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 1;
    //生命值
    info._health = 30;
    //速度
    info._speedLen = 100.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.5f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;
    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::chicken, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* CowFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 5;
    //生命值
    info._health = 60;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 40;
    //击退时间（秒）
    info._fendOffTime = 0.6;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.8f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 200;
    //位移时间
    bfo._slaTime = 1;
    //蓄力时间
    bfo._xuli = 1;
    //冷却时间
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(1.5, 8);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::cow, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* DeathFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 3;
    //生命值
    info._health = 55;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.6f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::death, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* DragonFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 5;
    //生命值
    info._health = 70;
    //速度
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 15;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.8f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 200;
    //位移时间
    bfo._slaTime = 1.3;
    //蓄力时间
    bfo._xuli = 1;
    //冷却时间
    bfo._cooling = 7;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    FireSkill* fireSkill = new FireSkill();
    //设置发射间隔
    fireSkill->setCool(2.5f);
    //设置子弹速度
    fireSkill->setFireSpeed(160);
    info.powers[1] = fireSkill;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::dragon, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* Dragon2Factory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 3;
    //生命值
    info._health = 50;
    //速度
    info._speedLen = 180.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.4f;
    //行动模式（盘旋、径直）
    ActionMode* act = new CurveMove();//盘旋
    //ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::dragon2, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* FireFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 5;
    //生命值
    info._health = 25;
    //速度
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.4f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    FireSkill* fireSkill = new FireSkill();
    //设置发射间隔
    fireSkill->setCool(2.f);
    //设置子弹速度
    fireSkill->setFireSpeed(140);
    info.powers[1] = fireSkill;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::fire, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* GostFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 3;
    //生命值
    info._health = 40;
    //速度
    info._speedLen = 140.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.3f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::gost, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* LizardFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 10;
    //生命值
    info._health = 70;
    //速度
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 15;
    //击退时间（秒）
    info._fendOffTime = 0.3;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.6f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 250;
    //位移时间
    bfo._slaTime = 1;
    //蓄力时间
    bfo._xuli = 1;
    //冷却时间
    bfo._cooling = 7;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::lizard, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* MummyFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 10;
    //生命值
    info._health = 65;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 15;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.6f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::mummy, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* SkeletonFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 10;
    //生命值
    info._health = 80;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 15;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.6f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 270;
    //位移时间
    bfo._slaTime = 1.2;
    //蓄力时间
    bfo._xuli = 1.1;
    //冷却时间
    bfo._cooling = 12;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 8);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::skeleton, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* SnakeFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 5;
    //生命值
    info._health = 40;
    //速度
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 5;
    //击退时间（秒）
    info._fendOffTime = 0.1;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.3f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;
    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(1, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::snake, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* StoneFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 15;
    //生命值
    info._health = 115;
    //速度
    info._speedLen = 80.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 30;
    //击退时间（秒）
    info._fendOffTime = 0.5;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 1.f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 300;
    //位移时间
    bfo._slaTime = 1;
    //蓄力时间
    bfo._xuli = 2;
    //冷却时间
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::stone, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* VampireFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = true;
    //碰撞伤害
    info._collPower = 10;
    //生命值
    info._health = 70;
    //速度
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 10;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.5f;
    //行动模式（盘旋、径直）
    ActionMode* act = new CurveMove();//盘旋
    //ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 8);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::vampire, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* ZombiesFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 10;
    //生命值
    info._health = 80;
    //速度
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 15;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.6f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    info.powers[0] = nullptr;
    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    info.powers[2] = nullptr;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::zombies, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}

BlockSprite* WolfFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //是否可飞行
    info._canFly = false;
    //碰撞伤害
    info._collPower = 15;
    //生命值
    info._health = 85;
    //速度
    info._speedLen = 140.f * fabsf(_rander.normal(1, 0.2));
    //碰撞击退（像素/秒）
    info._fendOffSed = 20;
    //击退时间（秒）
    info._fendOffTime = 0.2;
    //加速速率 x100%
    info._speedUpRate = 2.3;
    //抗击退力 （0~1）
    info._againstFendRate = 0.75f;
    //行动模式（盘旋、径直）
    //ActionMode* act = new CurveMove();//盘旋
    ActionMode* act = new LinearMove();//径直
    info.action = act;
    /************能力一：泰山压顶*******************/
    BodySlaMInfo bfo;
    //位移距离
    bfo._allMoveLen = 400;
    //位移时间
    bfo._slaTime = 1.2;
    //蓄力时间
    bfo._xuli = 1.5;
    //冷却时间
    bfo._cooling = 80;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************能力二：发射子弹******************************/
    info.powers[1] = nullptr;
    /********************能力三：加速****************************/
    FastMovE* faseMove = new FastMovE();
    //设置持续时间、冷却时间
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::wolf, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}