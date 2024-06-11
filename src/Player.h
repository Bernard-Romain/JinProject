#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity {
public:
	Player(pugi::xml_node node);
	std::string dump(std::string const& indent) const;
	void manageInput(sf::Keyboard::Key input, bool active);
private:
};