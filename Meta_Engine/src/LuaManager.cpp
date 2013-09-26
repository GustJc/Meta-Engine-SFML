#include "LuaManager.h"

#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>

#include <iostream>

using namespace std;

#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"

LuaManager LuaManager::LuaControl;


// ------------ Start Lua --------------------
void LuaManager::startLua()
{
    L = luaL_newstate();
	luaL_openlibs(L);
	luabind::open(L);

	luaL_dostring(L,
				  "print(2)\n"
				  );
    luabind::module(L) [
        bindClasses()
	];

	luabind::globals(L)["map"] =
        &Map::MapControl;

    luabind::globals(L)["player"] =
        &Player::PlayerControl;

	Tile t; t.id = 1;
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

luabind::scope LuaManager::bindClasses()
{
    return
    luabind::class_<Map>("Map")
        .def( luabind::constructor<>( ) )
	   .property("h", &Map::getMapHeight)
	   .property("w", &Map::getMapWidth)
	   .def("getTile", &Map::getTile)
	   .def("has_seens", &Map::has_seens)
	   .def("has_passed", &Map::has_passed)
	   .def("has_remembers", &Map::has_remembers)
	   .def("setSeen", &Map::setSeen)
	   .def("setRemember", &Map::setRemember)
	   .def("setPassed", &Map::setPassed)
	   .def("setNotVisible", &Map::setNotVisible)
	   .def("setVisible", &Map::setVisible),

    luabind::class_<Tile>("Tile")
        .def( luabind::constructor<>( ) )
        .def_readwrite("id", &Tile::id),

    luabind::class_<sf::Vector2i>("Vector2i")
        .def( luabind::constructor<>( ) )
        .def_readwrite("x", &sf::Vector2i::x)
        .def_readwrite("y", &sf::Vector2i::y),

    luabind::class_<GameObject>("GameObject")
        .def( luabind::constructor<>( ) )
        .property("x", &GameObject::getPositionX)
        .property("y", &GameObject::getPositionY)
        .def("getPos", &GameObject::getPosition )
        .def("setPos", (void (GameObject::*)(int, int))&GameObject::setPosition )
        .def("setPos", (void (GameObject::*)(sf::Vector2i))&GameObject::setPosition ),

    luabind::class_<Entity, GameObject>("Entity")
        .def( luabind::constructor<>( ) )
        .def("move", (void (Entity::*)(int, int))&Entity::movePosition)
        .def("move", (void (Entity::*)(int))&Entity::movePosition)
        .def("geraRota", &Entity::geraRota),

    luabind::class_<Player, Entity>("Player")
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

