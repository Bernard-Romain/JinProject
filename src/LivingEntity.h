#pragma once
#include "MovingEntity.h"

class LivingEntity : public MovingEntity {
public:
	LivingEntity(pugi::xml_node node);

	virtual std::string dump(std::string const& indent) const;
	void damage();
private:
	int hp;
};