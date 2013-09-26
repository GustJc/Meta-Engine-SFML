#include "StateGame.h"

#include "ConsoleInfo.h"
#include "Player.h"
#include "MetaEngine.h"
#include "TextureManager.h"
#include "Map.h"

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
    TextureManager::TextureControl.load(Textures::ID::MAP, "data/img/tileset.png");
    Map::MapControl.setSprite(TextureManager::TextureControl.get(Textures::ID::MAP));
}

int StateGame::unload()
{
    return mStack;
}
void StateGame::events(sf::Event& event)
{
    ConsoleInfo::MessageControl.events(event);
    Player::PlayerControl.events(event);
}
eStateType StateGame::update(unsigned int dt)
{

    Player::PlayerControl.update(dt);
    return GST_NONE;
}

void StateGame::render()
{

    ConsoleInfo::MessageControl.draw();
    Player::PlayerControl.resetMoved();

/*
    sf::Sprite sp(TextureManager::TextureControl.get(Textures::ID::MAP));
    sp.setPosition(MetaEngine::EngineControl.getWindowReference().mapPixelToCoords(sf::Vector2i(100,100)));
    sp.setTextureRect(sf::IntRect(0,0,16,16));
    MetaEngine::EngineControl.getWindowReference().draw(sp);
    */
}
