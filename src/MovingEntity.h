#pragma once
#include "Entity.h"

class MovingEntity : public Entity {
public:
	MovingEntity(pugi::xml_node node);

	void move();
	virtual std::string dump(std::string const& indent) const;
private:
	int speed;
};