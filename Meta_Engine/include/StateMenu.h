#include "State.h"
#include <SFGUI/SFGUI.hpp>
class StateMenu : public State
{
    public:
        StateMenu(sf::RenderWindow& wnd);
        virtual ~StateMenu();
        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
    protected:
        sfg::Window::Ptr dataWindow;
        sfg::Notebook::Ptr noteBook;
        sfg::SpinButton::Ptr spinRuns;
        sfg::SpinButton::Ptr spinMaps;
        sfg::SpinButton::Ptr spinMapX;
        sfg::SpinButton::Ptr spinMapY;
        sfg::SpinButton::Ptr spinRooms;
        sfg::SpinButton::Ptr spinRoomsSizeMax;
        sfg::SpinButton::Ptr spinRoomsSizeMin;
        sfg::Box::Ptr boxDataV;
        sfg::Box::Ptr boxDataV2;
        sfg::Box::Ptr boxDataH;
    protected:
        void ClickStart();
        void ClickExit();
        void ClickLoad();
        void ClickSave();
        void ClickOpcoes();

        void SetOptions();
        sfg::Window::Ptr guiWindow;
        sfg::Desktop guiDesktop;
        sfg::Button::Ptr buttonStart;
        sfg::Button::Ptr buttonLoadFromMap;
        sfg::Button::Ptr buttonStartSaveMap;
        sfg::Button::Ptr buttonOpcoes;
        sfg::Button::Ptr buttonQuit;
        sfg::Box::Ptr box;

    private:
};

