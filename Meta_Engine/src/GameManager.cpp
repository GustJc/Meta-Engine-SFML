#include "GameManager.h"

#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "MetaEngine.h"
#include "Map.h"
#include "Procedural.h"
#include <iostream>
#include <string>
#include "Defines.h"
#include "LuaManager.h"
#include "Entity.h"
#include "Player.h"
#include "ConsoleInfo.h"

#include "ResourceManager.h"
#include "StateGame.h"
#include "StateMenu.h"

using namespace std;


int GameManager::run(int argc, char* args[])
{
    LuaManager::LuaControl.loadConfigs("config.lua", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE);
    cout << "w=" << MAP_WIDTH << " h=" << MAP_HEIGHT << " ts=" << TILE_SIZE << endl;


    sf::RenderWindow& window = MetaEngine::EngineControl.getWindowReference();
    window.setKeyRepeatEnabled(false);

    sf::View& view = MetaEngine::EngineControl.getViewGame();
    view.setSize(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    window.setView(view);

    loadMainTextures();
    LuaManager::LuaControl.startLua();



    Procedural& procedural = Procedural::ProceduralControl;
    for(int i = 0; i < argc; ++i)
    {
        string s = args[i];
        if(s.compare("-s") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando numero de salas: " << num << endl;
            procedural.n_Salas = num;
        }
        else if(s.compare("-w") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando tamanho minimo: " << num << endl;
            procedural.min_width = num;
        }
        else if(s.compare("-W") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando tamanho maximo: " << num << endl;
            procedural.max_width = num;
        }
        else if(s.compare("-M") == 0)
        {
            procedural.mapType = 1;
            cout << "Usando Miner" << endl;
        }
        else if(s.compare("-v") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando Vida minimo: " << num << endl;
            procedural.vida_min = num;
        }
        else if(s.compare("-V") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando Vida maximo: " << num << endl;
            procedural.vida_max = num;
        }
        else if(s.compare("-c") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando chance(total 10.000) de spawn: " << num << endl;
            procedural.chance_spawn = num;
        }
        else if(s.compare("-t") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando total life: " << num << endl;
            procedural.total_life = num;
        }
        else if(s.compare("-map-w") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando map width: " << num << endl;
            MAP_WIDTH = num;
        }
        else if(s.compare("-map-h") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando map height: " << num << endl;
            MAP_HEIGHT = num;
        }
        else if(s.compare("-map-tile") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = atoi(s2.c_str());
            cout << "Usando map height: " << num << endl;
            TILE_SIZE = num;
        }
    }




// - - - - - - - - - - - Carrega estado inicial - - - - - - - - - - - -
    mEstadoAtual = new StateMenu(window);
    mEstadoAtual->load();

    ConsoleInfo::MessageControl.init();

// - - - - - - - Testes
    executeTests();
    window.setFramerateLimit(60);
// - - - - - - - - - - - Loop Principal - - - - - - - - - - - - - - - -
    sf::Clock tempoDecorrido;
    while(window.isOpen()){

        //Eventos
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            mEstadoAtual->events(event);
        }
        float dt = tempoDecorrido.getElapsedTime().asSeconds();
        tempoDecorrido.restart();
        //Update
        switch(mEstadoAtual->update(dt )  )
        {

        case GST_LOSE:
            {
                cout << "You Lose!" << endl;
                int mStack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new StateMenu(window);
                mEstadoAtual->load(mStack);
                break;
            }
        case GST_WIN:
            {
                cout << "You Win!" << endl;
                int mStack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new StateMenu(window);
                mEstadoAtual->load(mStack);
                break;
            }
        case GST_QUIT:
            mEstadoAtual->unload();
            delete mEstadoAtual;
            mEstadoAtual = nullptr;
            window.close();
            break;
        case GST_GAME:
            {
                int mStack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new StateGame(window);
                mEstadoAtual->load(mStack);
                break;
            }
        case GST_MENU:
            {
                int mStack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new StateMenu(window);
                mEstadoAtual->load(mStack);
                break;
            }
        case GST_NONE:
            break;
        default:
            break;
        }

        if(!mEstadoAtual) break;

        //Limpa a tela
        window.clear(sf::Color(10,10,10));


        //Desenha
        mEstadoAtual->render();

        window.display();
    }
    return 0;
}

GameManager::GameManager()
{
    //ctor
    stack = 0;
    mEstadoAtual = nullptr;
}

GameManager::~GameManager()
{
    if(mEstadoAtual == nullptr)
    {
        delete mEstadoAtual;
    }
    if(Player::PlayerControl != nullptr)
    {
        delete Player::PlayerControl;
    }
    //dtor
}


// - - - - - - - Testes - - - - - - - - - - - - - - - - - - - - - -
void GameManager::executeTests()
{
    bool testResourceCreation   = false;
    bool testExploration        = false;
    bool testManualCreation     = false;
    if(testResourceCreation)
    {
        Item* item = ResourceManager::ResourceControl.createItem("testPotion");
        item->mHp = 10;
        Item* item2 = new Item( *ResourceManager::ResourceControl.getItem("potion") );
        cout << "HP is: " << item2->mHp << endl;
        delete item2;

        Entity* ent = ResourceManager::ResourceControl.createEntity("testlv0");
        ent->mHP = 50;
        Entity* ent2 = new Entity( *ResourceManager::ResourceControl.getEntity("testlv0") );
        cout << "HP is: " << ent2->mHP << endl;
        delete ent2;
    }
    if(testExploration)
    {
        Player::PlayerControl->update(0);

        Map::MapControl.forceRemoveMapFlag(Player::PlayerControl->getPositionX()-2, Player::PlayerControl->getPositionY(), EX_SEEN);

        LuaManager::LuaControl.doFile("./testes.lua");
    }
    if(testManualCreation)
    {
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
    }
}



void GameManager::loadMainTextures()
{
    TextureManager::TextureControl.load(Textures::ID::MAP, "data/img/tileset.png");
    TextureManager::TextureControl.load(Textures::ID::CHARS, "data/img/chars.png");
    TextureManager::TextureControl.load(Textures::ID::ITENS, "data/img/itens.png");
    Map::MapControl.setSprite(TextureManager::TextureControl.get(Textures::ID::MAP));

    Player::PlayerControl = new Player();
    Player::PlayerControl->changeSprite(0);
}
