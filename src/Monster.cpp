#include "Monster.h"
#include <sstream>
#include "Room.h"

using namespace std;

Monster::Monster(pugi::xml_node node, Room* room)
    : LivingEntity(node)
    , room(room)
{}

std::string Monster::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent <<
        "Monster " << LivingEntity::dump(indent) << endl;
    return oss.str();
}

void Monster::collide_with(Projectile& other) {
    room->killMonster(this);
}