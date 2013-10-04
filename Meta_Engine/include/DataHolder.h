#pragma once

#include <vector>
typedef struct mapData
{
    int steps       = 0;
    int itens_get   = 0;
    int enemys_KO   = 0;
    bool win        = false;
}_mapData;

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
    protected:


        std::vector<mapData> mRunDataList;
    private:
};
