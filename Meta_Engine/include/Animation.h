#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/System/Vector2.hpp>

#include <SFML/System/Clock.hpp>

namespace sf
{
    class Sprite;
}
class Animation
{
    public:
        Animation();
        virtual ~Animation();
        void setSprite(sf::Sprite* sprite);

        sf::Vector2f mPosition;
        sf::Vector2f mPositionOffset;

        sf::Vector2f getPosition();

        void jumpAnimation();

        bool isJumping();

        void update(float dt);

    protected:
        int frame;
        int max_frames;
        int index_x;
        int index_y;
        int width;
        int height;

        bool jumping;
        sf::Clock jumpClock;
        float degree = 0;
    private:
};

#endif // ANIMATION_H
