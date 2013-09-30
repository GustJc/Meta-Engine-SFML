#include "StateGame.h"

#include "ConsoleInfo.h"
#include "Player.h"
#include "MetaEngine.h"
#include "TextureManager.h"
#include "ResourceManager.h"
#include "Map.h"
#include "Item.h"

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


    /* testes
    Entity* enTest = new Entity(TYPE_ENEMY);
    //As vezes cria fora do map e erro de seg
    enTest->setPosition(Player::PlayerControl->getPosition().x+2, Player::PlayerControl->getPosition().y+1);
    enTest->mSpeedCost = 200;
    enTest->geraRota(Player::PlayerControl->getPosition().x, Player::PlayerControl->getPosition().y);
    enTest->addToObjectList();
    enTest->setTexture(TextureManager::TextureControl.get(Textures::ID::CHARS));
    enTest->changeSprite(1,0);

    Player::PlayerControl->setTexture(TextureManager::TextureControl.get(Textures::ID::CHARS));
    Player::PlayerControl->changeSprite(0);

    Item* item = new Item(3,0);
    item->setPosition(Player::PlayerControl->getPosition().x-2, Player::PlayerControl->getPosition().y+1);
    item->addToObjectList();

    ResourceManager::ResourceControl.addGold(Player::PlayerControl->getPosition().x-1, Player::PlayerControl->getPosition().y-1,
                                             120);
    */
}

int StateGame::unload()
{

    for(unsigned int i = 0; i < ObjectList.size(); ++i)
    {
        delete ObjectList[i];
    }

    ObjectList.clear();

    return mStack;
}
void StateGame::events(sf::Event& event)
{
    ConsoleInfo::MessageControl.events(event);
    Player::PlayerControl->events(event);
}
eStateType StateGame::update(unsigned int dt)
{
    if(Player::PlayerControl->mDead)
    {
        return GST_LOSE;
    }

    Player::PlayerControl->update(dt);
    if(Player::PlayerControl->mHasMoved)
    {
        for(unsigned int i = 0; i < ObjectList.size();++i)
        {
            ObjectList[i]->update(0, Player::PlayerControl->mSpeedCost);
        }
    }
    return GST_NONE;
}

void StateGame::render()
{

    Map::MapControl.draw();
    for(unsigned int i = 0; i < ObjectList.size();++i)
    {
        ObjectList[i]->draw();
    }
    Player::PlayerControl->draw();

    Player::PlayerControl->resetMoved();
    ConsoleInfo::MessageControl.draw();

/*
    sf::Sprite sp(TextureManager::TextureControl.get(Textures::ID::MAP));
    sp.setPosition(MetaEngine::EngineControl.getWindowReference().mapPixelToCoords(sf::Vector2i(100,100)));
    sp.setTextureRect(sf::IntRect(0,0,16,16));
    MetaEngine::EngineControl.getWindowReference().draw(sp);
    */
}
