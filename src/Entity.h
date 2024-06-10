#pragma once
#include <string>
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	explicit(false) Entity(pugi::xml_node node);

	 virtual void render(sf::RenderWindow* mWindow) const = 0;
	 int isHit();
	 void collide();
	 void update();
	 virtual std::string dump(std::string const& indent) const;
private:

};