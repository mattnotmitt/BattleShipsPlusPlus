cmake_minimum_required(VERSION 3.20.0)
project(BattleShipsPlusPlus VERSION 0.1.0)


# External libraries
add_subdirectory(extern)
# Game logic source libraries
add_subdirectory(src)
# Executables
add_subdirectory(apps)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
