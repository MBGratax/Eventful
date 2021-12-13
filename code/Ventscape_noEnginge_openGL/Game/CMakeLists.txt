cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp src/rendering/shader.cpp src/rendering/shader.h src/rendering/mesh.cpp src/rendering/mesh.h src/entities/entity.cpp src/entities/entity.h src/game.cpp src/game.h)

set(EXE_FILE Ventscape)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE glad glfw glm soloud tinygltf)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=${PROJECT_SOURCE_DIR})

