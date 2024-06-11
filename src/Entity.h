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

	 void render(sf::RenderWindow* mWindow) const;
	 int isHit();
	 void collide();
	 virtual void update();
	 virtual std::string dump(std::string const& indent) const;
private:

};