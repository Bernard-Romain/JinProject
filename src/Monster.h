#pragma once
#include "LivingEntity.h"

class Monster : public LivingEntity {
public:
	Monster(pugi::xml_node node);
	std::string dump(std::string const& indent) const;
private:
};