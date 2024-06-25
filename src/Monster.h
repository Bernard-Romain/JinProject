#pragma once
#include "LivingEntity.h"

class Room;
class Player;

/*Les monstres peuvent être de pluiseur type :
* Le Fat ne bouge pas
* Le Angry suit le joueur
* Le Crazy se déplace de manière aléatoire
* Le Dumb fait une ronde dans la pièce
*/
enum class Monster_Type {
	Fat,
	Angry,
	Crazy,
	Dumb
};

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
	Monster_Type type;
};