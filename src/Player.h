#pragma once
#include "LivingEntity.h"
#include "Projectile.h"

class Player : public LivingEntity {
public:
	Player(pugi::xml_node node);
	std::string dump(std::string const& indent) const;
	void manageInput(sf::Keyboard::Key input, bool active);
	void shoot(sf::Vector2i mousePosition);

	void render(sf::RenderWindow* mWindow) const;
	void update();
private:
	std::vector<std::unique_ptr<Projectile>> activeProjectiles;
	std::vector<std::unique_ptr<Projectile>> inactiveProjectiles;
};