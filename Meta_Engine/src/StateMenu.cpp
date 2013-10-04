#include "StateMenu.h"
#include "MetaEngine.h"
#include "Defines.h"



StateMenu::StateMenu(sf::RenderWindow& wnd)
: State(wnd)
{

}

StateMenu::~StateMenu()
{

}

void StateMenu::load(int stack)
{
    window.resetGLStates();

    guiWindow = sfg::Window::Create(sfg::Window::BACKGROUND);
    guiWindow->SetTitle("Menu");



    box = sfg::Box::Create(sfg::Box::VERTICAL );

    buttonStart = sfg::Button::Create();
    buttonStart->SetLabel("Inicia Jogo");
    buttonQuit = sfg::Button::Create();
    buttonQuit->SetLabel("Sair");
    buttonLoadFromMap = sfg::Button::Create();
    buttonLoadFromMap->SetLabel("Inicia de Mapa");
    buttonStartSaveMap = sfg::Button::Create();
    buttonStartSaveMap->SetLabel("Inicia e salva Mapa");

    buttonStart->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickStart, this );
    buttonQuit->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickExit, this );
    buttonLoadFromMap->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickLoad, this );
    buttonStartSaveMap->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickSave, this );

    box->Pack(buttonStart);
    box->Pack(buttonLoadFromMap);
    box->Pack(buttonStartSaveMap);
    box->Pack(buttonQuit);

    box->SetSpacing( 5.f );

    guiWindow->Add( box );


    guiWindow->SetPosition(sf::Vector2f(WINDOW_WIDTH/2 - guiWindow->GetAllocation().width/2,
                                        WINDOW_HEIGHT/2 - guiWindow->GetAllocation().height/2) );

    guiDesktop.Add(guiWindow);



}

int StateMenu::unload()
{
    return mStack;
}

eStateType StateMenu::update(unsigned int dt)
{
    //guiWindow->Update( dt );

    guiDesktop.Update(dt);


    return mStado;
}

void StateMenu::events(sf::Event& event)
{
    guiDesktop.HandleEvent( event );
    //guiWindow->HandleEvent( event );
}

void StateMenu::render()
{
    MetaEngine::EngineControl.getSFGUIReference().Display(window);
    //MetaEngine::EngineControl.drawRectVertex(0,0,100,100,sf::Color::Blue);

}

void StateMenu::ClickStart()
{
    mStado = GST_GAME;
}

void StateMenu::ClickExit()
{
    mStado = GST_QUIT;
}

void StateMenu::ClickLoad()
{
    mStado = GST_GAME;
    mStack = 1; //Load From Map Start
}

void StateMenu::ClickSave()
{
    mStado = GST_GAME;
    mStack = 2; //Save To Map Start
}
