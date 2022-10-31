
#include "game.h"
#include <iostream>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

const float W_WIDTH = 1920.0f;
const float W_HEIGHT = 1080.0f;
const char* W_TITLE = "Ventscape";

int main(){

    try {

        namespace fs = std::filesystem;

        auto assetPath = GET_DIR(DEBUG_ASSET_ROOT) / fs::path("assets");

        assetPath = fs::canonical(assetPath).make_preferred();

        Ventgame::game spaceBattle(assetPath, W_WIDTH, W_HEIGHT, W_TITLE);
        spaceBattle.run();
    } catch (const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}