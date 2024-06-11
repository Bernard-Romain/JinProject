#include "MovingEntity.h"
#include <sstream>

using namespace std;

MovingEntity::MovingEntity(sf::Vector2f position, std::string spriteLabel, float speed, sf::Vector2f direction)
	: Entity(position, spriteLabel)
	, speed { speed }
	, direction{ direction }
{}

MovingEntity::MovingEntity(pugi::xml_node node) : Entity(node), speed{ node.attribute("speed").as_float() }
{
}

void MovingEntity::move()
{
	direction = sf::Vector2f();
	if (isMovingUp)
	{
		direction += sf::Vector2f(0, 1);
	}
	if (isMovingDown)
	{
		direction += sf::Vector2f(0, -1);
	}
	if (isMovingLeft)
	{
		direction += sf::Vector2f(1, 0);
	}
	if (isMovingRight)
	{
		direction += sf::Vector2f(-1, 0);
	}
	position += direction * speed;
}

std::string MovingEntity::dump(std::string const& indent) const {

	ostringstream oss;
	oss << Entity::dump(indent) << "speed: " << speed << ", ";
	return oss.str();
}

void MovingEntity::update()
{
	move();
	sprite.setPosition(position);
}
