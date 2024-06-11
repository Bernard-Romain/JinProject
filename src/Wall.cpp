#include "Wall.h"
#include <sstream>

using namespace std;

Wall::Wall(pugi::xml_node node)
	: Entity(node)
    , x_size { node.attribute("x_size").as_int() }
    , y_size{ node.attribute("y_size").as_int() }
{
    sprite.setTextureRect({ (int)position.x,(int)position.y,x_size,y_size });
    texture.setRepeated(true);
}

std::string Wall::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent << 
        "Wall " << Entity::dump(indent) << endl;
    return oss.str();
}

