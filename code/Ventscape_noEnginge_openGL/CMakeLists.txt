cmake_minimum_required(VERSION 3.18)
project(Ventscape_noEngine_openGL)

add_subdirectory(Extern/glad)
add_subdirectory(Extern/glfw)
add_subdirectory(Extern/glm)
add_subdirectory(Extern/tinygltf)
add_subdirectory(Extern/soloud)
add_subdirectory(Extern/box2d)

add_subdirectory(game)

set(CMAKE_CXX_STANDARD 17)
