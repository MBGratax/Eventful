#pragma once

#include <filesystem>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

namespace fs = std::filesystem;

namespace Ventgame {
    inline fs::path resolveAssetPath(const fs::path &relativeAssetPath) {
        fs::path l_root;
#if(NDEBUG)
        l_root = fs::current_path();
#else
        l_root = GET_DIR(DEBUG_ASSET_ROOT);
#endif
        auto l_mergedPath = (l_root / fs::path("Assets") / relativeAssetPath).make_preferred();
        return fs::canonical(l_mergedPath);
    }
}

