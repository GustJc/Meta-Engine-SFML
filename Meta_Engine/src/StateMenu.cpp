#include "StateMenu.h"
#include "MetaEngine.h"
#include "Defines.h"
#include "Procedural.h"
#include "DataHolder.h"

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

//Set Fixed Menu
    guiWindow = sfg::Window::Create(sfg::Window::BACKGROUND);
    guiWindow->SetTitle("Menu");

    box = sfg::Box::Create(sfg::Box::VERTICAL );

    buttonStart = sfg::Button::Create();
    buttonStart->SetLabel("Inicia Jogo");
    buttonQuit = sfg::Button::Create();
    buttonQuit->SetLabel("Sair");
    buttonOpcoes = sfg::Button::Create();
    buttonOpcoes->SetLabel(L"Opções");
    buttonLoadFromMap = sfg::Button::Create();
    buttonLoadFromMap->SetLabel("Inicia de Mapa");
    buttonStartSaveMap = sfg::Button::Create();
    buttonStartSaveMap->SetLabel("Inicia e salva Mapa");

    buttonStart->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickStart, this );
    buttonQuit->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickExit, this );
    buttonLoadFromMap->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickLoad, this );
    buttonStartSaveMap->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickSave, this );
    buttonOpcoes->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StateMenu::ClickOpcoes, this );

    box->Pack(buttonStart);
    box->Pack(buttonLoadFromMap);
    box->Pack(buttonStartSaveMap);
    box->Pack(buttonOpcoes);
    box->Pack(buttonQuit);

    box->SetSpacing( 5.f );

    guiWindow->Add( box );


    guiWindow->SetPosition(sf::Vector2f(WINDOW_WIDTH/2 - guiWindow->GetAllocation().width/2,
                                        WINDOW_HEIGHT/2 - guiWindow->GetAllocation().height/2) );

    guiDesktop.Add(guiWindow);

//Set float options menu
    dataWindow = sfg::Window::Create(sfg::Window::BACKGROUND | sfg::Window::TITLEBAR | sfg::Window::SHADOW);
    dataWindow->SetTitle("Opcoes");
    noteBook = sfg::Notebook::Create();
    boxDataH  = sfg::Box::Create();
    boxDataV  = sfg::Box::Create(sfg::Box::VERTICAL);
    boxDataV2  = sfg::Box::Create(sfg::Box::VERTICAL);
    spinRuns = sfg::SpinButton::Create(1,300,1);
    spinMaps = sfg::SpinButton::Create(1,10,1);

    boxDataV->Pack(sfg::Label::Create(L"Número de jogos: "));
    boxDataV2->Pack(spinRuns);
    boxDataV->Pack(sfg::Label::Create("Numero de Mapas: "));
    boxDataV2->Pack(spinMaps);
    boxDataH->Pack(boxDataV);
    boxDataH->Pack(boxDataV2);

    noteBook->AppendPage( boxDataH, sfg::Label::Create("Dados"));

    boxDataH = sfg::Box::Create();
    boxDataV  = sfg::Box::Create(sfg::Box::VERTICAL);
    boxDataV2  = sfg::Box::Create(sfg::Box::VERTICAL);
    spinMapX = sfg::SpinButton::Create(1,200,1);
    spinMapY = sfg::SpinButton::Create(1,200,1);
    spinRooms = sfg::SpinButton::Create(1,30,1);
    spinRoomsSizeMax = sfg::SpinButton::Create(1,30,1);
    spinRoomsSizeMin = sfg::SpinButton::Create(1,20,1);

    boxDataV->Pack(sfg::Label::Create(L"Largura do mapa(X): "));
    boxDataV2->Pack(spinMapX);
    boxDataV->Pack(sfg::Label::Create(L"Altura do mapa(Y): "));
    boxDataV2->Pack(spinMapY);
    boxDataV->Pack(sfg::Label::Create(L"Número de salas: "));
    boxDataV2->Pack(spinRooms);
    boxDataV->Pack(sfg::Label::Create(L"Tamanho mínimo das salas: "));
    boxDataV2->Pack(spinRoomsSizeMin);
    boxDataV->Pack(sfg::Label::Create(L"Tamanho máximo das salas: "));
    boxDataV2->Pack(spinRoomsSizeMax);
    boxDataH->Pack(boxDataV);
    boxDataH->Pack(boxDataV2);

    noteBook->AppendPage( boxDataH, sfg::Label::Create("Mapa"));

    noteBook->SetScrollable(true);
	noteBook->SetRequisition( sf::Vector2f( 300.f, 0.f ) );
	dataWindow->Add(noteBook);

    dataWindow->Show(false);
    guiDesktop.Add(dataWindow);

    spinRuns->SetValue(5);
    spinMaps->SetValue(1);
    spinMapX->SetValue(40);
    spinMapY->SetValue(30);
    spinRooms->SetValue(8);
    spinRoomsSizeMax->SetValue(3);
    spinRoomsSizeMin->SetValue(3);

}

int StateMenu::unload()
{
    return mStack;
}

eStateType StateMenu::update(unsigned int dt)
{
    guiDesktop.Update(dt/1000.f);


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
    SetOptions();
    DataHolder::DataControl.resetCount();
    mStado = GST_GAME;
}

void StateMenu::ClickExit()
{
    mStado = GST_QUIT;
}

void StateMenu::ClickLoad()
{
    SetOptions();
    mStado = GST_GAME;
    mStack = 1; //Load From Map Start
}

void StateMenu::ClickSave()
{
    SetOptions();
    mStado = GST_GAME;
    mStack = 2; //Save To Map Start
}

void StateMenu::ClickOpcoes()
{
    if( dataWindow->IsLocallyVisible() ){
        dataWindow->Show(false);
    } else{
        dataWindow->Show(true);
    }
}

void StateMenu::SetOptions()
{

    MAP_WIDTH = spinMapX->GetValue();
    MAP_HEIGHT = spinMapY->GetValue();
    Procedural::ProceduralControl.n_Salas = spinRooms->GetValue();
    Procedural::ProceduralControl.max_width = spinRoomsSizeMax->GetValue();
    Procedural::ProceduralControl.min_width = spinRoomsSizeMin->GetValue();
    DataHolder::DataControl.mRun = spinRuns->GetValue();
    DataHolder::DataControl.mMaps = spinMaps->GetValue();

}
