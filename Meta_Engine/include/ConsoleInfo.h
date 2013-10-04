#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <string>
#include <sstream>

#define MAX_CONSOLE_LOG 150
class ConsoleInfo
{
    public:
        static ConsoleInfo MessageControl;

        ConsoleInfo();
        virtual ~ConsoleInfo();
        void init();

        void draw();
        void events(const sf::Event& event);
        void addMessage(std::string msg);
        //Imprime proximas mensagens
        void nextPage();
        void clearMessages();

        bool isConsoleOnline();
        bool isReturn();

        void setViewPortOnline(bool on = true);
    protected:
        void processCommand();
        bool executeCommand(std::string str);
        void setMessageFromLog(int add);

        std::stringstream       mString;
        sf::Text                mText;
        sf::View                mView;
        //Index da mensagem atual, mensagens antigas permanecem para log
        int                     mMsgIndex; //não é console
        //Index de pegar logs, Setas UP/DOWN
        int                     mLogIndex;
        //Quantidade maxima de mensagens na tela
        unsigned int            mLimitMsg;
        unsigned int            mLimitMsgLog;
        bool                    mConsoleOnline;
        bool                    mReturn;
        //Info, mensagens alertas sobre o jogo
        std::vector<sf::Text>   mConsoleInfo;
        //Console log, log de mensagens do console.
        std::vector<sf::Text>   mConsoleLog;
    private:
};
