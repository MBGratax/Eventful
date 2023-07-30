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
        src/physics/PhysicsWorld.h
        src/entities/PlayerCharacter.cpp
        src/entities/PlayerCharacter.h
        src/Asset.h
        src/TimeStep.h)

set(EXE_FILE Ventscape)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_definitions(${EXE_FILE} PRIVATE $ENV{PREPROCESSORS})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_20)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")

target_include_directories(${EXE_FILE}
        PRIVATE ${TINYGLTF_INCLUDE_DIRS})

target_link_libraries(${EXE_FILE}
        PRIVATE glad::glad
        PRIVATE glfw
        PRIVATE glm::glm
        PRIVATE portaudio
        PRIVATE box2d::box2d
        PRIVATE JsonCpp::JsonCpp
        PRIVATE imgui::imgui
        PRIVATE imguizmo::imguizmo)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=${CMAKE_INSTALL_PREFIX})

install(TARGETS ${EXE_FILE}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Meshes DESTINATION Assets)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Shaders DESTINATION Assets)

install(IMPORTED_RUNTIME_ARTIFACTS glfw portaudio
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
        LIBRARY DESTINATION lib)

set(LIBS
        $<TARGET_FILE:glad::glad>
        $<TARGET_FILE:box2d::box2d>
        $<TARGET_FILE:imgui::imgui>
        $<TARGET_FILE:imguizmo::imguizmo>)

install(FILES ${LIBS} DESTINATION lib)

# Specify the package generator and format
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-Win64")

set(CPACK_PACKAGE_NAME "Ventscaped")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple endless platformer in openGL")
set(CPACK_PACKAGE_VENDOR "Jonas Haefner")
#set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
#set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
#set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

include(CPack)
