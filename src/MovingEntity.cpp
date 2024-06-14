#include "MovingEntity.h"
#include <sstream>
#include <iostream>

using namespace std;

MovingEntity::MovingEntity(std::string label, sf::Vector2f position, std::string spriteLabel, float speed, sf::Vector2f direction) 
	: Entity(label, position, spriteLabel)
	, speed { speed }
	, direction{ direction }
{}

MovingEntity::MovingEntity(pugi::xml_node node) : Entity(node), speed{ node.attribute("speed").as_float() }
{
}

void MovingEntity::move(std::vector<std::unique_ptr<Entity>> const& entities)
{
	sf::Vector2f memo = position;
	direction = sf::Vector2f();
	if (isMovingUp)
		direction += sf::Vector2f(0, 1);
	if (isMovingDown)
		direction += sf::Vector2f(0, -1);
	if (isMovingLeft)
		direction += sf::Vector2f(1, 0);
	if (isMovingRight)
		direction += sf::Vector2f(-1, 0);

	position += direction * speed;
	sprite.setPosition(position);

	isColliding = false;
	for (int i = 0; i < entities.size(); i++)
	{
		if (collide(*entities[i])) {
			isColliding = true;
			this->handleCollision(entities[i].get());
		}
	}
	if (isColliding) {
		position = memo;
		sprite.setPosition(memo);
	}
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

void MovingEntity::update(std::vector<std::unique_ptr<Entity>> const &entities)
{
	move(entities);
	sprite.setPosition(position);
}

void MovingEntity::handleCollision(Entity* const entity) {

	if (entity->getLabel() == "Door"sv) {
		
	}


}