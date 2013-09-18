#pragma once

#define N_KEYS 512
#define N_MOUSE_BUTTONS 5

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class InputManager
{
    public:
        virtual ~InputManager();
        InputManager* getInstance();

        void update();
        bool isKeyDown(sf::Keyboard::Key key);
        bool isKeyUp(sf::Keyboard::Key key);
        bool isKeyPressed(sf::Keyboard::Key key);
        bool isMouseDown(sf::Mouse::Button button);
        bool isMouseUp(sf::Mouse::Button button);
        bool isMousePressed(sf::Mouse::Button button);
        int mousePosX();
        int mousePosY();
        bool isMouseInside(const sf::IntRect& rect);

    protected:
        void resetStates();
    private:
        static InputManager *instance;
        InputManager();

        uint8_t keyDown[N_KEYS], keyUp[N_KEYS];
        uint8_t mouseDown[N_MOUSE_BUTTONS], mouseUp[N_MOUSE_BUTTONS];
        int mouseX, mouseY;

};
