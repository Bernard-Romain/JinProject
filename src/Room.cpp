#include <cassert>
#include <iostream>
#include <sstream>

#include "Room.h"
#include "Wall.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

Room::Room(pugi::xml_node node)
    : label { node.attribute("label").as_string() }
{
    for (auto child : node.children())
    {
        assert((child.name() == "Wall"sv) || (child.name() == "Monster"sv) || (child.name() == "Player"sv));
        if (child.name() == "Wall"sv) {
            entities.push_back(make_unique<Wall>(child));
        }
        if (child.name() == "Monster"sv) {
            entities.push_back(make_unique<Monster>(child));
        }
        if (child.name() == "Player"sv) {
            entities.push_back(make_unique<Player>(child));
        }
    }
}

void Room::render() {

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