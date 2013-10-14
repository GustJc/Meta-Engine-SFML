#pragma once

#include <vector>
typedef struct mapData
{
    int steps       = 0;
    int itens_get   = 0;
    int enemys_KO   = 0;
    bool win        = false;
}_mapData;


enum {
        GAME_START=0, GAME_LOAD=1, GAME_SAVE=2, GAME_RESET_LOAD=3, GAME_RESET_START=4
};

class DataHolder
{
    public:
        DataHolder();
        virtual ~DataHolder();
        static mapData RunData;
        static DataHolder DataControl;

        //Zera RunData
        void addData(mapData data = RunData);
        void clearData();
        void analyseData();

        void resetCount();

        //Dados
        int mRun;
        int mMaps;
        int mRunCount;
        int mMapsCount;
    protected:


        std::vector<mapData> mRunDataList;
    private:
};
