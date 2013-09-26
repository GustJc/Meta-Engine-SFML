#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
class MetaEngine
{
    public:

        static MetaEngine EngineControl;
        void drawRect(int x, int y, int w, int h, sf::Color color);
        void drawRectVertex(int x, int y, int w, int h, sf::Color color);

        sf::RenderWindow& getWindowReference();
        sf::Font& getFont();
        sf::View& getViewGame();


        bool isEventsPaused();
        void setEventsPaused(bool pause = true);
        bool isMapFog();
        void setMapFog(bool fog = true);


        MetaEngine();
        virtual ~MetaEngine();
    protected:
        bool mEventsPaused;
        bool mMapFog;
        //bool mPaused;
    private:
        sf::RenderWindow mWindow;
        sf::Font mFont;
        sf::View mViewGame;
};
extern std::vector<Entity*> EntityList;
