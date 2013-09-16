#include "Map.h"
#include "MetaEngine.h"
#include "Defines.h"
#include <iostream>
Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
    tileMap.clear();
}

void Map::createMap(int sizeW, int sizeH)
{
    assert(tileMap.empty());

    tileMap.clear();
    tileMap.resize(sizeW);

    for(int i = 0; i < sizeW; ++i)
    {
        tileMap[i].resize(sizeH);
    }
    //std::cout << tileMap.size() << "-" << tileMap[0].size() << std::endl;

}

void Map::draw()
{
    for(unsigned int i = 0; i < tileMap.size(); ++i)
    {
        for(unsigned int j = 0; j < tileMap[i].size();++j)
        {
            Tile& tile = tileMap[i][j];
            if(tile.color == 0) {
                MetaEngine::EngineControl.drawRectVertex(i*TILE_SIZE,j*TILE_SIZE,
                                           TILE_SIZE,TILE_SIZE,
                                           sf::Color::Black);
            } else if(tile.color == 1){
                MetaEngine::EngineControl.drawRectVertex(i*TILE_SIZE,j*TILE_SIZE,
                                           TILE_SIZE,TILE_SIZE,sf::Color::White);
            } else if(tile.color == 2){
                MetaEngine::EngineControl.drawRectVertex(i*TILE_SIZE,j*TILE_SIZE,
                                           TILE_SIZE,TILE_SIZE,sf::Color::Yellow);
            }else if(tile.color == 3){
                MetaEngine::EngineControl.drawRectVertex(i*TILE_SIZE,j*TILE_SIZE,
                                           TILE_SIZE,TILE_SIZE,sf::Color::Blue);
            }
        }
    }
}


void Map::setTile(int x, int y, int tileID, int tileColor)
{
    if(tileMap.empty())
    {
        std::cout << "Map not created\n";
    }
    if(x >= (int) tileMap.size() || y >= (int) tileMap[0].size() || x < 0 || y < 0)
    {
        //std::cout << "Out of boundaries: " << x << "," << y << " max: " << (tileMap.size()-1) << "," <<
          //  (tileMap[0].size()-1) << std::endl;
        return;
    }

    tileMap[x][y].id = tileID;
    tileMap[x][y].color = tileColor;
}

Tile& Map::getTile(int x, int y)
{
    if(x < 0 || y < 0 || x >= (int)tileMap.size() || y >= (int)tileMap[0].size()){
        //std::cout << "Tile invalido, retornando primeiro tile...\n";
        return tileMap[0][0];
    }
    return tileMap[x][y];
}

