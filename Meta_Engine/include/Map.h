#pragma once
#include <vector>
#include <Tile.h>
class Map
{
    public:
        Map();
        virtual ~Map();

        void draw();

        void createMap(int sizeW, int sizeH);
        void setTile(int x, int y, int tileID, int tileColor);
        Tile& getTile(int x, int y);

    private:
        std::vector<std::vector<Tile> > tileMap;

};
