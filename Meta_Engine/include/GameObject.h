#pragma once

#include <SFML/System/Vector2.hpp>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        sf::Vector2i getPosition();
        void setPosition(int x, int y);
        void setPosition(sf::Vector2i pos);
        void movePositionIgnore(int x, int y = 0);

        virtual void update(unsigned int dt, unsigned int delay){};
        virtual void draw(){};

        //lua functions
        int getPositionX();
        int getPositionY();
    protected:
        sf::Vector2i mPosition;
    private:
};
