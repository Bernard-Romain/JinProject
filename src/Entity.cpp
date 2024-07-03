#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

Entity::Entity(sf::Vector2f const &position, string const &spriteLabel) 
	: position { position }
{
	texture.loadFromFile("resources/sprites/" + spriteLabel + ".png");

	if (spriteLabel == "Tear"sv) sprite.setScale(sf::Vector2f(0.3f, 0.3f));  

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

Entity::Entity(pugi::xml_node node) 
	: position{ sf::Vector2f (node.attribute("x").as_float(),node.attribute("y").as_float())}
{
	string spriteLabel = node.attribute("sprite").as_string();
	texture.loadFromFile("resources/sprites/" + spriteLabel + ".png");

	if (spriteLabel == "FatEnemy"sv) sprite.setScale(sf::Vector2f(1, 1));
	if (spriteLabel == "Door"sv) sprite.setScale(sf::Vector2f(1.5, 1.5));

	sprite.setTexture(texture);
	sprite.setPosition(position);
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