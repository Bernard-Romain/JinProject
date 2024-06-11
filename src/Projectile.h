#include "MovingEntity.h"

class Projectile : public MovingEntity {
public:
	Projectile(sf::Vector2f position, std::string spriteLabel, float speed, sf::Vector2f direction, int damage = 1);

	void setDirection(sf::Vector2f direction) { this->direction = direction; }
	void setPosition(sf::Vector2f position) { this->position = position; }
	sf::Sprite getSprite() { return sprite; }

	void move();
	void update() override;
private:
	int damage;
};