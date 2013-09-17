#pragma once

enum {
    TILE_SOLID,
    TILE_FLOOR
};
enum {
    TILE_OBJ_ENTITY,
    TILE_OBJ_ITEM,
    TILE_OBJ_CHEST
};
class Tile
{
    public:
        Tile();
        virtual ~Tile();

        int id;
        int obj;
        int color;
    protected:
    private:
};
