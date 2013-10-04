#include "StateGame.h"

#include "ConsoleInfo.h"
#include "Player.h"
#include "MetaEngine.h"
#include "TextureManager.h"
#include "ResourceManager.h"
#include "Map.h"
#include "Item.h"
#include "Defines.h"
#include "Procedural.h"
#include "DataHolder.h"

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
    mStack = stack;
    if(mStack != 3){
        DataHolder::DataControl.clearData();
    }else
    { //Recarrega mapa, mas não libera data
        mStack = 1;
    }

    if(mStack == 1)
    {
        if( Map::MapControl.loadMap("output_map.map") == false )
        {
            mStack = -1;
            mStado = GST_MENU;
            return;
        }

        Player::PlayerControl->movePosition(0,0);
    }else
    {
        Map& myMap = Map::MapControl;
        myMap.createMap(MAP_WIDTH,MAP_HEIGHT);

        switch(Procedural::ProceduralControl.mapType){
        case 0:
            Procedural::ProceduralControl.makeMap(myMap);
            break;
        case 1:
            Procedural::ProceduralControl.makeMapMiner(myMap);
            break;
        }

        Player::PlayerControl->movePosition(0,0);
    }
    if(mStack == 2)
    {
        Map::MapControl.saveMap();
    }

    sf::View& view = MetaEngine::EngineControl.getViewGame();
    view.setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
    window.setView(view);
}

int StateGame::unload()
{

    for(unsigned int i = 0; i < ObjectList.size(); ++i)
    {
        delete ObjectList[i];
    }

    ObjectList.clear();

    Map::MapControl.clearMap();

    Player::PlayerControl->resetPlayer();

    return mStack;
}
//--------------------- Events ------------------------------------
void StateGame::events(sf::Event& event)
{
    bool isConsole = ConsoleInfo::MessageControl.isConsoleOnline();

    ConsoleInfo::MessageControl.events(event);
    Player::PlayerControl->events(event);

    if(ConsoleInfo::MessageControl.isReturn())
    {
        ConsoleInfo::MessageControl.setViewPortOnline(false);
        MetaEngine::EngineControl.getViewGame().setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
        window.setView(MetaEngine::EngineControl.getViewGame());

        render(); //Arruma Portview
        mStado = GST_MENU;

    }

    if(event.type == sf::Event::KeyPressed)
    {
        if(isConsole)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                sf::View& view = MetaEngine::EngineControl.getViewGame();
                view.setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
                window.setView(view);
            }
        }
        if(event.key.code == sf::Keyboard::Comma)
        {
            DataHolder::DataControl.analyseData();
        }
        if(event.key.code == sf::Keyboard::F10)
        {
            mStado = GST_MENU;
        }
    }
}

//---------------------------- Update ------------------------------------
eStateType StateGame::update(unsigned int dt)
{
    if(mStado != GST_NONE) return mStado;

    if(Player::PlayerControl->mDead)
    {
        DataHolder::DataControl.addData();
        if(mStack == 1)
        {
            unload();
            load(3);
            cout << "Lose\n";
            return GST_NONE;
        }
        return GST_LOSE;
    }

    Player::PlayerControl->update(dt);

    if(Player::PlayerControl->mHasWon)
    {
        DataHolder::RunData.win = true;
        DataHolder::DataControl.addData();
        if(mStack == 1)
        {
            unload();
            load(3);
            cout << "Win\n";
            return GST_NONE;
        }
        return GST_WIN;
    }
    if(Player::PlayerControl->mHasMoved)
    {
        DataHolder::RunData.steps++;
        //Atualiza posição da camera
        sf::View& view = MetaEngine::EngineControl.getViewGame();
        view.setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
        window.setView(view);
        //Atualiza inimigos e itens
        for(unsigned int i = 0; i < ObjectList.size();++i)
        {
            ObjectList[i]->update(0, Player::PlayerControl->mSpeedCost);
        }
    }
    return GST_NONE;
}

void StateGame::render()
{
    if(mStado != GST_NONE ) return;

    Map::MapControl.draw();
    for(unsigned int i = 0; i < ObjectList.size();++i)
    {
        ObjectList[i]->draw();
    }
    Player::PlayerControl->draw();
    ConsoleInfo::MessageControl.draw();

    Player::PlayerControl->resetMoved();
}
