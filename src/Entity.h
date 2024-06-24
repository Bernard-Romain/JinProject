#pragma once
#include <string>
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
 
class Player;
class Monster;
class Projectile;
class Door;
class Wall;

class Entity
{
protected:
	std::string label; //Permet de définir le type d'entité (joueur, monstre, porte,..)
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

	//V2 for collisions
	virtual void collide_with(Entity& other) = 0;

	virtual void collide_with(Wall& other) = 0;
	virtual void collide_with(Door& other) = 0;
	virtual void collide_with(Player& other) = 0;
	virtual void collide_with(Monster& other) = 0;
	virtual void collide_with(Projectile& other) = 0;
};