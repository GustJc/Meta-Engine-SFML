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
#include "StateGame.h"
#include "LuaManager.h"
#include "Entity.h"
#include "PlayerController.h"


using namespace std;
int GameManager::run(int argc, char* args[])
{

    LuaManager::LuaControl.loadConfigs("config.lua", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE);


    cout << "w=" << MAP_WIDTH << " h=" << MAP_HEIGHT << " ts=" << TILE_SIZE << endl;


    MetaEngine& en = MetaEngine::EngineControl;

    sf::Text t("", en.getFont());


    sf::RenderWindow& window = en.getWindowReference();
    window.setKeyRepeatEnabled(false);


    sf::View view = window.getView();
    view.setSize(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    window.setView(view);

    Map myMap;
    myMap.createMap(MAP_WIDTH,MAP_HEIGHT);
    //myMap.setTile(0,0,0,1);
    //myMap.setTile(39,0,0,1);
    //myMap.setTile(0,29,0,1);

    Procedural procedural;
    int mapType = 0;
    for(int i = 0; i < argc; ++i)
    {
        string s = args[i];
        if(s.compare("-s") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando numero de salas: " << num << endl;
            procedural.n_Salas = num;
        }
        else if(s.compare("-w") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando tamanho minimo: " << num << endl;
            procedural.min_width = num;
        }
        else if(s.compare("-W") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando tamanho maximo: " << num << endl;
            procedural.max_width = num;
        }
        else if(s.compare("-M") == 0)
        {
            mapType = 1;
            cout << "Usando Miner" << endl;
        }
        else if(s.compare("-v") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando Vida minimo: " << num << endl;
            procedural.vida_min = num;
        }
        else if(s.compare("-V") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando Vida maximo: " << num << endl;
            procedural.vida_max = num;
        }
        else if(s.compare("-c") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando chance(total 10.000) de spawn: " << num << endl;
            procedural.chance_spawn = num;
        }
        else if(s.compare("-t") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando total life: " << num << endl;
            procedural.total_life = num;
        }
        else if(s.compare("-map-w") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando map width: " << num << endl;
            MAP_WIDTH = num;
        }
        else if(s.compare("-map-h") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando map height: " << num << endl;
            MAP_HEIGHT = num;
        }
        else if(s.compare("-map-tile") == 0 && i < (argc-1))
        {
            string s2 = args[i+1];
            int num = std::stoi(s2);
            cout << "Usando map height: " << num << endl;
            TILE_SIZE = num;
        }
    }
    switch(mapType){
    case 0:
        procedural.makeMap(myMap);
        break;
    case 1:
        procedural.makeMapMiner(myMap);
        break;
    }
//Lua testes
    LuaManager lMan;
    lMan.BaseLuaInterpreter();

///Carrega estado inicial
    mEstadoAtual = new StateGame(window);
    Entity player(ENT_PLAYER);
    player.setPosition(5,5);
    PlayerController controller;
    controller.player = &player;
///Inicio loop principal
    sf::Clock tempoDecorrido;
    while(window.isOpen()){

        //Eventos
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            /*
            if(event.type == sf::Event::KeyPressed){
                window.close();
            }
            */
            mEstadoAtual->events(event);
            controller.events(event);
        }
        //Update
        switch(mEstadoAtual->update(tempoDecorrido.getElapsedTime().asSeconds() )  )
        {
        case GST_QUIT:
            mEstadoAtual->unload();
            delete mEstadoAtual;
            mEstadoAtual = nullptr;
            window.close();
            break;
        case GST_NONE:
            break;
        default:
            break;
        }
        //Limpa a tela
        window.clear();
        sf::View view = window.getView();
        view.setCenter(player.getPosition().x*TILE_SIZE-TILE_SIZE/4, player.getPosition().y*TILE_SIZE-TILE_SIZE/4);
        window.setView(view);
        //Desenha
        mEstadoAtual->render();

        t.setString("Hellow");
        t.setPosition(10,10);
        myMap.draw();
        player.draw();
        en.getWindowReference().draw(t);


/*
        sf::Clock time1;
        sf::Clock time2;

        window.draw(circle);
        time1.restart();
        en.drawRect(10,10,100,100,sf::Color::Red);
        std::cout << "Rectangle time: "<<  time1.getElapsedTime().asMicroseconds() << "\n";

        time2.restart();
        en.drawRectVertex(200,200,100,100,sf::Color::Red);
        std::cout << "RectangleVertex time: " << time2.getElapsedTime().asMicroseconds() << "\n";
*/



        //window.draw(circle);
        window.display();
    }
    return 0;
}

GameManager::GameManager()
{
    //ctor
    stack = 0;
    mEstadoAtual = NULL;
}

GameManager::~GameManager()
{
    //dtor
}
