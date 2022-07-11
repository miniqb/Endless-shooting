#include "Props.h"
#include "PlayerSprite.h"

Props::Props():
    Sprite()
{
    _tag = LAYER_BONUS;
}

Props::~Props()
{
    if (_weapon)
        delete _weapon;
    if (_bullet)
        delete _bullet;
}

void Props::updateSelf(float dt)
{
    if (_timer < _exitTime&&_alive)
    {
        _timer += dt;
        if (_timer > _lastTime)
        {
            if (_flashTimer <= _flashTime)
            {
                _flashTimer += dt;
            }
            if (_flashTimer >= _flashTime)
            {
                _flashTimer = 0;
                _visible = !_visible;
            }
        }
    }
    else
    {
        this->setAlive(false);
    }
}

bool Props::collisionFuntion(Node* node)
{
    if (node->getTag() == LAYER_PLY)
    {
        PlayerSprite* player = ((PlayerSprite*)node);
        if (_type == WEAPON)
        {
            if (_weapon)
            {
                player->changeWeapons(_weapon->getWeapons());
                delete _weapon;
                _weapon = nullptr;
            }
        }
        if (_type == BULLET)
        {
            if (_bullet)
            {
                player->changeBullet(_bullet->clon());
                delete _bullet;
                _bullet = nullptr;
            }
        }
        this->setAlive(false);
        return false;
    }
    return true;
}

Props* BoomPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::boom);
    prop->init(ain);
    prop->setBulletType(new BoomBulletFactor());
    return prop;
}

Props* NotePropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::note);
    prop->init(ain);
    prop->setBulletType(new TrackBulletFactor());
    return prop;
}

Props* ReboundPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::rebound);
    prop->init(ain);
    prop->setBulletType(new ReboundBulletFactor());
    return prop;
}

Props* ThroughPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::through);
    prop->init(ain);
    prop->setBulletType(new ThourthBulletFactor());
    return prop;
}

Props* RevolverPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::revolver);
    prop->init(ain);
    prop->setWeaponType(new RevolverFactor());
    return prop;
}

Props* RiflePropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::rifle);
    prop->init(ain);
    prop->setWeaponType(new RifleFactor());
    return prop;
}

Props* ShotgunPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::shotgun);
    prop->init(ain);
    prop->setWeaponType(new ShotgunFactor());
    return prop;
}

Props* BossPropsFactor::getProps()
{
    Props* prop = new Props();
    Static_Animation* ain = new Static_Animation(&PropsGraphs::boss);
    prop->init(ain);
    prop->setWeaponType(new BossFactor());
    return prop;
}

PropsFactor* PropsFactor::weaponsProp[4];
PropsFactor* PropsFactor::bulletProp[4];
void PropsFactor::init()
{
    weaponsProp[0] = new BossPropsFactor();
    weaponsProp[1] = new RiflePropsFactor();
    weaponsProp[2] = new ShotgunPropsFactor();
    weaponsProp[3] = new RevolverPropsFactor();

    bulletProp[0] = new BoomPropsFactor();
    bulletProp[1] = new ReboundPropsFactor();
    bulletProp[2] = new ThroughPropsFactor();
    bulletProp[3] = new NotePropsFactor();
}

void PropsFactor::release()
{
    for (size_t i = 0; i < 4; i++)
    {
        delete weaponsProp[i];
        delete bulletProp[i];
    }
}
