#pragma once
#include <vector>
#include <Tile.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum {
        EX_SEEN     =     0x0001,
        EX_PASSED   =     0x0002,
        EX_HAS_SEEN =     0x0004,
        EX_FOV      =     0x0008,
        EX_PLACE3   =     0x0010,
        EX_PLACE4   =     0x0020,
        EX_PLACE5   =     0x0040,
        EX_PLACE6   =     0x0080,
        EX_PLACE7   =     0x0100
};

class Map
{
    public:
        Map();
        virtual ~Map();

        static Map MapControl;

        void draw();

        void createMap(int sizeW, int sizeH, int defaultType = 0, int defaultGfx = -1);
        bool loadMap(std::string filename);
        void saveMap(std::string filename = "output_map.map");
        void clearMap();
        void setTile(int x, int y, int tileGfx, int tileColor);
        Tile* getTile(int x, int y);

        void setSprite(sf::Texture& texture);

        int getMapWidth();
        int getMapHeight();

        GameObject* getObj(int x, int y);
        GameObject* getItem(int x, int y, int index);
        GameObject* getIfObj(int x, int y, int typeObj);

        //Lua

        void forceShowMap();

        bool has_seens(int x, int y);
        bool has_remembers(int x, int y);
        bool has_passed(int x, int y);

        void setSeen(int x, int y);
        void setRemember(int x, int y);
        void setPassed(int x, int y);
        void setVisible(int x, int y);
        void setNotVisible(int x, int y);
        void remove_seens(int x, int y);

        void forceRemoveMapFlag(int x, int y, int flag);

        void mapseen();
        void mapfov();

    private:
        sf::Sprite mSprite;
        std::vector<std::vector<Tile> > tileMap;
        std::vector<std::vector<int> > exploreMap;

        bool isFlag(int& flags, int f);
        void setFlag(int& flags, int f);
        void removeFlag(int& flags, int f);

};
