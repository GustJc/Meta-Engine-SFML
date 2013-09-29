#pragma once

#include "State.h"

class GameManager
{
    private:
        State* mEstadoAtual;
        int stack;
    public:
        GameManager();
        virtual ~GameManager();

        int run(int argc, char* args[]);
        void executeTests();
};

