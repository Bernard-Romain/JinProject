#include "MovingEntity.h"
#include <sstream>
#include <iostream>

using namespace std;

MovingEntity::MovingEntity(std::string const& label, sf::Vector2f const& position, std::string const& spriteLabel, float const& speed, sf::Vector2f const& direction)
	: Entity(label, position, spriteLabel)
	, speed { speed }
	, direction{ direction }
{}

MovingEntity::MovingEntity(pugi::xml_node node) 
	: Entity(node)
	, speed{ node.attribute("speed").as_float() }
{}

void MovingEntity::move(std::vector<std::unique_ptr<Entity>> const& entities)
{
	//TODO : REMOVE OR FIND HOW TO CALL HANDLECOLLISION OF PLAYER FROM HERE
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

	isColliding = false;
	for (auto const& entity : entities)
	{
		if (collide(*entity)) {
			isColliding = true;
			this->handleCollision(entity.get());
		}
	}

	if (isColliding) {
		position = lastPosition;
		sprite.setPosition(lastPosition);
	}
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

void MovingEntity::update(std::vector<std::unique_ptr<Entity>> const& entities)
{
	move(entities);
}

void MovingEntity::handleCollision(Entity* const entity) const {
	//TODO : IMPLEMENT HERE FOR PLAYER OR DELETE
}