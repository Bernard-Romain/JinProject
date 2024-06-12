#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

Entity::Entity(sf::Vector2f position, string spriteLabel) 
	: position { position }
{
	texture = sf::Texture();

	texture.loadFromFile("resources/sprites/" + spriteLabel + ".png");
	if (spriteLabel == "Tear"sv) sprite.setScale(sf::Vector2f(0.3, 0.3));

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

Entity::Entity(pugi::xml_node node) : position{ sf::Vector2f (node.attribute("x").as_float(),node.attribute("y").as_float())}
{
	texture = sf::Texture();

	string spriteLabel = node.attribute("sprite").as_string();
	texture.loadFromFile("resources/sprites/" + spriteLabel + ".png");

	if (spriteLabel == "FatEnemy"sv) sprite.setScale(sf::Vector2f(2.5, 2.5));
	if (spriteLabel == "Door"sv) sprite.setScale(sf::Vector2f(0.6, 0.6));

	sprite.setTexture(texture);
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