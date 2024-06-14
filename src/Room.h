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

    void discover() { state = (monster > 0) ? Room_State::Active : Room_State::Cleared; }

    void killMonster() { monster--; if (monster == 0) state = Room_State::Cleared; }

    std::string dump(std::string const& indent) const;
    std::string getLabel() { return label; }
    Room_State getState() { return state; }
    std::vector<std::unique_ptr<Entity>> entities;
private:
    std::string label;
    Room_State state;

    int monster;
};

