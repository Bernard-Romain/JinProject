#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

enum class Room_State {
    Undiscovered,
    Active,
    Cleared
};

class Room
{
public:
    Room(pugi::xml_node node);

    void render();
    void update();

    std::string dump(std::string const& indent) const;

private:
    Room_State state;
    std::vector<std::unique_ptr<Entity>> entities;
};

