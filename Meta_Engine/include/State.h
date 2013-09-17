#pragma once

#include <SFML/Graphics.hpp>

typedef enum eStateType {
    GST_GAME,
    GST_MENU,
    GST_QUIT,
    GST_NONE
} StateType;

class State
{
    public:
        virtual void load(int stack = 0) = 0;
        virtual int unload() = 0;
        virtual eStateType update(unsigned int dt) = 0;
        virtual void render() = 0;
        virtual void events(sf::Event event) = 0;
        virtual ~State(){};
        State(sf::RenderWindow& wnd) : window(wnd){mStack = 0;};

    protected:
        sf::RenderWindow& window;
        int mStack;
};

