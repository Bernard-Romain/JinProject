#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

Entity::Entity(pugi::xml_node node) : position{ sf::Vector2f (node.attribute("x").as_float(),node.attribute("y").as_float())}
{
	texture = sf::Texture();

	string spriteLabel = node.attribute("sprite").as_string();
	if (spriteLabel == "Wall"sv) texture.loadFromFile("resources/sprites/Wall.png");

	sprite.setTexture(texture);
}

void Entity::render(sf::RenderWindow mWindow)
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
