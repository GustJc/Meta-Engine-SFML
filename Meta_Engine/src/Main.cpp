#include "GameManager.h"

using namespace std;

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
    GameManager app;
    return app.run(argc, args);
}
