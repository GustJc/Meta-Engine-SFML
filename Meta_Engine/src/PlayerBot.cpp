#include "PlayerBot.h"

#include <iostream>
using namespace std;

PlayerBot::PlayerBot()
{
    //ctor
}

PlayerBot::~PlayerBot()
{
    //dtor
}
void PlayerBot::startBot(Entity& Player)
{
    mPlayer = &Player;

    cout << mPlayer->getPosition().x << endl;
}
