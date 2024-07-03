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
	//TODO : a voir comment on fait, est ce qu'on vire ca et on met pas tout dans movvingStrategy
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