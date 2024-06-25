#pragma once
#include "LivingEntity.h"
#include "MovingStrategy.h"

class Room;
class Player;
class Context;


class Monster : public LivingEntity {
public:
	explicit(false) Monster(pugi::xml_node node, Room* room, Player* player);
	std::string dump(std::string const& indent) const override;
	void move() override;
	void update(std::vector<std::unique_ptr<Entity>> const& entities) override;

	//V2 Collisions
	void collide_with(Entity& other) override {
		other.collide_with(*this);
	};

	void collide_with(Wall& other) override;
	void collide_with(Door& other) override {};
	void collide_with(Player& other) override {};
	void collide_with(Monster& other) override {};
	void collide_with(Projectile& other) override;
private :
	Room* room;
	Player* player;
	Context context;
};