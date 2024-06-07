#include "Wall.h"
#include <sstream>

using namespace std;

Wall::Wall(pugi::xml_node node)
	: Entity(node)
{}

std::string Wall::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent << 
        "Wall " << Entity::dump(indent) << endl;
    return oss.str();
}