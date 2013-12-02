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

#include <sstream>

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
    if(mStack != GAME_RESET_START && mStack != GAME_RESET_LOAD){
        DataHolder::DataControl.clearData();
    }else
    { //Recarrega mapa, mas não libera data
        if(mStack == GAME_RESET_LOAD) {
            mStack = GAME_LOAD;
        } else
        if(mStack == GAME_RESET_START) {
            mStack = GAME_START;
        }
    }

    if(mStack == GAME_START)
    {
        Player::PlayerControl->isBot = true;
        if(DataHolder::DataControl.mMapsCount == 0)
        {
            createNewMap();
            DataHolder::DataControl.mMapsCount++;
            stringstream mstr; mstr << "testmap_" << DataHolder::DataControl.mMapsCount << "_" << DataHolder::DataControl.mMapsCount;
            Map::MapControl.saveMap(mstr.str());
        }
        else if (DataHolder::DataControl.mRunCount+1 <= DataHolder::DataControl.mRun)
        {
            stringstream mstr; mstr << "testmap_" << DataHolder::DataControl.mMapsCount << "_" << DataHolder::DataControl.mMapsCount;
            if( Map::MapControl.loadMap(mstr.str()) == false )
            {
                mStack = -1;
                mStado = GST_MENU;
                return;
            }
                Player::PlayerControl->movePosition(0,0);
        }
        DataHolder::DataControl.mRunCount++;
        //cout << "mRunCount " << DataHolder::DataControl.mRunCount << " de " << DataHolder::DataControl.mRun << endl;

        if(DataHolder::DataControl.mRunCount > DataHolder::DataControl.mRun)
        {

            DataHolder::DataControl.mMapsCount++;
            //cout << "mMAPCount " << DataHolder::DataControl.mMapsCount << " de " << DataHolder::DataControl.mMaps << endl;
            if(DataHolder::DataControl.mMapsCount > DataHolder::DataControl.mMaps)
            {
                DataHolder::DataControl.analyseData();
                mStado = GST_MENU;
                return;
            } else
            {
                cout << "New Map!" << endl;
            }
            DataHolder::DataControl.analyseData();
            DataHolder::DataControl.mRunCount=0;
            createNewMap();
            Player::PlayerControl->isBot = true;
            stringstream mstr; mstr << "testmap_" << DataHolder::DataControl.mMapsCount << "_" << DataHolder::DataControl.mMapsCount;
            Map::MapControl.saveMap(mstr.str());
            DataHolder::DataControl.clearData();
            DataHolder::DataControl.mRunCount++;
        }
        else
        {
            cout << "New Game!" << endl;
        }

    }
    else
    if(mStack == GAME_LOAD)
    {
        if( Map::MapControl.loadMap("output_map.map") == false )
        {
            mStack = -1;
            mStado = GST_MENU;
            return;
        }

        Player::PlayerControl->movePosition(0,0);
    }
    else
    if(mStack == GAME_SAVE)
    {
        createNewMap();
        Map::MapControl.saveMap();
    }

    sf::View& view = MetaEngine::EngineControl.getViewGame();
    view.setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
    window.setView(view);
}

void StateGame::createNewMap()
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
        if(mStack == GAME_START)
        {
            cout << "Lose\n";
            unload();
            load(GAME_RESET_START);
            return GST_NONE;
        }else
        if(mStack == GAME_LOAD)
        {
            cout << "Lose\n";
            unload();
            load(GAME_RESET_LOAD);
            return GST_NONE;
        }
        return GST_LOSE;
    }

    Player::PlayerControl->update(dt);

    if(Player::PlayerControl->mHasWon)
    {
        DataHolder::RunData.win = true;
        DataHolder::DataControl.addData();
        if(mStack == GAME_START)
        {
            cout << "Win\n";
            unload();
            load(GAME_RESET_START);
            return GST_NONE;
        }else
        if(mStack == GAME_LOAD)
        {
            cout << "Win\n";
            unload();
            load(GAME_RESET_LOAD);
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