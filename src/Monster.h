#pragma once
#include "LivingEntity.h"

class Room;

class Monster : public LivingEntity {
public:
	explicit(false) Monster(pugi::xml_node node, Room* room);
	std::string dump(std::string const& indent) const override;

	//V2 Collisions
	void collide_with(Entity& other) override {
		other.collide_with(*this);
	};

	void collide_with(Wall& other) override {};
	void collide_with(Door& other) override {};
	void collide_with(Player& other) override {};
	void collide_with(Monster& other) override {};
	void collide_with(Projectile& other) override;
private :
	Room* room;
};