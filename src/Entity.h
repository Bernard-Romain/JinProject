#pragma once
#include <string>
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f position;
	sf::RectangleShape shape;
	sf::Texture texture;
public:
	 void render();
	 int isHit();
	 void collide();
	 void update();
	 virtual std::string dump(std::string const& indent) const;
private:

};