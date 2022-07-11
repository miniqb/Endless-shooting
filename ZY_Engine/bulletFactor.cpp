#include "bulletFactor.h"

//��ը��
Bullet* BoomBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::boom);
    info._ain = ani;//�ӵ�����
    info._basisPower = 4;//�ӵ������˺�
    info._penetration = 0;//���͸����
    info._surviveTime = 3.f;//����ʱ��
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new BoomBullet();
    bullet->initBullet(info);
    return bullet;
}

//����
Bullet* TrackBulletFactor::getBullet()
{
    bulletInfo info;
    ALine_Animation* ani = new ALine_Animation(&BulletGraphs::note, 17, 1,20);
    ani->setIndexX(rand() % 17);
    info._ain = ani;//�ӵ�����������
    info._basisPower = 6;//�����˺�
    info._penetration = 0;//���͸
    info._surviveTime = 4.f;//����ʱ��
    info._tag = LAYER_PLY_BOMB;
    info._speedRate = 0.5f;
    TrackBullet* bullet = new TrackBullet();
    bullet->setAim(nullptr);
    bullet->setMaxTurn(M_PI * 3.f);
    bullet->setDetecTion(200.f);
    bullet->initBullet(info);
    return bullet;
}

//�ᴩ��
Bullet* ThourthBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::through);
    info._ain = ani;
    info._basisPower = 2;
    info._penetration = 9999;
    info._surviveTime = 1.f;
    info._speedRate = 1.5f;
    info._tag = LAYER_PLY_BOMB;
    ThourthBullet* bullet = new ThourthBullet();
    bullet->initBullet(info);
    bullet->setCooling(0.15f);
    return bullet;
}

//���䵯
Bullet* ReboundBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::rebound);
    info._ain = ani;//�ӵ�����
    info._basisPower = 4;//�ӵ������˺�
    info._penetration = 6;//���͸����
    info._surviveTime = 3.f;//����ʱ��
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1.4f;
    ReboundBullet* bullet = new ReboundBullet();
    bullet->initBullet(info);//��ʼ���ӵ�
    return bullet;
}


//��ͨ��
Bullet* BulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::bullet);
    info._ain = ani;//�ӵ�����
    info._basisPower = 4;//�ӵ������˺�
    info._penetration = 0;//���͸����
    info._surviveTime = 3.f;//����ʱ��
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new Bullet();
    bullet->initBullet(info);//��ʼ���ӵ�

    return bullet;
}

Bullet* NpcBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::npc);
    info._ain = ani;//�ӵ�����
    info._basisPower = 2;//�ӵ������˺�
    info._penetration = 0;//���͸����
    info._surviveTime = 2.f;//����ʱ��
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new Bullet();
    bullet->initBullet(info);//��ʼ���ӵ�

    return bullet;
}
