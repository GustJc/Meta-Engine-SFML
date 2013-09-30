#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum ENUM_TYPE_OBJ{
        TYPE_ENEMY,
        TYPE_PLAYER,
        TYPE_ITEM,
        TYPE_TRAP,
        TYPE_DESTROYABRE
};

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        ENUM_TYPE_OBJ type;

        sf::Vector2i getPosition();
        void setPosition(int x, int y);
        void setPosition(sf::Vector2i pos);
        void movePositionIgnore(int x, int y = 0);

        virtual void update(unsigned int dt, unsigned int delay){};
        virtual void draw();

        void setTexture(sf::Texture& targetTexture);
        void changeSprite(int x, int y = -1);

        void addToObjectList();
        void removeFromObjectList();
        void removeFromTileReference();

        //lua functions
        int getPositionX();
        int getPositionY();
    protected:
        sf::Vector2i mPosition;
        sf::Sprite   mSprite;
    private:
};
