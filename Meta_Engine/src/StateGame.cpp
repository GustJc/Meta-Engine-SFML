#include "StateGame.h"

StateGame::StateGame(sf::RenderWindow& wnd) :
State(wnd)
{
    //ctor
}

StateGame::~StateGame()
{
    //dtor
}

void StateGame::load(int stack)
{

}

int StateGame::unload()
{
    return mStack;
}
void StateGame::events(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed){
        window.close();
    }
}
eStateType StateGame::update(unsigned int dt)
{
    return GST_NONE;
}

void StateGame::render()
{

}
