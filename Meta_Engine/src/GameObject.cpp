#include "GameObject.h"
#include "Defines.h"

#include "MetaEngine.h"
#include "Map.h"
GameObject::GameObject()
{
    //ctor
    mPosition.x = mPosition.y = 0;
}

GameObject::~GameObject()
{
    //dtor

    Tile* t = Map::MapControl.getTile(mPosition.x, mPosition.y);
    if (t)
    {
        //Garante que não é deixado a referencia do objeto no tile ao deixar de existir
        for(unsigned int i = 0; i < t->obj.size(); ++i)
        {
            if(t->obj[i] == this)
            {
                t->obj.erase(t->obj.begin()+ i);
            }
        }
    }
}


sf::Vector2i GameObject::getPosition()
{
    return mPosition;
}


int GameObject::getPositionX()
{
    return mPosition.x;
}

int GameObject::getPositionY()
{
    return mPosition.y;
}

void GameObject::setPosition(int x, int y)
{


    Tile* tileOld = Map::MapControl.getTile(mPosition.x, mPosition.y);
    //Remove da lista de tiles
    for(unsigned int i = 0; i < tileOld->obj.size(); ++i)
    {
        if(tileOld->obj[i] == this)
        {
            tileOld->obj.erase(tileOld->obj.begin()+i);
        }
    }
    //Move e adciona a lista de tiles
    mPosition.x = x;
    mPosition.y = y;
    Map::MapControl.getTile(mPosition.x, mPosition.y)->obj.push_back(this);
}

void GameObject::setPosition(sf::Vector2i pos)
{
    setPosition(pos.x, pos.y);
}

void GameObject::movePositionIgnore(int x, int y)
{
    Tile* tileOld = Map::MapControl.getTile(mPosition.x, mPosition.y);
    //Remove da lista de tiles
    for(unsigned int i = 0; i < tileOld->obj.size(); ++i)
    {
        if(tileOld->obj[i] == this)
        {
            tileOld->obj.erase(tileOld->obj.begin()+i);
        }
    }
    //Move e adciona a lista de tiles

    mPosition.x += x;
    mPosition.y += y;
    Map::MapControl.getTile(mPosition.x, mPosition.y)->obj.push_back(this);
}


void GameObject::setTexture(sf::Texture& targetTexture)
{
    mSprite.setTexture(targetTexture);

    assert(mSprite.getTexture() != nullptr);
}

void GameObject::changeSprite(int x, int y)
{
    assert(mSprite.getTexture() != nullptr);
    if(y < 0)
    {
        int width = mSprite.getTexture()->getSize().x;
        y =  x % width;
        x =  x / width;
    }

    mSprite.setTextureRect(sf::IntRect(x*TILE_SIZE, (int)(y*TILE_SIZE*mSprite.getTexture()->getSize().x) ,
                           TILE_SIZE, TILE_SIZE) );
}

void GameObject::draw()
{
    //test, mostra caso isFog false
    if(MetaEngine::EngineControl.isMapFog() &&
        Map::MapControl.has_seens(mPosition.x, mPosition.y) == false) return;

    if(mSprite.getTexture() == nullptr)
    {
        sf::Color c;
        if(type == TYPE_PLAYER){
            c.b = 100;
            c.g = 255;
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
    else
    {
        //TODO: Move e setPosition mexe sprite.
        mSprite.setPosition(mPosition.x*TILE_SIZE, mPosition.y*TILE_SIZE);
        MetaEngine::EngineControl.getWindowReference().draw(mSprite);
    }
}

void GameObject::addToObjectList()
{
    for(unsigned int i = 0; i < ObjectList.size();i++)
    {
        if (ObjectList[i] == this)
        {
            return; //Já existe.
        }
    }
    ObjectList.push_back(this);
}

void GameObject::removeFromObjectList()
{
    for(unsigned int i = 0; i < ObjectList.size();i++)
    {
        if (ObjectList[i] == this)
        {
            ObjectList.erase(ObjectList.begin()+ i);
            delete this;
            return;
        }
    }
}

void GameObject::removeFromTileReference()
{
    Tile* tileOld = Map::MapControl.getTile(mPosition.x, mPosition.y);
    if (!tileOld) return;

    for(unsigned int i = 0; i < tileOld->obj.size(); ++i)
    {
        if(tileOld->obj[i] == this)
        {
            tileOld->obj.erase(tileOld->obj.begin()+i);
        }
    }
}
