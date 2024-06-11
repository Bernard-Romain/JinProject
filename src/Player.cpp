#include "Player.h"
#include <sstream>

using namespace std;

Player::Player(pugi::xml_node node)
    : LivingEntity(node)
{
    sprite.setScale(sf::Vector2f(0.35, 0.35));
}

std::string Player::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent <<
        "Player " << LivingEntity::dump(indent) << endl;
    return oss.str();
}

void Player::manageInput(sf::Keyboard::Key input, bool active)
{
    switch (input)
    {
    case sf::Keyboard::Key::Z:
        isMovingUp = !active;
        break;
    case sf::Keyboard::Key::Q:
        isMovingLeft = !active;
        break;
    case sf::Keyboard::Key::S:
        isMovingDown = !active;
        break;
    case sf::Keyboard::Key::D:
        isMovingRight = !active;
        break;
    default :
        break;
    }
}

