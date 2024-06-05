#include <cassert>
#include <iostream>

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

    return "NOT YET IMPLEMENTED";
}