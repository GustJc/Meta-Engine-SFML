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
    removeFromTileReference();
}


sf::Vector2i GameObject::getPosition()
{
    return mPosition;
}

sf::Vector2f GameObject::getAnimationPosition()
{
    return (anim.mPosition);
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
    //Remove da lista de tiles
    removeFromTileReference();
    //Move e adciona a lista de tiles
    mPosition.x = x;
    mPosition.y = y;
    anim.mPosition.x = x;
    anim.mPosition.y = y;
    if(this->type == TYPE_ITEM)
    {
        Map::MapControl.getTile(mPosition.x, mPosition.y)->itens.push_back(this);
    } else
    {
        Map::MapControl.getTile(mPosition.x, mPosition.y)->obj = (this);
    }


}

void GameObject::setPosition(sf::Vector2i pos)
{
    setPosition(pos.x, pos.y);
}

void GameObject::movePositionIgnore(int x, int y)
{
    //Remove da lista de tiles
    removeFromTileReference();
    //Move e adciona a lista de tiles

    mPosition.x += x;
    mPosition.y += y;
    anim.mPosition.x += x;
    anim.mPosition.y += y;
    if(this->type == TYPE_ITEM)
    {
        Map::MapControl.getTile(mPosition.x, mPosition.y)->itens.push_back(this);
    } else
    {
        Map::MapControl.getTile(mPosition.x, mPosition.y)->obj = (this);
    }
}


void GameObject::setTexture(sf::Texture& targetTexture)
{
    mSprite.setTexture(targetTexture);

    assert(mSprite.getTexture() != nullptr);
}

void GameObject::changeSprite(int x, int y)
{
    if(y < 0)
    {
        assert(mSprite.getTexture() != nullptr);
        int textureSizeW = mSprite.getTexture()->getSize().x/TILE_SIZE;
        y =  x % textureSizeW;
        x =  x / textureSizeW;
    }


    mSprite.setTextureRect(sf::IntRect(x*TILE_SIZE, (int)(y*TILE_SIZE) ,
                           TILE_SIZE, TILE_SIZE) );
}

int  GameObject::getSpriteIdx()
{
    if(mSprite.getTexture() == nullptr) return 0;

    return mSprite.getTextureRect().left/TILE_SIZE;

}
int  GameObject::getSpriteIdy()
{
    if(mSprite.getTexture() == nullptr) return 0;

    return mSprite.getTextureRect().top/TILE_SIZE;
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
        mSprite.setPosition(anim.getPosition().x*TILE_SIZE, anim.getPosition().y*TILE_SIZE);
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

void GameObject::removeFromTileReference(int pX, int pY)
{
    if(pX == -1 && pY == -1)
    {
        pX = mPosition.x;
        pY = mPosition.y;
    }
    Tile* tileOld = Map::MapControl.getTile(pX, pY);
    if (!tileOld) return;

    if(tileOld->obj == this)
    {
        tileOld->obj = nullptr;
        return;
    }

    for(unsigned int i = 0; i < tileOld->itens.size(); ++i)
    {
        if(tileOld->itens[i] == this)
        {
            tileOld->itens.erase(tileOld->itens.begin()+i);
            return;
        }
    }
}
