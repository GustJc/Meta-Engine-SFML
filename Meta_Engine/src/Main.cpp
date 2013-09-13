#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include <iostream>

sf::Font font;
int main(){

    try{
    TextureManager manager;
    manager.load(Textures::ID::Gust, "mdia/aa.pjg");
    } catch ( std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(640,480), "SFML Application");
    sf::CircleShape circle;
    circle.setRadius(40.0f);
    circle.setPosition(100.f,100.f);
    circle.setFillColor(sf::Color::Cyan);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }


        window.clear();

        window.draw(circle);
        window.display();
    }
    return 0;
}
