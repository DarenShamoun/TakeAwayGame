cmake_minimum_required(VERSION 3.12) 
project(take-away VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")
include (prevent_source_builds)
include (clang_tidy)

# If not using tests list all source files here
add_executable(${PROJECT_NAME} main.cpp 
  computer_player.h computer_player.cpp
  game.h game.cpp
  options.h options.cpp
 )