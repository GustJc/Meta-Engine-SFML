#include "PlayerController.h"

#include <SFML/Window/Event.hpp>
#include "Entity.h"

PlayerController::PlayerController()
{
    //ctor
    player = nullptr;
}

PlayerController::~PlayerController()
{
    //dtor
}

void PlayerController::events(sf::Event& event)
{
    if(player == nullptr) return;

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::W)
        {
            player->movePosition(0,-1);
        } else
        if(event.key.code == sf::Keyboard::S)
        {
            player->movePosition(0,1);
        } else
        if(event.key.code == sf::Keyboard::D)
        {
            player->movePosition(1,0);
        } else
        if(event.key.code == sf::Keyboard::A)
        {
            player->movePosition(-1,0);
        } else
        if(event.key.code == sf::Keyboard::Num1)
        {
            player->movePosition(-1,1);
        } else
        if(event.key.code == sf::Keyboard::Num3)
        {
            player->movePosition(1,1);
        } else
        if(event.key.code == sf::Keyboard::Num7)
        {
            player->movePosition(-1,-1);
        } else
        if(event.key.code == sf::Keyboard::Num9)
        {
            player->movePosition(1,-1);
        }
    }
}
