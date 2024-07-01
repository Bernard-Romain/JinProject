#pragma once
#include "LivingEntity.h"
#include <iostream>

class Game;

class Player : public LivingEntity {

public:
	explicit(false) Player(pugi::xml_node node, Game* game);

	std::string dump(std::string const& indent) const override;
	void manageInput(sf::Keyboard::Key input, bool active); //Appel� lorsque l'on appuie sur une touche du clavier
	void shoot(sf::Vector2i mousePosition); //Appel� lors du clic gauche : g�er le tir de projectile

	void render(sf::RenderWindow* mWindow) const override;
	void update(std::vector<std::unique_ptr<Entity>> const &entities) override;

	void move() override;
	void desactiveProjectile(Projectile* projectile);

	//V2 Collisions
	void collide_with(Entity& other) override {
		other.collide_with(*this);
	};

	void collide_with(Wall& other) override;
	void collide_with(Door& other) override;
	void collide_with(Player& other) override {};
	void collide_with(Monster& other) override;
	void collide_with(Projectile& other) override {};

	sf::Vector2f getPosition() const { return position; };

private:

	/*Les projectiles sont g�r�s par une pool d'instances:
	* 10 projectiles sont instanci�s lors de la cr�ation du personnage et sont mis dans inactiveProjectiles.
	* A chaque tir, un projectile inactif est d�plac� dans activeProjectile (et fait son r�le de projectile)
	* Lors de la fin de vie du projectile, l'instance n'est pas d�truite mais retourne dans le vecteur inactiveProjectile.
	*/
	std::vector<std::unique_ptr<Projectile>> activeProjectiles;
	std::vector<std::unique_ptr<Projectile>> inactiveProjectiles;

	std::vector<Projectile*> toRemoveProjectiles;
	void removeProjectile();

	Game* game;
};