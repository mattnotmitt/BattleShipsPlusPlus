add_library(BattleshipsBot STATIC MakeMove.cpp PlaceShips.cpp)

target_include_directories(BattleshipsBot 
    PUBLIC  ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus
            ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus/BattleshipsLogic
            ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus/DrawBattleships)
