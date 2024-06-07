#include "Monster.h"
#include <sstream>

using namespace std;

Monster::Monster(pugi::xml_node node)
    : LivingEntity(node)
{}

std::string Monster::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent <<
        "Monster " << LivingEntity::dump(indent) << endl;
    return oss.str();
}