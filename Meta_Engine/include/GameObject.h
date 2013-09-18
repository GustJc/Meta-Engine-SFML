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
        void movePosition(int x, int y = 0);
    protected:
        sf::Vector2i mPosition;
    private:
};
