#pragma once

#include <filesystem>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

namespace fs = std::filesystem;

namespace Ventgame {
    inline fs::path resolveAssetPath(const fs::path &relativeAssetPath) {
        auto l_mergedPath = (fs::current_path() / fs::path("Assets") / relativeAssetPath).make_preferred();
        return fs::canonical(l_mergedPath);
    }
}

