#include "MovingEntity.h"
#include <sstream>
#include <iostream>

using namespace std;

MovingEntity::MovingEntity(sf::Vector2f const& position, std::string const& spriteLabel, float const& speed, sf::Vector2f const& direction)
	: Entity(position, spriteLabel)
	, speed { speed }
	, direction{ direction }
{}

MovingEntity::MovingEntity(pugi::xml_node node) 
	: Entity(node)
	, speed{ node.attribute("speed").as_float() }
{}

void MovingEntity::move()
{
	//TODO : doublon avec le player
	lastPosition = position;

	direction = sf::Vector2f(0, 0);
	if (isMovingUp)
		direction += sf::Vector2f(0, -1);
	if (isMovingDown)
		direction += sf::Vector2f(0, 1);
	if (isMovingLeft)
		direction += sf::Vector2f(-1, 0);
	if (isMovingRight)
		direction += sf::Vector2f(1, 0);

	position += direction * speed;
	sprite.setPosition(position);
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

void MovingEntity::update(std::vector<std::unique_ptr<Entity>> const& entities)
{
	move();
}

void MovingEntity::handleCollision(Entity* const entity) const {
	//TODO : implémenter ici, ou supprimer (a voir avec le joueur)
}