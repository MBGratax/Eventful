cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp src/rendering/shader.cpp src/rendering/shader.h src/rendering/mesh.cpp src/rendering/mesh.h src/entities/entity.cpp src/entities/entity.h src/game.cpp src/game.h src/physics/listner.cpp src/physics/listner.h)

set(EXE_FILE Ventscape)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")
message(${TINYGLTF_INCLUDE_DIRS})
target_include_directories(${EXE_FILE} PRIVATE ${TINYGLTF_INCLUDE_DIRS}/tiny_gltf.h)

target_link_libraries(${EXE_FILE} PRIVATE fmt::fmt glad::glad glfw glm::glm portaudio box2d::box2d)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=${PROJECT_SOURCE_DIR})

