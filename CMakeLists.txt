cmake_minimum_required(VERSION 3.27)
set(PROJECT_NAME "untitled")
project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 11)

# Add your source files
add_executable(${PROJECT_NAME} main.c
        setup.c
        input_handler.c
        update.c
        collision_detection.c
        render.c
        sandbox.c
        level_1.c)

# Very Important - DONT FORGET!
# in Run/debug Configurations
# set working directory

# Include SDL2 headers
include_directories("/usr/include/SDL2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Link SDL2 and SDL2_image libraries directly
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libSDL2.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
