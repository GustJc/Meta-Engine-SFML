#include "Animation.h"
#include "MetaEngine.h"
#include "Defines.h"
#include <math.h>
Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::update(float dt)
{
// TODO (gust#3#): Mover frame da animacao

    if(jumping)
    {
        //g_animationSpeed = 1, demora 0.5s para fazer 180 graus
        float timeSpeed = 180.f*g_animationSpeed;
        timeSpeed *= dt;
        degree += timeSpeed;
        mPositionOffset.y = -sin(degree * 3.14f/180.f)*0.1; //Pula 1/10 do quadrado

        g_animationsLeft = true;

        if(degree > 180) {
            mPositionOffset.y = 0;
            degree = 0;
            jumping = false;
        }
    }
}

sf::Vector2f Animation::getPosition()
{
    return mPosition + mPositionOffset;
}
void Animation::jumpAnimation()
{
    jumping = true;
}

bool Animation::isJumping()
{
    return jumping;
}
