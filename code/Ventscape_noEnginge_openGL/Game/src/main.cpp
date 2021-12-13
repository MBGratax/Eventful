
#include "game.h"
#include <iostream>

const float W_WIDTH = 1280.0f;
const float W_HEIGHT = 720.0f;
const char* W_TITLE = "SpaceBattle";

#define _AS_STRING(x) #x
#define AS_STRING(x) _AS_STRING(x)

int main(){

    try {

        namespace fs = std::filesystem;
        auto assetPath = AS_STRING(DEBUG_ASSET_ROOT) / fs::path("assets");

        assetPath = fs::canonical(assetPath).make_preferred();

        gl3::game spaceBattle(assetPath, W_WIDTH, W_HEIGHT, W_TITLE);
        spaceBattle.run();

    } catch (const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}