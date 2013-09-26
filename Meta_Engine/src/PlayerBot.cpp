#include "PlayerBot.h"
#include "Defines.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
using namespace std;

PlayerBot::PlayerBot()
{
    //ctor
    mDelay = 0;
}

PlayerBot::~PlayerBot()
{
    //dtor
}
void PlayerBot::startBot(Entity& Player)
{
    mPlayer = &Player;

    cout << mPlayer->getPosition().x << endl;

    KnowledMap.clear();
    KnowledMap.resize(MAP_WIDTH);

    for(int i = 0; i < MAP_WIDTH; ++i)
    {
        KnowledMap[i].resize(MAP_HEIGHT, TILE_NONE);
    }


}


void PlayerBot::update(unsigned int dt)
{
    mDelay += dt;
    if(mDelay < 100) return;
}

void PlayerBot::runAI()
{


}
