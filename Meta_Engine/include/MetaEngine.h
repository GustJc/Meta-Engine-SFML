#pragma once
#include <SFML/Graphics.hpp>

class MetaEngine
{
    public:

        static MetaEngine EngineControl;
        void drawRect(int x, int y, int w, int h, sf::Color color);
        void drawRectVertex(int x, int y, int w, int h, sf::Color color);

        sf::RenderWindow& getWindowReference();
        sf::Font& getFont();

        MetaEngine();
        virtual ~MetaEngine();
    protected:
    private:
        sf::RenderWindow mWindow;
        sf::Font mFont;

};
