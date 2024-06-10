#pragma once
#include "Entity.h"

class Wall : public Entity {
public:
	Wall(pugi::xml_node node);
	std::string dump(std::string const& indent) const;
private:
	void render(sf::RenderWindow* mWindow) const;
};