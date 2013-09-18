#pragma once
#include <lua5.2/lua.hpp>
#include <string>
class LuaManager
{
    public:
        LuaManager();
        virtual ~LuaManager();

        static LuaManager LuaControl;

        void loadConfigs(std::string filename, int& width, int& height, int& tile);

        int BaseLuaInterpreter();
        int BaseLuaInterpreter2();
    protected:
        lua_State* L;
    private:
};
