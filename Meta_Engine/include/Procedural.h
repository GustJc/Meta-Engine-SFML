#pragma once
#include "Map.h"
#include <string>
class Procedural
{
    public:
        Procedural();
        virtual ~Procedural();

        std::string currentMap;

        static Procedural ProceduralControl;

        void makeMap(Map& mMap);
        void makeMapMiner(Map& mMap);

        int mapType;

        int n_Salas;
        int tamanho;
        int min_width;
        int max_width;

        //miner
        int vida_min;
        int vida_max;
        int chance_spawn;
        int total_life;
        bool isChance(float chance);
    protected:
        struct Sala
        {
            int x, y;
        };
        struct Miner
        {
            int x, y;
            unsigned int life;
            bool dead;
        };
    private:
};
