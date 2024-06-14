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

    void render(sf::RenderWindow* mWindow) const;
    void update();

    std::string dump(std::string const& indent) const;
    std::string getLabel() { return label; }
    std::vector<std::unique_ptr<Entity>> entities;
private:
    std::string label;
    Room_State state;

};

