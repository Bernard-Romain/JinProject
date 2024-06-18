#pragma once
#include <string>
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	std::string label;
	sf::Vector2f position;
	sf::Texture texture = sf::Texture();
	sf::Sprite sprite;

public:
	bool isColliding = false;

	explicit(false) Entity(std::string const &label, sf::Vector2f const &position, std::string const &spriteLabel);
	explicit(false) Entity(pugi::xml_node node);
	virtual ~Entity() = default;
	
	virtual void update(std::vector<std::unique_ptr<Entity>> const& entities) {} ;
	virtual std::string dump(std::string const& indent) const;
	virtual void render(sf::RenderWindow* mWindow) const;

	std::string getLabel() const { return label; }
	bool collide(Entity const& other) const { return sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds()); }

};