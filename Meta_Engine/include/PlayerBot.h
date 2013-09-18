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

    protected:
        std::vector<std::vector<Tile> > KnowledMap;
        Entity* mPlayer;
    private:
};
