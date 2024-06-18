#pragma once
#include "Entity.h"

class Wall : public Entity {
public:
	explicit(false) Wall(pugi::xml_node node);
	std::string dump(std::string const& indent) const override;
private:
	int x_size;
	int y_size;
};