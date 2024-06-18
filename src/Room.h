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
    explicit(false) Room(pugi::xml_node node);

    void render(sf::RenderWindow* mWindow) const;

    void discover();

    void killMonster(int i);

    std::string dump(std::string const& indent) const;

    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> doors;

    std::string getLabel() const { return label; }
    Room_State getState() const { return state; }

private:
    std::string label;
    Room_State state = Room_State::Undiscovered;
    int monster = 0;

    void clearRoom();
};

