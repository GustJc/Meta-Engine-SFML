#include "MetaEngine.h"
#include "Defines.h"

std::vector<GameObject*> ObjectList;
MetaEngine MetaEngine::EngineControl;
void MetaEngine::drawRect(int x, int y, int w, int h, sf::Color color)
{
    sf::RectangleShape rect(sf::Vector2f(x,y));

    rect.setSize(sf::Vector2f(w,h));
    rect.setFillColor(color);

    mWindow.draw(rect);

}

void MetaEngine::drawRectVertex(int x, int y, int w, int h, sf::Color color)
{
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
    quad[0].position = sf::Vector2f(x,y);
    quad[1].position = sf::Vector2f(x+w,y);
    quad[2].position = sf::Vector2f(x+w,y+h);
    quad[3].position = sf::Vector2f(x,y+h);

    mWindow.draw(quad);
}

sf::RenderWindow& MetaEngine::getWindowReference()
{
    return mWindow;
}
sfg::SFGUI& MetaEngine::getSFGUIReference()
{
    return mSfgui;
}

sf::Font& MetaEngine::getFont()
{
    return mFont;
}

sf::View& MetaEngine::getViewGame()
{
    return mViewGame;
}

MetaEngine::MetaEngine() :
mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close)
{
    mFont.loadFromFile("arial.ttf");

    mViewGame.setSize(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    mEventsPaused = false;

    mMapFog = true;
}

MetaEngine::~MetaEngine()
{

}


//-------- Getters Setters

bool MetaEngine::isEventsPaused()
{
    return mEventsPaused;
}

void MetaEngine::setEventsPaused(bool pause)
{
    mEventsPaused = pause;
}

bool MetaEngine::isMapFog()
{
    return mMapFog;
}

void MetaEngine::setMapFog(bool fog)
{
    mMapFog = fog;
}
