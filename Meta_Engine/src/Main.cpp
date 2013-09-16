#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "MetaEngine.h"
#include "Map.h"
#include "Procedural.h"
#include <iostream>
#include <string>

using namespace std;
sf::Font font;
int main(int argc, char* args[]){
/*
    try{
    TextureManager manager;
    manager.load(Textures::ID::Gust, "mdia/aa.pjg");
    } catch ( std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        return 1;
    }
*/

    MetaEngine& en = MetaEngine::EngineControl;

    sf::RenderWindow& window = en.getWindowReference();

    Map myMap;
    myMap.createMap(40,30);
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
    }
    switch(mapType){
    case 0:
        procedural.makeMap(myMap);
        break;
    case 1:
        procedural.makeMapMiner(myMap);
        break;
    }


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            else
            if(event.type == sf::Event::KeyPressed){
                window.close();
            }
        }


        window.clear();
        myMap.draw();

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
