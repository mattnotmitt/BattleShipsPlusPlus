cmake_minimum_required(VERSION 3.20.0)
project(BattleShipsPlusPlus 
    VERSION 0.1.0
    LANGUAGES CXX)

find_package(Curses REQUIRED)

# Game logic source libraries
add_subdirectory(src)
# Executables
add_subdirectory(apps)
