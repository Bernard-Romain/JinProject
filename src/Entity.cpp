#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

sf::Vector2f position;
sf::Image sprite;

Entity::Entity(pugi::xml_node node) 
	: position{ sf::Vector2f (node.attribute("x").as_float(),node.attribute("y").as_float())}
{
	sprite = sf::Image();
	string spriteLabel = node.attribute("sprite").as_string();
	if (spriteLabel == "Wall"sv) sprite.loadFromFile("sprites/Wall.png");
	else cout << "a\n\n\n";
}

void Entity::render()
{
}

int Entity::isHit()
{
	return 0;
}

void Entity::collide()
{
}

void Entity::update()
{
}

std::string Entity::dump(std::string const& indent) const {

	ostringstream oss;
	oss	<< "x: " << position.x << ", "
		<< "y: " << position.y << ", ";
	return oss.str();
}
