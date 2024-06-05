#pragma once
#include <vector>
#include <memory>

enum class Room_State {
    Undiscovered,
    Active,
    Cleared
};

class Room
{
public:
    void render();
    void update();
private:
    Room_State state;
    std::vector<std::unique_ptr<Entity>> entities;
};

