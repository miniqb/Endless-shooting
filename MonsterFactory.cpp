#include "MonsterFactory.h"

BlockSprite* BatFactory::getMonster()
{
    MonsterInfo info;
    info._tag = LAYER_NPC;
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 1;
    //����ֵ
    info._health = 50;
    //�ٶ�
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.5;
    //�������� ��0~1��
    info._againstFendRate = 0.1f;
    //�ж�ģʽ����������ֱ��
    ActionMode* act = new CurveMove();//����
    //ActionMode* act = new LinearMove();//��ֱ
    info.action = act;

    /****************����һ��̩ɽѹ��*****************/
    info.powers[0] = nullptr;
    info.powers[1] = nullptr;
    //������������
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 1;
    //����ֵ
    info._health = 90;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 10;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 1.f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 300;
    //λ��ʱ��
    bfo._slaTime = 1;
    //����ʱ��
    bfo._xuli = 1;
    //��ȴʱ��
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    FireSkill* fireSkill = new FireSkill();
    //���÷�����
    fireSkill->setCool(3.f);
    //�����ӵ��ٶ�
    fireSkill->setFireSpeed(100);
    info.powers[1] = fireSkill;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 2;
    //����ֵ
    info._health = 110;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 50;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 1.f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 300;
    //λ��ʱ��
    bfo._slaTime = 1;
    //����ʱ��
    bfo._xuli = 1;
    //��ȴʱ��
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 1;
    //����ֵ
    info._health = 30;
    //�ٶ�
    info._speedLen = 100.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.5f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;
    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 5;
    //����ֵ
    info._health = 60;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 40;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.6;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.8f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 200;
    //λ��ʱ��
    bfo._slaTime = 1;
    //����ʱ��
    bfo._xuli = 1;
    //��ȴʱ��
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 3;
    //����ֵ
    info._health = 55;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.6f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 5;
    //����ֵ
    info._health = 70;
    //�ٶ�
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 15;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.8f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 200;
    //λ��ʱ��
    bfo._slaTime = 1.3;
    //����ʱ��
    bfo._xuli = 1;
    //��ȴʱ��
    bfo._cooling = 7;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    FireSkill* fireSkill = new FireSkill();
    //���÷�����
    fireSkill->setCool(2.5f);
    //�����ӵ��ٶ�
    fireSkill->setFireSpeed(160);
    info.powers[1] = fireSkill;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 3;
    //����ֵ
    info._health = 50;
    //�ٶ�
    info._speedLen = 180.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.4f;
    //�ж�ģʽ����������ֱ��
    ActionMode* act = new CurveMove();//����
    //ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 5;
    //����ֵ
    info._health = 25;
    //�ٶ�
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.4f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    FireSkill* fireSkill = new FireSkill();
    //���÷�����
    fireSkill->setCool(2.f);
    //�����ӵ��ٶ�
    fireSkill->setFireSpeed(140);
    info.powers[1] = fireSkill;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 3;
    //����ֵ
    info._health = 40;
    //�ٶ�
    info._speedLen = 140.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.3f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 10;
    //����ֵ
    info._health = 70;
    //�ٶ�
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 15;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.3;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.6f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 250;
    //λ��ʱ��
    bfo._slaTime = 1;
    //����ʱ��
    bfo._xuli = 1;
    //��ȴʱ��
    bfo._cooling = 7;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 10;
    //����ֵ
    info._health = 65;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 15;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.6f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 10;
    //����ֵ
    info._health = 80;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 15;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.6f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 270;
    //λ��ʱ��
    bfo._slaTime = 1.2;
    //����ʱ��
    bfo._xuli = 1.1;
    //��ȴʱ��
    bfo._cooling = 12;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 5;
    //����ֵ
    info._health = 40;
    //�ٶ�
    info._speedLen = 120.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 5;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.1;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.3f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;
    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 15;
    //����ֵ
    info._health = 115;
    //�ٶ�
    info._speedLen = 80.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 30;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.5;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 1.f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 300;
    //λ��ʱ��
    bfo._slaTime = 1;
    //����ʱ��
    bfo._xuli = 2;
    //��ȴʱ��
    bfo._cooling = 10;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = true;
    //��ײ�˺�
    info._collPower = 10;
    //����ֵ
    info._health = 70;
    //�ٶ�
    info._speedLen = 150.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 10;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.5f;
    //�ж�ģʽ����������ֱ��
    ActionMode* act = new CurveMove();//����
    //ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 10;
    //����ֵ
    info._health = 80;
    //�ٶ�
    info._speedLen = 130.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 15;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.6f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    info.powers[0] = nullptr;
    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
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
    //�Ƿ�ɷ���
    info._canFly = false;
    //��ײ�˺�
    info._collPower = 15;
    //����ֵ
    info._health = 85;
    //�ٶ�
    info._speedLen = 140.f * fabsf(_rander.normal(1, 0.2));
    //��ײ���ˣ�����/�룩
    info._fendOffSed = 20;
    //����ʱ�䣨�룩
    info._fendOffTime = 0.2;
    //�������� x100%
    info._speedUpRate = 2.3;
    //�������� ��0~1��
    info._againstFendRate = 0.75f;
    //�ж�ģʽ����������ֱ��
    //ActionMode* act = new CurveMove();//����
    ActionMode* act = new LinearMove();//��ֱ
    info.action = act;
    /************����һ��̩ɽѹ��*******************/
    BodySlaMInfo bfo;
    //λ�ƾ���
    bfo._allMoveLen = 400;
    //λ��ʱ��
    bfo._slaTime = 1.2;
    //����ʱ��
    bfo._xuli = 1.5;
    //��ȴʱ��
    bfo._cooling = 80;
    BodySlaM* bodySlaM = new BodySlaM();
    bodySlaM->initSkill(bfo);
    info.powers[0] = bodySlaM;

    /**************�������������ӵ�******************************/
    info.powers[1] = nullptr;
    /********************������������****************************/
    FastMovE* faseMove = new FastMovE();
    //���ó���ʱ�䡢��ȴʱ��
    faseMove->initSkill(3, 6);
    info.powers[2] = faseMove;

    BlockSprite* sp = new BlockSprite();
    ZY_Animation* ain = new ALine_Animation(&MonsterGraphs::wolf, 4, 4, 10);
    sp->init(ain);
    sp->initMonster(info);
    return sp;
}