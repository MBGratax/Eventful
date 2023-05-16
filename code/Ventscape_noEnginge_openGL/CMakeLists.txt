cmake_minimum_required(VERSION 3.18)

project(Ventscape_noEnginge_openGL)

add_subdirectory(game)

include(GoogleTest)
include(InstallRequiredSystemLibraries)

include(CPack)

# Specify the package generator and format
set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-Win64")


