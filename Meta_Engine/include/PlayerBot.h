#pragma once

#include <vector>

#include "Tile.h"
#include "Entity.h"

class PlayerBot
{
    public:
        PlayerBot();
        virtual ~PlayerBot();

        void startBot(Entity& Player);

        void update(unsigned int dt);

    protected:
        std::vector<std::vector<int> > KnowledMap;
        Entity* mPlayer;
        unsigned int mDelay;

        void runAI();
    private:
};
