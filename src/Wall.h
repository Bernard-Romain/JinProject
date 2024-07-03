#pragma once
#include "Entity.h"
#include <iostream>

class Wall : public Entity {
public:
	explicit(false) Wall(pugi::xml_node node);
	std::string dump(std::string const& indent) const override;

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
	int x_size;
	int y_size;
};