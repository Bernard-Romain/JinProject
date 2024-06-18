#pragma once
#include "Entity.h"

class MovingEntity : public Entity {
public:
	explicit(false) MovingEntity(std::string const &label, sf::Vector2f const& position, std::string const& spriteLabel, float const& speed, sf::Vector2f const& direction);
	explicit(false) MovingEntity(pugi::xml_node node);

	virtual void move(std::vector<std::unique_ptr<Entity>> const& entities);
	void update(std::vector<std::unique_ptr<Entity>> const &entities) override;
	std::string dump(std::string const& indent) const override;


protected:
	float speed;
	sf::Vector2f direction = sf::Vector2f();
	sf::Vector2f lastPosition = sf::Vector2f();

	//Permet de g�rer le d�placement orthogonal du joueur
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;

	void handleCollision(Entity* const entity) const;
};