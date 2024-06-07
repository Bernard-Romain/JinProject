#include "Player.h"
#include <sstream>

using namespace std;

Player::Player(pugi::xml_node node)
    : LivingEntity(node)
{}

std::string Player::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent <<
        "Player " << LivingEntity::dump(indent) << endl;
    return oss.str();
}