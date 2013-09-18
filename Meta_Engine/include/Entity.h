#pragma once
#include "GameObject.h"
enum ENUM_ENT_TYPE{
    ENT_PLAYER,
    ENT_ENEMY
};

class Entity : public GameObject
{
    public:
        Entity(ENUM_ENT_TYPE tipo);
        Entity();
        virtual ~Entity();

        void draw();

        ENUM_ENT_TYPE type;
    //futuro protected
        double mSpeed;
        double mDelay;
        int mAtk;
        int mDef;
        int mRange;
    protected:
    private:
};
