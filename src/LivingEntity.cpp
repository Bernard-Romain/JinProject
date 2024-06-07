#include "LivingEntity.h"
#include <sstream>

using namespace std;

LivingEntity::LivingEntity(pugi::xml_node node)
	: MovingEntity(node)
	, hp{ node.attribute("hp").as_int() }
{}

void LivingEntity::damage()
{
}

std::string LivingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << MovingEntity::dump(indent) << "hp: " << hp << ", ";
	return oss.str();
}
