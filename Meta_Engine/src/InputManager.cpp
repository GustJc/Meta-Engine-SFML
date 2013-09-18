#include "InputManager.h"

#include <SFML/Window/Event.hpp>
#include "MetaEngine.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
    if(instance != nullptr)
        delete instance;
}

InputManager* InputManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new InputManager();
    }

    return instance;

}

void InputManager::resetStates()
{
    for(int i = 0; i < N_KEYS; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < N_MOUSE_BUTTONS; i++){
        mouseDown[i] = false;
        mouseUp[i] = false;
    }
}


void InputManager::update()
{
    sf::Event event;
    while(MetaEngine::EngineControl.getWindowReference().pollEvent(event))
    {

    }
}

bool InputManager::isKeyDown(sf::Keyboard::Key key)
{
    return keyDown[key];
}

bool InputManager::isKeyUp(sf::Keyboard::Key key)
{
    return keyUp[key];
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::isMouseDown(sf::Mouse::Button button)
{
    return mouseDown[button];
}

bool InputManager::isMouseUp(sf::Mouse::Button button)
{
    return mouseUp[button];
}

bool InputManager::isMousePressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

int InputManager::mousePosX()
{
    return sf::Mouse::getPosition().x;
}

int InputManager::mousePosY()
{
    return sf::Mouse::getPosition().y;
}

bool InputManager::isMouseInside(const sf::IntRect& rect)
{
    return rect.contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}
