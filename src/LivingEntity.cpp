#include "LivingEntity.h"
#include <sstream>

using namespace std;

LivingEntity::LivingEntity(pugi::xml_node node)
	: MovingEntity(node)
	, hp{ node.attribute("hp").as_int() }
{}

void LivingEntity::damage() const
{
	//A IMPLEMENTER, SI L'ON VEUT QUE LES ENNEMIS/ LE JOUEUR NE MEURE PAS EN UN COUP
}

std::string LivingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << MovingEntity::dump(indent) << "hp: " << hp << ", ";
	return oss.str();
}
