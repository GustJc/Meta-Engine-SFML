#pragma once
#include <SFML/Graphics.hpp>

class MetaEngine
{
    public:

        static MetaEngine EngineControl;
        void drawRect(int x, int y, int w, int h, sf::Color color);
        void drawRectVertex(int x, int y, int w, int h, sf::Color color);

        sf::RenderWindow& getWindowReference();

        MetaEngine();
        virtual ~MetaEngine();
    protected:
    private:
        sf::RenderWindow mWindow;

};
