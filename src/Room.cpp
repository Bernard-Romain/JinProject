#include <cassert>
#include <iostream>
#include <sstream>

#include "Room.h"
#include "Wall.h"

using namespace std;

Room::Room(pugi::xml_node node)
{
    for (auto child : node.children())
    {
        assert((child.name() == "Wall"sv));
        if (child.name() == "Wall"sv) {
            entities.push_back(make_unique<Wall>(child));
        }
    }
}

void Room::render() {

}

void Room::update() {

}

std::string Room::dump(std::string const& indent) const{

    ostringstream oss;
    oss << indent << "Room [" << endl;
    for (auto const& c : entities) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}