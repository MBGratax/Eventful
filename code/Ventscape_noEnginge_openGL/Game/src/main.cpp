
#include "Game.h"
#include <iostream>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

const int W_WIDTH = 1920;
const int W_HEIGHT = 1080;
constexpr auto W_TITLE = "Ventscape";

int main() {

    try {

        namespace fs = std::filesystem;

        auto l_assetPath = GET_DIR(DEBUG_ASSET_ROOT) / fs::path("assets");

        l_assetPath = fs::canonical(l_assetPath).make_preferred();

        Ventgame::Game l_ventscaped(l_assetPath, W_WIDTH, W_HEIGHT, W_TITLE);
        l_ventscaped.Run();
    } catch (const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}