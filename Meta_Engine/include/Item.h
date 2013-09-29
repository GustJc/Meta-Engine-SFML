#pragma once
#include "GameObject.h"
class Item : public GameObject
{
    public:
        Item();
        Item(bool buff, int hpAtk, int mpDef, int idX, int idY = -1);
        Item(int gold, int idX, int idY = -1);
        virtual ~Item();


// TODO (gust#9#): Adicionar equipar, para jogador e inimigo.

        void useItem(); //Atualmente somente jogador
        //Futuro protected
        int mAtk;
        int mDef;
        int mHp;
        int mMp;
        int mGold;
        bool mIsBuff;

    protected:
    private:
};
