#pragma once
#include "LivingEntity.h"
#include "Projectile.h"

class Game;

class Player : public LivingEntity {
public:
	Player(pugi::xml_node node);
	std::string dump(std::string const& indent) const;
	void manageInput(sf::Keyboard::Key input, bool active);
	void shoot(sf::Vector2i mousePosition);

	void render(sf::RenderWindow* mWindow) const;
	void update(std::vector<std::unique_ptr<Entity>> const &entities);

	typedef void (Game::*CollisionCallback)(Entity*);
	typedef void (Game::*KillCallback)(int);
	void setCollisionCallback(Game* instance, CollisionCallback callback) { callbackInstance = instance;  collisionCallback = callback; }
	void setKillCallback(Game* instance, KillCallback callback) {
		callbackInstance = instance;
		killCallback = callback;
	}


	void move(std::vector<std::unique_ptr<Entity>> const& entities);

private:
	std::vector<std::unique_ptr<Projectile>> activeProjectiles;
	std::vector<std::unique_ptr<Projectile>> inactiveProjectiles;

	void handleCollision(Entity* const entity);
	CollisionCallback collisionCallback;
	KillCallback killCallback;
	Game* callbackInstance;
};