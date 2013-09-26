#include "GameObject.h"
#include "Defines.h"
GameObject::GameObject()
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
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
    mPosition.x = x;
    mPosition.y = y;
}

void GameObject::setPosition(sf::Vector2i pos)
{
    mPosition = pos;
}

void GameObject::movePositionIgnore(int x, int y)
{
    mPosition.x += x;
    mPosition.y += y;
}
