#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

#include "Item.h"
#include "Entity.h"

class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();

        static ResourceManager ResourceControl;

        Item* createItem(std::string nome);
        Item* getItem(std::string nome);
        Item* getItemByIndex(int ID);
        Entity* createEntity(std::string nome);
        Entity* getEntity(std::string nome);
        Entity* getEntityByIndex(int ID);

        void addItem(int mapX, int mapY, std::string ID);
        void addEntity(int mapX, int mapY, std::string ID);
        void addGold(int mapX, int mapY, int gold);

        std::string addEntityByIndex(int mapX, int mapY, int ID);
        std::string addItemByIndex(int mapX, int mapY, int ID);

        void addCustomEntity(int mapX, int mapY, Entity* ent);
        void clearEntityMap();
        void clearItemMap();
    protected:

        std::map< std::string, Item>      mItemMap;
        std::map< std::string, Entity>    mEntityMap;
    private:
};
