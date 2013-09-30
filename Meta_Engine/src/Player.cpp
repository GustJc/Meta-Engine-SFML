#include "Player.h"

#include <SFML/Window/Event.hpp>
#include "Defines.h"
#include "MetaEngine.h"
#include "Tile.h"
#include "Map.h"
#include "LuaManager.h"
#include <string>
#include <sstream>

Player* Player::PlayerControl = nullptr;

Player::Player()
{
    //ctor
    mGold = 0;
    mHasMoved = false;
    mDelay = 0;
    mSpeedCost = 100;
    type = TYPE_PLAYER;
    isBot = false;
}

Player::~Player()
{
    //dtor
}

void Player::events(sf::Event& event)
{
    if(MetaEngine::EngineControl.isEventsPaused()) return;

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Period)
        {
            mHasMoved = true;
        }
        if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            this->movePosition(0,-1);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            this->movePosition(0,1);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
        {
            this->movePosition(1,0);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
        {
            this->movePosition(-1,0);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::Num1)
        {
            this->movePosition(-1,1);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::Num3)
        {
            this->movePosition(1,1);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::Num7)
        {
            this->movePosition(-1,-1);
            mHasMoved = true;
        } else
        if(event.key.code == sf::Keyboard::Num9)
        {
            this->movePosition(1,-1);
            mHasMoved = true;
        }
    }
}
void Player::draw()
{
    Entity::draw();
    //temporario, imprime valores
    sf::RenderWindow& window = MetaEngine::EngineControl.getWindowReference();
    std::stringstream stringTxt;
    stringTxt << "Gold: " << mGold;
    sf::Text txt(stringTxt.str(), MetaEngine::EngineControl.getFont(), 12);
    txt.setColor(sf::Color::Yellow);
    txt.setPosition(window.mapPixelToCoords(
                                    sf::Vector2i(5,100)) );
    window.draw(txt);
    //Stats
    stringTxt.str(std::string());       stringTxt << "HP: " << mHP;
    txt.setString(stringTxt.str());     txt.setColor(sf::Color::Red);
    txt.setPosition(window.mapPixelToCoords(
                                    sf::Vector2i(5,100+20*1)) );
    window.draw(txt);
    //Stats
    stringTxt.str(std::string());       stringTxt << "MP: " << mMP;
    txt.setString(stringTxt.str());     txt.setColor(sf::Color::Blue);
    txt.setPosition(window.mapPixelToCoords(
                                    sf::Vector2i(5,100+20*2)) );
    window.draw(txt);
    //Stats
    stringTxt.str(std::string());       stringTxt << "Atk: " << mAtk;
    txt.setString(stringTxt.str());     txt.setColor(sf::Color::Magenta);
    txt.setPosition(window.mapPixelToCoords(
                                    sf::Vector2i(5,100+20*3)) );
    window.draw(txt);
    //Stats
    stringTxt.str(std::string());       stringTxt << "Def: " << mAtk;
    txt.setString(stringTxt.str());     txt.setColor(sf::Color::Magenta);
    txt.setPosition(window.mapPixelToCoords(
                                    sf::Vector2i(5,100+20*4)) );
    window.draw(txt);
}
void Player::update(unsigned int dt)
{
    if(mDead) return;

    if(MetaEngine::EngineControl.isEventsPaused()) return;

    if(mHP <= 0)
    {
        mDead = true;
        return;
    }


    Tile* tile = Map::MapControl.getTile(mPosition.x, mPosition.y);
    if(tile->id == TILE_FINISH_LV)
    {
        cout << "Win!" << endl;
        getchar();
        exit(0);
    }

    Map::MapControl.setPassed(mPosition.x, mPosition.y);

    for(int i = -mRange; i <= mRange; ++i)
    {
        for(int j = -mRange; j <= mRange; ++j)
        {
            float dist = (abs(mPosition.x+i - mPosition.x)
                  + abs(mPosition.y+j - mPosition.y));

            if(dist > mRange) continue;

            int kx = mPosition.x+i;
            int ky = mPosition.y+j;

            Tile* tile = Map::MapControl.getTile(kx,ky);
            if(tile == nullptr) continue;

            Map::MapControl.setSeen(kx, ky);
        }
    }



    if(isBot)
    {
        mDelay += dt;
        if(mDelay < 100) return;

        //cout << "Position: "<< mPosition.x <<", " << mPosition.y << endl;
        cout << "temp: " << mDelay << endl;

        mDelay -= 100;

        runBotAI();
        mHasMoved = true;
    }
}

void Player::startController()
{

}


void Player::runBotAI()
{
    LuaManager::LuaControl.doFile("./playerExplorer.lua");
}
void Player::resetMoved()
{
    mHasMoved = false;
}


