#include "Projectile.h"
#include "Player.h"
#include <iostream>

using namespace std;

Projectile::Projectile(sf::Vector2f position, std::string const& spriteLabel, float speed, sf::Vector2f direction, int damage, Player* player) 
	: MovingEntity(position, spriteLabel, speed, direction)
	, damage { damage }
	, player { player }
{}

void Projectile::move()
{
	position += direction * speed;
}

void Projectile::update(std::vector<std::unique_ptr<Entity>> const &entities) {
	this->move();
	sprite.setPosition(position);
}

void Projectile::collide_with(Entity& other) {
	player->desactiveProjectile(this);
	other.collide_with(*this);
};