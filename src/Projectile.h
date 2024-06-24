#include "MovingEntity.h"

class Projectile : public MovingEntity {
public:
	Projectile(sf::Vector2f position, std::string const& spriteLabel, float speed, sf::Vector2f direction, int damage = 1);

	void setDirection(sf::Vector2f direction) { this->direction = direction; }
	void setPosition(sf::Vector2f position) { this->position = position; }
	sf::Sprite getSprite() const { return sprite; }

	void move(); //TODO : Regler le fait que move de movingEntity prend maitenant des arguments
	void update(std::vector<std::unique_ptr<Entity>> const &entities) override;

	//V2 Collisions
	void collide_with(Entity& other) override {
		other.collide_with(*this);
	};

	void collide_with(Wall& other) override {};
	void collide_with(Door& other) override {};
	void collide_with(Player& other) override {};
	void collide_with(Monster& other) override {};
	void collide_with(Projectile& other) override {};
private:
	int damage;
};