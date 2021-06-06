add_library(BattleshipsLogic STATIC Ship.cpp)

target_include_directories(BattleshipsLogic 
    PUBLIC  ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus
            ${CMAKE_SOURCE_DIR}/inc/BattleshipsPlusPlus/BattleshipsLogic)
