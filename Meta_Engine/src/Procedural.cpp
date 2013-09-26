#include "Procedural.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Defines.h"
#include "Player.h"
#include "Entity.h"
using namespace std;
Procedural::Procedural()
{
    //ctor
    srand(time(0));
    n_Salas = 8;
    min_width = 3;
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
        s.x = (int)(rand() % MAP_WIDTH);
        s.y = (int)(rand() % MAP_HEIGHT);
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
            if(n_x < 0 || n_x >= MAP_WIDTH){
                break;
            }
            mMap.setTile(n_x,n_y,TILE_FLOOR,1);
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
            if(n_y < 0 || n_y >= MAP_HEIGHT){
                break;
            }
            mMap.setTile(n_x,n_y,TILE_FLOOR,1);
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
            }else if(startX+ix >= MAP_WIDTH){
                break;
            }
            for(int iy = 0, startY = mSalas[i].y-up_w;
                    iy < (up_w+bottom_w+1); ++iy)
            {
                if(startY+iy < 0){
                    continue;
                } else if(startY+iy >= MAP_HEIGHT){
                    break;
                }
                mMap.setTile(startX+ix, startY+iy,TILE_FLOOR,3);
            }
        }
    }

    //Pinta centro de ponto das salas
    for(unsigned int i = 0; i < mSalas.size();++i)
    {
        if(i == mSalas.size()-1)
        {
            mMap.setTile(mSalas[i].x, mSalas[i].y, TILE_FLOOR, 4);
            mMap.getTile(mSalas[i].x, mSalas[i].y)->id = TILE_FINISH_LV;
        } else
        {
            mMap.setTile(mSalas[i].x, mSalas[i].y, TILE_FLOOR, 2);
        }

    }

    Player::PlayerControl.setPosition(mSalas[0].x, mSalas[0].y);

}

void Procedural::makeMapMiner(Map& mMap)
{
    std::vector<Miner> mMiner;
    for(int i = 0; i < n_Salas; ++i)
    {
        Miner s;
        s.x = (int)(rand() % MAP_WIDTH);
        s.y = (int)(rand() % MAP_HEIGHT);
        s.life = vida_min + (int)(rand() % (vida_max+1));
        mMiner.push_back(s);
        mMap.setTile(mMiner[i].x, mMiner[i].y, TILE_FLOOR, 2);
    }
    int dead = 0;
    int life = total_life;
    int spawn = 0;
    //time step
    while(dead != (int)mMiner.size() && life > 0)
    {
        dead = 0;
        for(int i = 0; i < (int)mMiner.size(); ++i)
        {
            if(mMiner[i].dead){

                mMiner.erase(mMiner.begin()+i);
                //cout << "Deletado\n";
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

            Tile* tile = mMap.getTile(m_x, m_y);
            bool positions_tested[4] = {false, false, false, false};
            bool checking_pos = true;
            while(checking_pos)
            {
                int randpos = (int)(rand() % 4);
                switch(randpos)
                {
                case 0:
                    m_x += 1;
                    positions_tested[0] = true;
                    break;
                case 1:
                    m_x -= 1;
                    positions_tested[1] = true;
                    break;
                case 2:
                    m_y += 1;
                    positions_tested[2] = true;
                    break;
                case 3:
                    m_y -= 1;
                    positions_tested[3] = true;
                    break;
                default:
                    mMiner[i].dead = true;
                }
                int count = 0;
                for(int z = 0; z < 4; ++z){
                    if(positions_tested[z] == true){
                        count++;
                    }
                }
                if(count >= 4) {
                    checking_pos = false;
                }
                tile = mMap.getTile(m_x, m_y);
                //Se for solido, pode cavar
                if(tile != nullptr && tile->id == TILE_SOLID) {
                    checking_pos = false;
                }

            }

            if(tile != nullptr && tile->id == TILE_SOLID){
                mMap.setTile(m_x,m_y,TILE_FLOOR,3);
                life--;
                mMiner[i].x = m_x;
                mMiner[i].y = m_y;
            } else
            {
                mMiner.erase(mMiner.begin()+i);
            }

            //Chance de criar miner
            double chance = (double)(rand() % 10000);
            if(chance < chance_spawn) //5%
            {
                spawn++;
                Miner m;
                m.x = mMiner[i].x;
                m.y = mMiner[i].y;
                m.life = vida_min + (int)(rand() % (vida_max+1));
                mMiner.push_back(m);
                mMap.setTile(m.x, m.y, TILE_FLOOR, 1);
            }
        } //fim iterar vida
    } //fim loop
    if(life < 0){
        cout << "Acabou por tempo." << endl;
    }
    cout << "Miner criados: " << spawn << endl;

}
