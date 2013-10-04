#include "State.h"
#include <SFGUI/SFGUI.hpp>
class StateMenu : public State
{
    public:
        StateMenu(sf::RenderWindow& wnd);
        virtual ~StateMenu();
        void load(int stack = 0);
        int unload();
        eStateType update(unsigned int dt);
        void events(sf::Event& event);
        void render();
    protected:

        void ClickStart();
        void ClickExit();
        void ClickLoad();
        void ClickSave();
        sfg::Window::Ptr guiWindow;
        sfg::Desktop guiDesktop;
        sfg::Button::Ptr buttonStart;
        sfg::Button::Ptr buttonLoadFromMap;
        sfg::Button::Ptr buttonStartSaveMap;
        sfg::Button::Ptr buttonQuit;
        sfg::Box::Ptr box;

    private:
};

