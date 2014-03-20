#include "LuaManager.h"

#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>

#include <iostream>

using namespace std;

#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "ResourceManager.h"

LuaManager LuaManager::LuaControl;


//Compactability function, should do nothing
static int lua_sleep(lua_State *L)
{
    //int m = static_cast<int> (luaL_checknumber(L,1));

    //sf::Time t = sf::milliseconds(m);
    //sf::sleep(t);

    return 0;
}

// ------------ Start Lua --------------------
void LuaManager::startLua()
{
    L = luaL_newstate();
	luaL_openlibs(L);
	luabind::open(L);

    luabind::module(L) [
        bindClasses()
	];

	luabind::globals(L)["map"] =
        &Map::MapControl;

    luabind::globals(L)["player"] =
        Player::PlayerControl;

    luabind::globals(L)["res"] =
        &ResourceManager::ResourceControl;

    lua_pushcfunction(L, lua_sleep);
    lua_setglobal(L, "sleep");

    //executeTests();

    doFile("./data/scripts/itens.lua");
    doFile("./data/scripts/entitys.lua");
//luabind::call_function<int>(myLuaState, "testadd", 2, 3);
//function
}

luabind::scope LuaManager::bindClasses()
{
    return
    luabind::class_<Map>("Map")
        .def( luabind::constructor<>( ) )
	   .property("h", &Map::getMapHeight)
	   .property("w", &Map::getMapWidth)
	   .def("forceShowMap", &Map::forceShowMap)
	   .def("getIfObj", &Map::getIfObj)
	   .def("getObj", &Map::getObj)
	   .def("getItem", &Map::getItem)
	   .def("getTile", &Map::getTile)
	   .def("setTile", &Map::setTile)
	   .def("has_seens", &Map::has_seens)
	   .def("has_passed", &Map::has_passed)
	   .def("has_remembers", &Map::has_remembers)
	   .def("setSeen", &Map::setSeen)
	   .def("setRemember", &Map::setRemember)
	   .def("setPassed", &Map::setPassed)
	   .def("setNotVisible", &Map::setNotVisible)
	   .def("setVisible", &Map::setVisible)
	   .def("createMap", &Map::createMap),

    luabind::class_<Tile>("Tile")
        .def( luabind::constructor<>( ) )
        .def_readwrite("gfx", &Tile::gfx)
        .def_readwrite("type", &Tile::tipo)
        .enum_("Tile_type")
        [
            luabind::value("NONE", TILE_NONE),
            luabind::value("BLOCK", TILE_SOLID),
            luabind::value("PASS", TILE_FLOOR),
            luabind::value("START", TILE_START_LV),
            luabind::value("END", TILE_FINISH_LV),
            luabind::value("CHEST", TILE_OBJ_CHEST)
        ],

    luabind::class_<sf::Vector2i>("Vector2i")
        .def( luabind::constructor<>( ) )
        .def_readwrite("x", &sf::Vector2i::x)
        .def_readwrite("y", &sf::Vector2i::y),

    luabind::class_<GameObject>("Obj")
        .def( luabind::constructor<>( ) )
        .property("x", &GameObject::getPositionX)
        .property("y", &GameObject::getPositionY)
        .def_readwrite("type", &GameObject::type)
        .def("changeSprite", &GameObject::changeSprite)
        .def("addObj", &GameObject::addToObjectList )
        .def("removeObj", &GameObject::removeFromObjectList )
        .def("removeReference", &GameObject::removeFromTileReference )
        .def("getPos", &GameObject::getPosition )
        .def("setPos", (void (GameObject::*)(int, int))&GameObject::setPosition )
        .def("setPos", (void (GameObject::*)(sf::Vector2i))&GameObject::setPosition )
        .enum_("Obj_type")
        [
            luabind::value("ENEMY", TYPE_ENEMY),
            luabind::value("PLAYER", TYPE_PLAYER),
            luabind::value("ITEM", TYPE_ITEM),
            luabind::value("TRAP", TYPE_TRAP),
            luabind::value("DESTROYABLE", TYPE_DESTROYABRE)
        ]

        ,

    luabind::class_<Entity, GameObject>("Entity")
        .def( luabind::constructor<>( ) )
        .def_readwrite("mHp", &Entity::mHP)
        .def_readwrite("mMp", &Entity::mMP)
        .def_readwrite("mSpeedCost", &Entity::mSpeedCost)
        .def_readwrite("mRange", &Entity::mRange)
        .def_readwrite("mAtk", &Entity::mAtk)
        .def_readwrite("mDef", &Entity::mDef)
        .def("move", (bool (Entity::*)(int, int))&Entity::movePosition)
        .def("move", (void (Entity::*)(int))&Entity::movePosition)
        .def("geraRota", &Entity::geraRota)
        .def("isRota", &Entity::isRota)
        .def("getRotaTarget", &Entity::getRotaTarget)
        .def("moveRota", &Entity::moveRota),

    luabind::class_<Player, Entity>("Player")
        .def( luabind::constructor<>( ) )
        .def_readwrite("mHasEnemys", &Player::mHasEnemys)
        .def_readwrite("mHasNewTiles", &Player::mHasNewTiles),

    luabind::class_<Item, GameObject>("Item")
        .def( luabind::constructor<>( ) )
        .def_readwrite("mHp", &Item::mHp)
        .def_readwrite("mMp", &Item::mMp)
        .def_readwrite("mAtk", &Item::mAtk)
        .def_readwrite("mDef", &Item::mDef)
        .def_readwrite("mIsBuff", &Item::mIsBuff)
        .def_readwrite("mGold", &Item::mGold),

    luabind::class_<ResourceManager>("ResourceManager")
        .def( luabind::constructor<>( ) )
        .def( "createItem", &ResourceManager::createItem)
        .def( "createEntity", &ResourceManager::createEntity)
        .def( "getItem", &ResourceManager::getItem)
        .def( "getEntity", &ResourceManager::getEntity)
        .def( "getEntityByIndex", &ResourceManager::getEntityByIndex)
        .def( "getItemByIndex", &ResourceManager::createItem)
        .def( "addGold", &ResourceManager::addGold)
        .def( "addEntityByIndex", &ResourceManager::addEntityByIndex)
        .def( "addItemByIndex", &ResourceManager::addItemByIndex)
        .def( "addEntity", &ResourceManager::addEntity)
        .def( "addItem", &ResourceManager::addItem)
        .def( "addCustomEntity", &ResourceManager::addCustomEntity)
        .def( "clearEntityMap", &ResourceManager::clearEntityMap)
        .def( "clearItemMap", &ResourceManager::clearEntityMap),

    luabind::class_<std::string>("stdString")
        .def( luabind::constructor<>( ) )
    ;
}

//all of the error messages are pushed on to the stack, so while there are items on the stack, pop and print them
void LuaManager::ReportLuaError(lua_State* luaState)

{
    const char* msg = lua_tostring(luaState,-1);

    while(msg)
    {
        lua_pop(luaState,1);
        std::cout << msg << std::endl;
        msg = lua_tostring(L,-1);
    }

}







void LuaManager::doFile(const char* filename)
{
    if( luaL_dofile(L, filename) )
    {
        ReportLuaError(L);
    }
}

void LuaManager::doFunctionInFile(const char* functionName)
{
    luabind::call_function<int>(L, functionName);
}



void LuaManager::loadConfigs(std::string filename, int& width, int& height, int& tile)
{
    L = luaL_newstate();
    luaL_openlibs(L);

    if( luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
    {
        luaL_error(L, "Erro ao rodar arquivo de configuracao: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    lua_getglobal(L, "tile_size");
    if(!lua_isnumber(L, -3))
    {
        luaL_error(L, "'width' deve ser um numero\n");
    }
    if(!lua_isnumber(L,-2))
    {
        luaL_error(L, "'height' deve ser um numero\n");
    }
    if(!lua_isnumber(L,-1))
    {
        luaL_error(L, "'tile_size' deve ser um numero\n");
    }

    width = (int) lua_tonumber(L, -3);
    height = (int) lua_tonumber(L, -2);
    tile = (int) lua_tonumber(L, -1);

    lua_close(L);
}




LuaManager::LuaManager()
{
    //ctor
    L = nullptr;
}

LuaManager::~LuaManager()
{
    //Close lua
    if(L != nullptr)
        lua_close(L);
}

void LuaManager::executeTests()
{
    Tile t; t.gfx = 1;
	luabind::globals(L)["tile"] = t;

	sf::Vector2i v(1,2);
	luabind::globals(L)["v"] = &v;
	Entity obj; obj.setPosition(2,1);
	luabind::globals(L)["obj"] = &obj;

	int error = luaL_dostring(L,
				  "print('map height: ' .. map.h)\n"
				  "print('map width: ' .. map.w)\n"
				  "print('tile t: ' .. tile.id)\n"
				  "print('vector: ' .. v.x .. ',' .. v.y)\n"
				  "print('obj: ' .. obj:getPos().x .. ',' .. obj:getPos().y)\n"
				  "t = map:getTile(0,0)\n"
				  "print(t.id)\n"
				  );


    cout << obj.getPosition().x << "," << obj.getPosition().y << endl;

    if(error != 0)
        ReportLuaError(L);
}
