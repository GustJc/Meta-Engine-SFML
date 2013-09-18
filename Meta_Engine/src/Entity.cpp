#include "Entity.h"

#include "MetaEngine.h"
#include "Defines.h"
Entity::Entity()
{
    //ctor
    type = ENT_ENEMY;
    mDelay = 0;
    mSpeed = 100;
    mAtk = 10;
    mDef = 5;
}
Entity::Entity(ENUM_ENT_TYPE tipo)
{
    type = tipo;
    mDelay = 0;
    mSpeed = 100;
    mAtk = 10;
    mDef = 5;
}

Entity::~Entity()
{
    //dtor
}


void Entity::draw()
{
    sf::Color c;
    if(type == ENT_PLAYER){
        c.b = 255;
        c.g = 20;
        c.r = 150;
    } else
    {
        c.b = 100;
        c.g = 50;
        c.r = 230;
    }

    int center = TILE_SIZE/4;
    MetaEngine::EngineControl.drawRectVertex(mPosition.x*TILE_SIZE +center, mPosition.y*TILE_SIZE +center,
                                             TILE_SIZE/2, TILE_SIZE/2, c);
}
