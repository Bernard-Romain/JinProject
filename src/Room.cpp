#include <cassert>
#include <iostream>
#include <sstream>

#include "Room.h"
#include "Wall.h"
#include "Player.h"
#include "Monster.h"
#include "Door.h"

using namespace std;

Room::Room(pugi::xml_node node)
    : label { node.attribute("label").as_string() }
    , monster { 0 }
    , state{ Room_State::Undiscovered }
{
    for (auto child : node.children())
    {
        assert((child.name() == "Wall"sv) || (child.name() == "Monster"sv) || (child.name() == "Player"sv) || (child.name() == "Door"sv));
        if (child.name() == "Wall"sv) {
            entities.push_back(make_unique<Wall>(child));
        }
        if (child.name() == "Monster"sv) {
            entities.push_back(make_unique<Monster>(child));
            monster++;
        }
        if (child.name() == "Player"sv) {
            entities.push_back(make_unique<Player>(child));
        }
        if (child.name() == "Door"sv) {
            entities.push_back(make_unique<Door>(child));
        }
    }    
}

void Room::render(sf::RenderWindow* mWindow) const {
    for (auto const& entity : entities) {
        entity.get()->render(mWindow);
    }
}

void Room::update() {

}

std::string Room::dump(std::string const& indent) const{

    ostringstream oss;
    oss << indent << "Room " << label << " [" << endl;
    for (auto const& c : entities) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}
