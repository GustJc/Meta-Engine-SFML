#include "ConsoleInfo.h"

#include "MetaEngine.h"
#include "Defines.h"
#include "Player.h"
#include<iostream>

//token
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
ConsoleInfo ConsoleInfo::MessageControl;

ConsoleInfo::ConsoleInfo()
{
    //ctor
    mMsgIndex = 0;
    mLimitMsg = 3;
    mLimitMsgLog = 7;
    mConsoleOnline = false;
    mView.setSize(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
    mLogIndex = 0;
}

void ConsoleInfo::init()
{
    mText.setFont(MetaEngine::EngineControl.getFont());
    mText.setCharacterSize(12);


    setViewPortOnline();
    mText.setPosition(MetaEngine::EngineControl.getWindowReference()
                      .mapPixelToCoords(sf::Vector2i(5,11*7), mView));
    mString << "> ";
    mText.setString(mString.str());
    setViewPortOnline(false);
}


ConsoleInfo::~ConsoleInfo()
{
    //dtor
    mConsoleInfo.clear();
}

//------------------ Process Command -----------------------------------------------------------------------
void ConsoleInfo::processCommand()
{
    cout << mString.str() << endl;

    mConsoleLog.push_back(sf::Text(mString.str(), MetaEngine::EngineControl.getFont(), 12) );

    if(executeCommand(mString.str()) == false)
    {
        mConsoleLog.push_back(sf::Text(std::string("Comando nao encontrado."), MetaEngine::EngineControl.getFont(), 12));
    }

    mString.str(std::string());
    mString << "> ";
    mText.setString(mString.str());
    mLogIndex = mConsoleLog.size();
}

//------------------ Eventos -----------------------------------------------------------------------
void ConsoleInfo::events(const sf::Event& event)
{
    if(mConsoleOnline)
    {
        if(event.type == sf::Event::TextEntered)
        {
            //Se backspace
            if(event.text.unicode == 8 || event.text.unicode == 127)
            {
                int pos = mString.tellp();
                string str(mString.str() );
                int extra = str.length() - pos;

                if(event.text.unicode == 127 || str.length() - extra > 2)
                {
                    //se Delete
                    if(event.text.unicode == 8) { pos--;}
                    str.erase(pos,1);
                    mString.str(str);
                    mString.seekp(pos,ios::beg);
                    mText.setString(mString.str());
                }

            } else
            // unicode 13 é enter.
            if(event.text.unicode > 13 && event.text.unicode < 127 )
            {
                //Evita de aparecer o ; ao chamar console
                if( !(event.text.unicode == 59 && mString.str()[0] == '>') )
                {
                    int pos = mString.tellp();
                    //Se cursor não for ultimo, coloca no meio
                    if(pos != (int)mString.str().length())
                    {
                        string str(mString.str().substr(pos));
                        cout << str << endl;
                        mString << static_cast<char>(event.text.unicode);
                        mString << str;
                        mString.seekp(pos+1,ios::beg);
                    }
                    else
                    {
                        mString << static_cast<char>(event.text.unicode);
                    }
                    mText.setString(mString.str());
                }

            }
        }
    }
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {   //Seta mConsoleOnline = false
            setViewPortOnline(false);
            mString.str(std::string());
            mString << "> ";
            mText.setString(mString.str());
        } else
        if(mConsoleOnline && event.key.code == sf::Keyboard::Up)
        {   //Se console online e enter, envia comando para processamento
            setMessageFromLog(-1);
        } else
        if(mConsoleOnline && event.key.code == sf::Keyboard::Down)
        {   //Se console online e enter, envia comando para processamento
            setMessageFromLog(1);
        } else
        if(mConsoleOnline && event.key.code == sf::Keyboard::Return)
        {   //Se console online e enter, envia comando para processamento
            processCommand();
        }
        else
        if(event.key.code == sf::Keyboard::Left && mString.tellp() > 2)
        {
            mString.seekp(-1,ios::cur);
        } else
        if(event.key.code == sf::Keyboard::Right && mString.tellp() < (int)mString.str().length())
        {
            mString.seekp(1,ios::cur);
        }
    //Se eventos pausados, ignora teclas que não sejam console
        if(MetaEngine::EngineControl.isEventsPaused())
        {
            return;
        } else
        if(event.key.code == sf::Keyboard::Space)
        {
            nextPage();
        } else
        if(event.key.code == sf::Keyboard::SemiColon)
        {   //Seta mConsoleOnline = true
            setViewPortOnline(true);
        }
        else {
            clearMessages();
        }


    }

}

//------------------ Desenha -----------------------------------------------------------------------
void ConsoleInfo::draw()
{
    sf::RenderWindow& window = MetaEngine::EngineControl.getWindowReference();

// - - - - - - - - - - - - Console Online Draw - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    if(mConsoleOnline)
    {
        window.setView(mView);
        sf::Vector2f ppos = window.mapPixelToCoords(
                                    sf::Vector2i(0,0));
        MetaEngine::EngineControl.drawRectVertex(ppos.x, ppos.y, mView.getSize().x,
                                                 mView.getSize().y,sf::Color(120,120,120));


        for(int i = (int)(mConsoleLog.size()-1), n = 0; i >= 0; --i, ++n)
        {
            if(n >= (int)mLimitMsgLog)
            {
                sf::Vector2f pos = window.mapPixelToCoords(
                                    sf::Vector2i(5,5));
                MetaEngine::EngineControl.drawRectVertex(pos.x, pos.y,5,5,sf::Color::Blue);
                break;
            }
            mConsoleLog[i].setPosition(window.mapPixelToCoords(sf::Vector2i(5,66-11*n) ) );
            window.draw( mConsoleLog[i] );
        }

        window.draw(mText);

        //Imprime cursor
        string str = mString.str();
        int width = 5;
        unsigned int cursor = mString.tellp();
        for(unsigned int i = 0; i < str.length();++i)
        {
            if(i == cursor) break;
            width += MetaEngine::EngineControl.getFont().
                        getGlyph(str.at(i), mText.getCharacterSize(),false).advance;
        }
        sf::Vector2f pos = window.mapPixelToCoords(
                                    sf::Vector2i(width,90));
                MetaEngine::EngineControl.drawRectVertex(pos.x, pos.y,5,2,sf::Color::White);

        //Reseta view
        window.setView(MetaEngine::EngineControl.getViewGame());
        return;
    }
    if(mMsgIndex >= (int)mConsoleInfo.size())
    {
        return;
    }
// - - - - - - - - - - - - Console Offline Draw - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    window.setView(mView);
    for(unsigned int i = mMsgIndex, n = 0; i < mConsoleInfo.size(); ++i, ++n)
    {
        if(n >= mLimitMsg)
        {
            sf::Vector2f pos = window.mapPixelToCoords(
                                sf::Vector2i(5,10+n*18));
            MetaEngine::EngineControl.drawRectVertex(pos.x, pos.y,5,5,sf::Color::Blue);
            break;
        }
        mConsoleInfo[i].setPosition(window.mapPixelToCoords(sf::Vector2i(0,n*18) ) );
        //cout << "i: " << i << " mconsolesize: " << mConsoleInfo.size() << endl;
        window.draw( mConsoleInfo[i] );
    }
    window.setView(MetaEngine::EngineControl.getViewGame());
}

//------------------ Add Message -----------------------------------------------------------------------
void ConsoleInfo::addMessage(std::string msg)
{
    if(mConsoleInfo.size() >= MAX_CONSOLE_LOG)
    {
        mConsoleInfo.erase(mConsoleInfo.begin());
        mMsgIndex--;
    }
    mConsoleInfo.push_back(sf::Text(msg, MetaEngine::EngineControl.getFont(), 12));
}

//------------------ Next Page -----------------------------------------------------------------------
void ConsoleInfo::nextPage()
{
    if(mMsgIndex < (int)mConsoleInfo.size()){
        mMsgIndex += mLimitMsg;
        if(mMsgIndex > (int)mConsoleInfo.size())
        {
            mMsgIndex = mConsoleInfo.size();
        }
    }
}

//------------------ Clear Message -----------------------------------------------------------------------
void ConsoleInfo::clearMessages()
{
    mMsgIndex = mConsoleInfo.size();
}
//------------------ Viewpor Online -----------------------------------------------------------------------
void ConsoleInfo::setViewPortOnline(bool on)
{
    mReturn = false;
    if(on)
    {
        mView.setViewport(sf::FloatRect(0,0,1,0.2f));
        mView.setSize(WINDOW_WIDTH,WINDOW_HEIGHT/5);
        MetaEngine::EngineControl.getViewGame().setViewport(sf::FloatRect(0,0.2f,1,1));
        mConsoleOnline = true;
        MetaEngine::EngineControl.setEventsPaused();
        MetaEngine::EngineControl.getWindowReference().setKeyRepeatEnabled(true);
    } else
    {
        mView.setViewport(sf::FloatRect(0,0,1,1));
        mView.setSize(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
        MetaEngine::EngineControl.getViewGame().setViewport(sf::FloatRect(0,0,1,1));
        mConsoleOnline = false;
        MetaEngine::EngineControl.setEventsPaused(false);
        MetaEngine::EngineControl.getWindowReference().setKeyRepeatEnabled(false);
    }
}
//------------------ Execute Command -----------------------------------------------------------------------
bool ConsoleInfo::executeCommand(std::string str)
{


    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string s;
    while (std::getline(iss, s, ' ')) {
        tokens.push_back(s);
    }

    if(tokens.size() <= 1) return false;

        cout << "Cmd: " << tokens[1] << endl;
        if(tokens[1].compare("setFog") == 0)
        {
            if(tokens.size() <= 2)
            {
                mConsoleLog.push_back(sf::Text(std::string("Uso invalido, setFog boolean"), MetaEngine::EngineControl.getFont(), 12));
            } else{
                std::transform(tokens[2].begin(), tokens[2].end(), tokens[2].begin(), ::tolower);
                std::istringstream is(tokens[2]);
                bool b;
                is >> std::boolalpha >> b;

                cout << "Valor: " << (b?"True":"False") << endl;
                MetaEngine::EngineControl.setMapFog(b);
            }
            return true;
        }
        if(tokens[1].compare("enableBot") == 0)
        {
            Player::PlayerControl->isBot = true;
            return true;
        }
        else
        if(tokens[1].compare("disableBot") == 0)
        {
            Player::PlayerControl->isBot = false;
            return true;
        }
        else
        if(tokens[1].compare("exit") == 0 || tokens[1].compare("quit") == 0)
        {
            exit(0);
        } else
        if(tokens[1].compare("return") == 0 || tokens[1].compare("menu") == 0)
        {
            mReturn = true;
            return true;
        } else
        if(tokens[1].compare("botDelay") == 0 || tokens[1].compare("setBotDelay") == 0)
        {
            if(tokens.size() <= 2)
            {
                mConsoleLog.push_back(sf::Text(std::string("Uso invalido, setBotDelay int"), MetaEngine::EngineControl.getFont(), 12));
            } else
            {
                std::istringstream is(tokens[2]);
                int b;
                is >> b;
                Player::PlayerControl->mBotDelay = b;
            }
            return true;
        }

    return false;
}

//------------------ Set Message From Log -----------------------------------------------------------------------
void ConsoleInfo::setMessageFromLog(int add)
{
    bool isCmd = false;
    while(isCmd == false)
    {
        if(mLogIndex+add >= (int)mConsoleLog.size() || mLogIndex+add < 0) {
            return;
        }

        mLogIndex += add;
        if(mConsoleLog[mLogIndex].getString()[0] == '>'){
            break;
        }

    }

    mString.str(mConsoleLog[mLogIndex].getString());
    mString.seekp(mString.str().length(),ios::beg);
    mText.setString(mString.str());


}

bool ConsoleInfo::isConsoleOnline()
{
    return mConsoleOnline;
}

bool ConsoleInfo::isReturn()
{
    return mReturn;
}
