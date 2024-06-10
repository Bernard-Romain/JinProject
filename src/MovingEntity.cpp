#include "MovingEntity.h"
#include <sstream>

using namespace std;

MovingEntity::MovingEntity(pugi::xml_node node)
	: Entity(node)
	, speed{ node.attribute("speed").as_float() }
{}

void MovingEntity::move()
{
	position += direction * speed;
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

