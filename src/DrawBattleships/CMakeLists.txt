add_library(DrawBattleships STATIC Screen.cpp)

target_include_directories(DrawBattleships 
    PUBLIC  ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus
            ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus/DrawBattleships
            ${CURSES_INCLUDE_DIRS})

target_link_libraries(DrawBattleships PUBLIC BattleshipsLogic ${CURSES_LIBRARIES})
