#include <cassert>
#include <iostream>
#include <sstream>

#include "Room.h"

using namespace std;

Room::Room(pugi::xml_node node)
{
    for (auto child : node.children())
    {
        cout << "top\n";
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