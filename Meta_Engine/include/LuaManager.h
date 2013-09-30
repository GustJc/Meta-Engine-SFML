#pragma once
#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>
#include <string>


class LuaManager
{
    public:
        LuaManager();
        virtual ~LuaManager();

        static LuaManager LuaControl;

        void startLua();
        void doFile(const char* filename);
        void doFunctionInFile(const char* functionName);

        void executeTests();

        void loadConfigs(std::string filename, int& width, int& height, int& tile);

        void ReportLuaError(lua_State* luaState);
    protected:
        lua_State* L;
    private:
        luabind::scope bindClasses();
};
