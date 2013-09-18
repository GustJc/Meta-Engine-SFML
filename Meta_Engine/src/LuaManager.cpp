#include "LuaManager.h"

#include <lua5.2/lua.hpp>

#include <iostream>
using namespace std;

LuaManager LuaManager::LuaControl;

int LuaManager::BaseLuaInterpreter()
{
    /// Inicia interpretador
    lua_State *L = luaL_newstate();
    if(L == NULL) {
        fprintf(stderr, "Erro na inicializacao lua\n");
        return -1;
    }

    luaL_openlibs(L);

    int rc = luaL_dofile(L, "hello.lua");

    cout << "Resultado do script: " << rc << endl;

    lua_close(L);
    return 0;
}

int LuaManager::BaseLuaInterpreter2()
{
    /// Inicia interpretador
    lua_State *L = luaL_newstate();
    if(L == NULL) {
        fprintf(stderr, "Erro na inicializacao lua\n");
        return -1;
    }

    luaL_openlibs(L);

    int rc = luaL_dofile(L, "hello.lua");

    cout << "Resultado do script: " << rc << endl;

    lua_close(L);
    return 0;
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
}

LuaManager::~LuaManager()
{
    //dtor
}

