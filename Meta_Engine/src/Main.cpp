#include "GameManager.h"
#include <iostream>
using namespace std;
#include "LuaManager.h"
int main(int argc, char* args[]){
/*
    try{
    TextureManager manager;
    manager.load(Textures::ID::Gust, "mdia/aa.pjg");
    } catch ( std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        return 1;
    }
*/
    try{
       GameManager app;
        return app.run(argc, args);
    }
     catch ( std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        return 1;
    }
    return 0;


}
