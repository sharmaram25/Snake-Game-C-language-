cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SDL2 paths manually if not found automatically
if(NOT SDL2_DIR AND EXISTS "${CMAKE_SOURCE_DIR}/deps/SDL2")
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2")
endif()

if(NOT SDL2_TTF_DIR AND EXISTS "${CMAKE_SOURCE_DIR}/deps/SDL2_ttf")
    set(SDL2_TTF_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_ttf")
endif()

if(NOT SDL2_MIXER_DIR AND EXISTS "${CMAKE_SOURCE_DIR}/deps/SDL2_mixer")
    set(SDL2_MIXER_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_mixer")
endif()

# Find SDL2
if(WIN32)
    # Check if we're using MinGW
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # For MinGW, link directly to DLL import libraries and add system libs
        set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
        set(SDL2_LIBRARIES 
            "${SDL2_DIR}/lib/x64/SDL2.dll"
            "${SDL2_DIR}/lib/x64/SDL2main.lib"
            mingw32
            winmm
            ole32
            oleaut32
            imm32
            setupapi
            version)
        
        set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include")
        set(SDL2_TTF_LIBRARIES "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.dll")
        
        set(SDL2_MIXER_INCLUDE_DIRS "${SDL2_MIXER_DIR}/include")
        set(SDL2_MIXER_LIBRARIES "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.dll")
    else()
        # For Visual Studio, use .lib libraries
        set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
        set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
        
        set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include")
        set(SDL2_TTF_LIBRARIES "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.lib")
        
        set(SDL2_MIXER_INCLUDE_DIRS "${SDL2_MIXER_DIR}/include")
        set(SDL2_MIXER_LIBRARIES "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.lib")
    endif()
else()
    # For other systems, use find_package
    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/SDL2/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/SDL2_ttf/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/SDL2_mixer/include)

# Add executable
add_executable(SnakeGame 
    src/main.cpp
    src/game.cpp
    src/snake.cpp
    src/food.cpp
    src/text.cpp
    src/sound.cpp
    src/grid.cpp
)

# Link libraries
target_link_libraries(SnakeGame 
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Copy executable to build directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
