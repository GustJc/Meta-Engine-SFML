#pragma once

namespace sf
{
    class Event;
}

#include "Entity.h"

class Player : public Entity
{
    public:
        Player();
        virtual ~Player();

        void draw();
        void update(float dt = 0);
        void events(sf::Event& event);
        void startController();
        void resetMoved();
        void resetPlayer();

        virtual void movePosition(int x = 0, int y = 0);

        static Player* PlayerControl;

        bool mHasWon;
        bool mHasMoved;
        bool mHasNewTiles;
        int  mHasEnemys;
        bool isBot;

        int mGold;
        int mBotDelay;
    protected:
        void runBotAI();

        int mDelay;
    private:
};
