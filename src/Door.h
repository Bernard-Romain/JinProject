#pragma once
#include "Room.h"

class Door : public Entity {
public:
	explicit(false) Door(pugi::xml_node node, Game* game);

	std::string getDestination() const { return destination; }
	void setGame(Game* game) { this->game = game; };

	//V2 Collisions
	void collide_with(Entity& other) override {
		other.collide_with(*this);
	};

	void collide_with(Wall& other) override {};
	void collide_with(Door& other) override {};
	void collide_with(Player& other) override;
	void collide_with(Monster& other) override {};
	void collide_with(Projectile& other) override {};
private:
	std::string destination; //Contient le nom de la room à laquelle emmène cette porte
	Game* game;

};