#include "DataHolder.h"
#include <iostream>
#include <math.h>
using namespace std;
mapData DataHolder::RunData;
DataHolder DataHolder::DataControl;
DataHolder::DataHolder()
{
    //ctor
    mRun = 5;
    mMaps = 1;
    resetCount();
}

DataHolder::~DataHolder()
{
    //dtor
}

void DataHolder::resetCount()
{
    mRunCount = mMapsCount = 0;
}


void DataHolder::clearData()
{
    mRunDataList.clear();
}

void DataHolder::addData(mapData data)
{
    mRunDataList.push_back(data);

    RunData = mapData();
}

void DataHolder::analyseData()
{
    mapData totalData;
    int totalWins = 0;

    for(unsigned int i = 0; i < mRunDataList.size() ; ++i)
    {
        cout << "Run["        << i+1 << "]: Steps: " << mRunDataList[i].steps
            << " Enemy K.O: " << mRunDataList[i].enemys_KO
            << " Itens get: " << mRunDataList[i].itens_get
            << " Win? "       << mRunDataList[i].win << endl;
        totalData.steps += mRunDataList[i].steps;
        totalData.enemys_KO += mRunDataList[i].enemys_KO;
        totalData.itens_get += mRunDataList[i].itens_get;
        if(mRunDataList[i].win){
            totalWins++;
        }

    } //End get data

    float meanSteps = (float)totalData.steps / (float)mRunDataList.size();
    float meanKO = (float)totalData.enemys_KO / (float)mRunDataList.size();
    float meanItem = (float)totalData.itens_get / (float)mRunDataList.size();
    float meanVictories = (float)totalWins / (float)mRunDataList.size();

    float varSteps = 0;
    float varKO = 0;
    float varItem = 0;

    float dpSteps = 0;
    float dpKO = 0;
    float dpItem = 0;
    if(mRunDataList.size() > 1)
    {
        for(unsigned int i = 0; i < mRunDataList.size(); ++i)
        {
            varSteps += pow(mRunDataList[i].steps-meanSteps,2);
            varKO += pow(mRunDataList[i].enemys_KO-meanKO,2);
            varItem += pow(mRunDataList[i].itens_get-meanItem,2);
        }

        dpSteps = sqrt(varSteps/(float)(mRunDataList.size()-1));
        dpKO = sqrt(varKO/(float)(mRunDataList.size()-1));
        dpItem = sqrt(varItem/(float)(mRunDataList.size()-1));

        varSteps = varSteps/(float)(mRunDataList.size());
        varKO = varKO/(float)(mRunDataList.size());
        varItem = varItem/(float)(mRunDataList.size());

    }
    cout << "======== TOTAL DATA =======" << endl;
    //std::cout.unsetf ( std::ios::floatfield );
    std::cout.precision(3);
    cout <<    "Mean Steps    : " << meanSteps  << " \tVariance(pop): " << varSteps  << " \tDeviation(amt): " << dpSteps << endl
            << "Mean Enemy K.O: " << meanKO     << " \tVariance(pop): " << varKO     << " \tDeviation(amt): " << dpKO << endl
            << "Mean Itens get: " << meanItem   << " \tVariance(pop): " << varItem   << " \tDeviation(amt): " << dpItem << endl
            << "Mean Victories: " << meanVictories << endl;
}
