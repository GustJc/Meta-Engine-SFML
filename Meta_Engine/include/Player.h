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

        void update(unsigned int dt = 0);
        void events(sf::Event& event);
        void startController();
        void resetMoved();

        static Player PlayerControl;

        bool mHasMoved;
        bool isBot;
    protected:
        void runBotAI();

        int mDelay;
    private:
};
