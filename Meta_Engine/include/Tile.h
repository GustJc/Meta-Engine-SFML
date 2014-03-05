#pragma once
#include <vector>
class GameObject;
enum {
    TILE_NONE = -1,
    TILE_SOLID = 0,
    TILE_FLOOR = 1,
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
        Tile(int defaultType = TILE_SOLID, int defaultGfx = -1);
        virtual ~Tile();

        int gfx;
        std::vector<GameObject*> itens;
        GameObject* obj;
        int tipo;
    protected:
    private:
};
