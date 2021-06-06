#pragma once

#include <functional>

class BattleshipsPlusPlusCore {
public:
    template<typename T>
    std::function<void(T)> DrawFn;
}