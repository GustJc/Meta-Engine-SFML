#include "Tile.h"

Tile::Tile(int defaultType, int defaultGfx)
{
    //ctor
    gfx = defaultGfx;
    tipo = defaultType;
    itens.clear();
    obj = nullptr;
}

Tile::~Tile()
{
    //dtor
}
