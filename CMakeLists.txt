# Specify the minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Set the variable projectName to "flappy"
set(projectName "Crawler")

# Declare the project with the specified language (C++)
project(${projectName} LANGUAGES CXX)

# Set the output directory for executables to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define an option to build shared libraries (default is OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include FetchContent module for managing external dependencies
include(FetchContent)

# Fetch and declare SFML as an external dependency
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch and declare EnTT as an external dependency
FetchContent_Declare(EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2)  # Specify the desired tag or commit
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)  # Specify the desired tag or commit
FetchContent_MakeAvailable(json)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

# Debug info on where the binary directory is
message(STATUS "Binary directory: ${CMAKE_BINARY_DIR}")

# Create an executable target named "flappy" with the source file src/main.cpp
add_executable(${projectName} src/main.cpp  "src/Engine/GameEngine.cpp" "src/Engine/Assets.cpp" "src/Engine/Scene/Scene.cpp" "src/Engine/Scene/Scene_Menu.cpp" "src/Engine/Action/Action.cpp" "src/Engine/Scene/Scene_Play.cpp" "src/Core/Factories.cpp" "src/Sys/Systems.cpp" "src/Sys/sMovement.cpp" "src/Sys/sAnimation.cpp" "src/Sys/sSampleSystem.cpp" "src/Sys/sRender.cpp" "src/Engine/Animation.cpp")

# Link the executable against SFML and EnTT libraries
target_link_libraries(${projectName} PRIVATE sfml-graphics sfml-audio ImGui-SFML::ImGui-SFML EnTT::EnTT nlohmann_json::nlohmann_json)

# Set the C++ standard to C++17 for the "flappy" target
target_compile_features(${projectName} PRIVATE cxx_std_17)

# Check if the platform is Windows
if(WIN32)
    # Add a custom command to copy OpenAL DLL before building
    add_custom_command(
        TARGET ${projectName}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${projectName}>
        VERBATIM)
endif()

# Install the "flappy" target
install(TARGETS ${projectName})