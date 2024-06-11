#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

Entity::Entity(pugi::xml_node node) : position{ sf::Vector2f (node.attribute("x").as_float(),node.attribute("y").as_float())}
{
	texture = sf::Texture();

	string spriteLabel = node.attribute("sprite").as_string();
	if (spriteLabel == "Wall"sv) texture.loadFromFile("resources/sprites/Wall.png");
	if (spriteLabel == "Player"sv) texture.loadFromFile("resources/sprites/Isaac.png");

	texture.setRepeated(true);

	sprite.setTexture(texture);
	sprite.setTextureRect({0,0,1960,60});
	sprite.setPosition(position);
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

void Entity::render(sf::RenderWindow* mWindow) const {
	mWindow->draw(sprite);
}