#pragma once
#include "LivingEntity.h"
#include "Projectile.h"
#include <functional>

class Game;

class Player : public LivingEntity {

public:
	explicit(false) Player(pugi::xml_node node);

	std::string dump(std::string const& indent) const override;
	void manageInput(sf::Keyboard::Key input, bool active);
	void shoot(sf::Vector2i mousePosition);

	void render(sf::RenderWindow* mWindow) const override;
	void update(std::vector<std::unique_ptr<Entity>> const &entities) override;

	using CollisionCallback = std::function<void(Entity*)>;
	using KillCallback = std::function<void(int)>;
	void setCollisionCallback(Game* instance, CollisionCallback const& callback) { callbackInstance = instance;  collisionCallback = callback; }
	void setKillCallback(Game* instance, KillCallback const& callback) { callbackInstance = instance; killCallback = callback; }

	void reversePosition(); //TODO : Comprendre pourquoi ca marche pas

	void move(std::vector<std::unique_ptr<Entity>> const& entities) override;

private:
	std::vector<std::unique_ptr<Projectile>> activeProjectiles;
	std::vector<std::unique_ptr<Projectile>> inactiveProjectiles;

	void handleCollision(Entity* const entity);

	CollisionCallback collisionCallback = nullptr;
	KillCallback killCallback = nullptr;
	Game* callbackInstance = nullptr;
};