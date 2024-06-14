#pragma once
#include <string>
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	std::string label;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	bool isColliding;

public:
	explicit(false) Entity(std::string label, sf::Vector2f position, std::string spriteLabel);
	explicit(false) Entity(pugi::xml_node node);

	 void render(sf::RenderWindow* mWindow) const;
	 int isHit(sf::Sprite other);
	 bool collide(Entity other);
	 virtual void update(std::vector<std::unique_ptr<Entity>> const &entities);
	 virtual std::string dump(std::string const& indent) const;

	 std::string getLabel() { return label; }
private:

};