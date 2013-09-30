#include "Map.h"
#include "MetaEngine.h"
#include "Defines.h"
#include "Player.h"
#include <iostream>
using namespace std;
Map Map::MapControl;
Map::Map()
{
    //ctor

    int a = 0;
    setFlag(a, EX_SEEN);
    a = 0;

    if(isFlag(a, EX_HAS_SEEN | EX_SEEN) )
        cout << "isSEEN!\n";

    removeFlag(a, EX_SEEN);

    if(isFlag(a, EX_SEEN) )
        cout << "SEEN AGAIN\n";
    if(isFlag(a, EX_HAS_SEEN) )
        cout << "SEEN NO AGAIN\n";
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
    exploreMap.clear();
    tileMap.resize(sizeW);
    exploreMap.resize(sizeW);

    for(int i = 0; i < sizeW; ++i)
    {
        tileMap[i].resize(sizeH);
    }
    for(int i = 0; i < sizeW; ++i)
    {
        exploreMap[i].resize(sizeH, 0);
    }

    //std::cout << tileMap.size() << "-" << tileMap[0].size() << std::endl;

}

void Map::draw()
{
    for(unsigned int i = 0; i < tileMap.size(); ++i)
    {
        for(unsigned int j = 0; j < tileMap[i].size();++j)
        {
            if(MetaEngine::EngineControl.isMapFog() &&
                   !has_seens(i,j)) continue;

            Tile& tile = tileMap[i][j];

            if(mSprite.getTexture() == nullptr)
            {
                //Se player não ve, no renderiza.
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
                else if(tile.color == 4){
                    MetaEngine::EngineControl.drawRectVertex(i*TILE_SIZE,j*TILE_SIZE,
                                               TILE_SIZE,TILE_SIZE,sf::Color::Magenta);
                }
            } // Fim sem sprite
            else
            {
                int tileImg = tile.color;
                if(tileImg == 0) continue;
                mSprite.setPosition(i*TILE_SIZE, j*TILE_SIZE);
                mSprite.setTextureRect(sf::IntRect(tileImg*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
                MetaEngine::EngineControl.getWindowReference().draw(mSprite);
            }
        } // fim for
    } //fim for
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
    if(tileID >=0){
        tileMap[x][y].id = tileID;
    }
    tileMap[x][y].color = tileColor;
}

Tile* Map::getTile(int x, int y)
{
    if(x < 0 || y < 0 || x >= (int)tileMap.size() || y >= (int)tileMap[0].size()){
        return nullptr;
    }
    return &tileMap[x][y];
}


int Map::getMapWidth()
{
    return tileMap.size();
}

int Map::getMapHeight()
{

    return tileMap[0].size();
}

void Map::setSprite(sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

GameObject* Map::getObj(int x, int y, int index)
{
    if (x < 0 || y < 0) return nullptr;
    if (x >= getMapWidth() || y >= getMapHeight() ) return nullptr;

    if(tileMap[x][y].obj.empty() || index >= (int)tileMap[x][y].obj.size() || index < 0) return nullptr;

    return tileMap[x][y].obj[index];
}




bool Map::isFlag(int& flags, int f){
    return ((flags & f) == f);
}
void Map::setFlag(int& flags, int f){
    flags |= f;
}
void Map::removeFlag(int& flags, int f){
    flags = flags & ~f;
}




//Lua maps
bool Map::has_seens(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return false;
    if(y < 0 || y > (int)tileMap[0].size()) return false;

    return isFlag(exploreMap[x][y], EX_SEEN);
}

bool Map::has_remembers(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return false;
    if(y < 0 || y > (int)tileMap[0].size()) return false;

    return (isFlag(exploreMap[x][y], EX_HAS_SEEN) );
}

bool Map::has_passed(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return false;
    if(y < 0 || y > (int)tileMap[0].size()) return false;

    return isFlag(exploreMap[x][y], EX_PASSED) ;
}


void Map::setSeen(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return;
    if(y < 0 || y > (int)tileMap[0].size()) return;

    setFlag(exploreMap[x][y], EX_SEEN);
}

void Map::setRemember(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return;
    if(y < 0 || y > (int)tileMap[0].size()) return;

    setFlag(exploreMap[x][y], EX_HAS_SEEN);
}

void Map::setPassed(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return;
    if(y < 0 || y > (int)tileMap[0].size()) return;

    setFlag(exploreMap[x][y], EX_PASSED);
}

void Map::setVisible(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return;
    if(y < 0 || y > (int)tileMap[0].size()) return;

    setFlag(exploreMap[x][y], EX_FOV);
}

void Map::setNotVisible(int x, int y)
{
    if(x < 0 || x > (int)tileMap.size()) return;
    if(y < 0 || y > (int)tileMap[0].size()) return;

    removeFlag(exploreMap[x][y], EX_FOV);
}

void Map::forceRemoveMapFlag(int x, int y, int flag)
{
    removeFlag(exploreMap[x][y],flag);
}


void Map::mapseen()
{

}

void Map::mapfov()
{

}

void Map::forceShowMap()
{
    MetaEngine::EngineControl.setMapFog(false);
    MetaEngine::EngineControl.getWindowReference().clear();
    sf::View& view = MetaEngine::EngineControl.getViewGame();
    view.setCenter(Player::PlayerControl->getPosition().x*TILE_SIZE-TILE_SIZE/4, Player::PlayerControl->getPosition().y*TILE_SIZE-TILE_SIZE/4);
    MetaEngine::EngineControl.getWindowReference().setView(view);

    draw();
    Player::PlayerControl->draw();

    MetaEngine::EngineControl.getWindowReference().display();
}


