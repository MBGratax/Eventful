cmake_minimum_required(VERSION 3.23)

set(SOURCE_FILES
        src/main.cpp
        src/rendering/Shader.cpp
        src/rendering/Shader.h
        src/rendering/Mesh.cpp
        src/rendering/Mesh.h
        src/entities/Entity.cpp
        src/entities/Entity.h
        src/Game.cpp
        src/Game.h
        src/physics/Listner.cpp
        src/physics/Listner.h
        src/physics/PhysicsWorld.cpp
        src/physics/PhysicsWorld.h src/entities/PlayerCharacter.cpp src/entities/PlayerCharacter.h)

set(EXE_FILE Ventscape)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_definitions(${EXE_FILE} PRIVATE $ENV{PREPROCESSORS})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")

target_include_directories(${EXE_FILE}
        PRIVATE ${TINYGLTF_INCLUDE_DIRS})

target_link_libraries(${EXE_FILE}
        PRIVATE glad::glad
        PRIVATE glfw
        PRIVATE glm::glm
        PRIVATE portaudio
        PRIVATE box2d::box2d)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=${PROJECT_SOURCE_DIR})
