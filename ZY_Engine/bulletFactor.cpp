#include "bulletFactor.h"

//爆炸弹
Bullet* BoomBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::boom);
    info._ain = ani;//子弹动画
    info._basisPower = 4;//子弹基础伤害
    info._penetration = 0;//最大穿透数量
    info._surviveTime = 3.f;//存在时间
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new BoomBullet();
    bullet->initBullet(info);
    return bullet;
}

//导弹
Bullet* TrackBulletFactor::getBullet()
{
    bulletInfo info;
    ALine_Animation* ani = new ALine_Animation(&BulletGraphs::note, 17, 1,20);
    ani->setIndexX(rand() % 17);
    info._ain = ani;//子弹动画：音符
    info._basisPower = 6;//基础伤害
    info._penetration = 0;//最大穿透
    info._surviveTime = 4.f;//存在时间
    info._tag = LAYER_PLY_BOMB;
    info._speedRate = 0.5f;
    TrackBullet* bullet = new TrackBullet();
    bullet->setAim(nullptr);
    bullet->setMaxTurn(M_PI * 3.f);
    bullet->setDetecTion(200.f);
    bullet->initBullet(info);
    return bullet;
}

//贯穿弹
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

//反射弹
Bullet* ReboundBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::rebound);
    info._ain = ani;//子弹动画
    info._basisPower = 4;//子弹基础伤害
    info._penetration = 6;//最大穿透数量
    info._surviveTime = 3.f;//存在时间
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1.4f;
    ReboundBullet* bullet = new ReboundBullet();
    bullet->initBullet(info);//初始化子弹
    return bullet;
}


//普通弹
Bullet* BulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::bullet);
    info._ain = ani;//子弹动画
    info._basisPower = 4;//子弹基础伤害
    info._penetration = 0;//最大穿透数量
    info._surviveTime = 3.f;//存在时间
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new Bullet();
    bullet->initBullet(info);//初始化子弹

    return bullet;
}

Bullet* NpcBulletFactor::getBullet()
{
    bulletInfo info;
    Static_Animation* ani = new Static_Animation(&BulletGraphs::npc);
    info._ain = ani;//子弹动画
    info._basisPower = 2;//子弹基础伤害
    info._penetration = 0;//最大穿透数量
    info._surviveTime = 2.f;//存在时间
    info._tag = LAYER_PLY_BOMB;//tag
    info._speedRate = 1;
    Bullet* bullet = new Bullet();
    bullet->initBullet(info);//初始化子弹

    return bullet;
}
