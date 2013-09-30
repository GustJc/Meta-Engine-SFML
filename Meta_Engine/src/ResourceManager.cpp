#include "ResourceManager.h"

#include "Map.h"

#include <iostream>
ResourceManager ResourceManager::ResourceControl;
ResourceManager::ResourceManager()
{
    //ctor
}

ResourceManager::~ResourceManager()
{
    //dtor
}

Item* ResourceManager::createItem(std::string nome)
{

    auto inserted = mItemMap.insert(std::make_pair(nome, Item() ));

    assert(inserted.second);

    return getItem(nome);
}

Item* ResourceManager::getItem(std::string nome)
{
    auto found = mItemMap.find(nome);

    if(found == mItemMap.end() ){
        std::cout << "Not found item: " << nome << std::endl;
    }
    assert(found != mItemMap.end());

    return &found->second;
}

Entity* ResourceManager::getEntity(std::string nome)
{
    auto found = mEntityMap.find(nome);
    if(found == mEntityMap.end()){
        std::cout << "Not found Entity: " << nome << std::endl;
    }
    assert(found != mEntityMap.end());

    return &found->second;
}


Entity* ResourceManager::createEntity(std::string nome)
{

    auto inserted = mEntityMap.insert(std::make_pair(nome, Entity() ));

    assert(inserted.second);

    return getEntity(nome);
}

//-----------------------------------------------------------------------
void ResourceManager::addItem(int mapX, int mapY, std::string ID)
{
    Item* item = new Item( *ResourceManager::ResourceControl.getItem(ID) );
    item->addToObjectList();
    item->setPosition(mapX, mapY);
}

void ResourceManager::addEntity(int mapX, int mapY, std::string ID)
{
    Entity* ent = new Entity( *ResourceManager::ResourceControl.getEntity(ID) );
    ent->addToObjectList();
    ent->setPosition(mapX, mapY);
}

void ResourceManager::addGold(int mapX, int mapY, int gold)
{
    int goldSize = gold/5;
    if(goldSize > 5) goldSize = 5;

    if(goldSize != 0){
        goldSize = gold/(5*goldSize);
    }
    if(goldSize > 5) {
        goldSize = 5;
    }

    Item* item = new Item(gold, goldSize,0);
    item->addToObjectList();
    item->setPosition(mapX, mapY);
}

std::string ResourceManager::addEntityByIndex(int mapX, int mapY, int ID)
{
    int i = 0;
    for (auto &any : mEntityMap ) {
        Entity* ent = &any.second;

        if(!ent) return "not found";
        if(i == ID)
        {
            Entity* n_ent = new Entity( *ent );
            n_ent->addToObjectList();
            n_ent->setPosition(mapX, mapY);
            return any.first;
        }
        i++;
    }
    return "not found";
}

std::string ResourceManager::addItemByIndex(int mapX, int mapY, int ID)
{
    int i = 0;
    for (auto &any : mItemMap ) {
        Item* item = &any.second;

        if(!item) return "not found";
        if(i == ID)
        {
            Item* n_item = new Item( *item );
            n_item->addToObjectList();
            n_item->setPosition(mapX, mapY);
            return any.first;
        }
        i++;
    }
    return "not found";
}

