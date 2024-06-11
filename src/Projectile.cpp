#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile(sf::Vector2f position, std::string spriteLabel, float speed, sf::Vector2f direction, int damage) 
	: MovingEntity(position, spriteLabel, speed, direction)
	, damage { damage }
{}

void Projectile::move()
{
	position += direction * speed;
}

void Projectile::update() {
	this->move();
	sprite.setPosition(position);
}