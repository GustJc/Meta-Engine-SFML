#pragma once
#include <vector>
class GameObject;
enum {
    TILE_NONE = -1,
    TILE_SOLID,
    TILE_FLOOR,
    TILE_FINISH_LV
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
        std::vector<GameObject*> obj;
        int color;
    protected:
    private:
};
