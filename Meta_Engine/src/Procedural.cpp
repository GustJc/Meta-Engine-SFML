#include "Procedural.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
Procedural::Procedural()
{
    //ctor
    srand(time(0));
    n_Salas = 8;
    min_width = 1;
    max_width = 3;

    vida_min = 5;
    vida_max = 30;
    chance_spawn = 500;
    total_life = 5000;
}

Procedural::~Procedural()
{
    //dtor
}

void Procedural::makeMap(Map& mMap)
{
    std::vector<Sala> mSalas;
    for(int i = 0; i < n_Salas; ++i)
    {
        Sala s;
        s.x = (int)(rand() % 40);
        s.y = (int)(rand() % 30);
        mSalas.push_back(s);
    }
    //Liga salas
    for(int i = 0; i < n_Salas-1;++i)
    {
        //origem
        int n_x = mSalas[i].x;
        int n_y = mSalas[i].y;
        //destino
        int d_x = mSalas[i+1].x;
        int d_y = mSalas[i+1].y;
        //Cria caminho em X
        while(n_x != d_x)
        {
            if(n_x < d_x)
            {
                ++n_x;
            } else
            if(n_x > d_x)
            {
                --n_x;
            }
            if(n_x < 0 || n_x >= 40){
                break;
            }
            mMap.setTile(n_x,n_y,0,1);
        }
        //Cria caminho em Y
        while(n_y != d_y)
        {
            if(n_y < d_y)
            {
                ++n_y;
            } else
            if(n_y > d_y)
            {
                --n_y;
            }
            if(n_y < 0 || n_y >= 30){
                break;
            }
            mMap.setTile(n_x,n_y,0,1);
        }


    } //Fim ligar salas
    for(int i = 0; i < n_Salas;++i)
    {
        //Enlarga salas
        int left_w = min_width + (int)(rand() % max_width);
        int right_w = min_width + (int)(rand() % max_width);
        int up_w = min_width + (int)(rand() % max_width);
        int bottom_w = min_width + (int)(rand() % max_width);

        for(int ix = 0, startX = mSalas[i].x-left_w;
                ix < (left_w+right_w+1); ++ix)
        {
            if(startX+ix < 0){
                continue;
            }else if(startX+ix >= 40){
                break;
            }
            for(int iy = 0, startY = mSalas[i].y-up_w;
                    iy < (up_w+bottom_w+1); ++iy)
            {
                if(startY+iy < 0){
                    continue;
                } else if(startY+iy >= 30){
                    break;
                }
                mMap.setTile(startX+ix, startY+iy,0,3);
            }
        }
    }

    //Pinta centro de ponto das salas
    for(unsigned int i = 0; i < mSalas.size();++i)
    {
        mMap.setTile(mSalas[i].x, mSalas[i].y, 0, 2);
    }

}

void Procedural::makeMapMiner(Map& mMap)
{
    std::vector<Miner> mMiner;
    for(int i = 0; i < n_Salas; ++i)
    {
        Miner s;
        s.x = (int)(rand() % 40);
        s.y = (int)(rand() % 30);
        s.life = vida_min + (int)(rand() % (vida_max+1));
        mMiner.push_back(s);
        mMap.setTile(mMiner[i].x, mMiner[i].y, 1, 2);
    }
    int dead = 0;
    int life = total_life;
    //time step
    while(dead != (int)mMiner.size() && life > 0)
    {
        life--;
        dead = 0;
        for(int i = 0; i < (int)mMiner.size(); ++i)
        {
            if(mMiner[i].dead){
                dead++;
                continue;
            }
            mMiner[i].life -= 1;
            if(mMiner[i].life <= 0) {
                mMiner[i].dead = true;
            }

            //Cava
            int m_x = mMiner[i].x;
            int m_y = mMiner[i].y;

            int randpos = (int)(rand() % 4);
            switch(randpos)
            {
            case 0:
                if(mMap.getTile(m_x-1,m_y).id == 0){
                    mMap.setTile(m_x-1,m_y,1,3);
                    mMiner[i].x -= 1;
                }
                break;
            case 1:
                if(mMap.getTile(m_x+1,m_y).id == 0){
                    mMap.setTile(m_x+1,m_y,1,3);
                    mMiner[i].x += 1;
                }
                break;
            case 2:
                if(mMap.getTile(m_x,m_y-1).id == 0){
                    mMap.setTile(m_x,m_y-1,1,3);
                    mMiner[i].y -= 1;
                }
                break;
            case 3:
                if(mMap.getTile(m_x,m_y+1).id == 0){
                    mMap.setTile(m_x,m_y+1,1,3);
                    mMiner[i].y += 1;
                }
                break;
            default:
                mMiner[i].dead = true;
            }

            //Chance de criar miner
            double chance = (double)(rand() % 10000);
            if(chance < chance_spawn) //5%
            {
                cout << "CHANCE SPAWN!" << endl;
                Miner m;
                m.x = mMiner[i].x;
                m.y = mMiner[i].y;
                m.life = vida_min + (int)(rand() % (vida_max+1));
                mMiner.push_back(m);
                mMap.setTile(m.x, m.y, 1, 1);
            }
        } //fim iterar vida
    } //fim loop
    if(life < 0){
        cout << "Acabou por tempo." << endl;
    }

}

