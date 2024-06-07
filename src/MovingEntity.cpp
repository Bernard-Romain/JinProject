#include "MovingEntity.h"
#include <sstream>

using namespace std;

MovingEntity::MovingEntity(pugi::xml_node node)
	: Entity(node)
	, speed{ node.attribute("speed").as_int() }
{}

void MovingEntity::move()
{
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

