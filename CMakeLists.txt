cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

message(STATUS "Fetching ImGui-SFML...")

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

add_executable(main src/main.cpp
        src/world/World.cpp
        src/world/World.h
        src/world/Cell.cpp
        src/world/Cell.h
        src/util/utils.cpp
        src/world/SolidMovableCell.cpp
        src/world/SolidMovableCell.h
        src/world/cells/Sand.cpp
        src/world/cells/Sand.h
        src/world/SolidImmovableCell.cpp
        src/world/SolidImmovableCell.h
        src/world/cells/Barrier.cpp
        src/world/cells/Barrier.h
        src/world/cells/NothingCell.cpp
        src/world/cells/NothingCell.h
        src/world/FluidCell.cpp
        src/world/FluidCell.h
        src/world/cells/Water.cpp
        src/world/cells/Water.h
        src/world/cells/Metal.cpp
        src/world/cells/Metal.h
        src/Drawing.cpp
        src/saving.cpp
        src/world/cell_info.cpp
        src/world/cell_info.h
        src/world/cell_info.h)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
