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

void Player::manageInput(sf::Keyboard::Key input, bool active)
{
    if (active)
    {
        switch (input)
        {
        case sf::Keyboard::Key::Z:
            direction += sf::Vector2f(0, -1);
            break;
        case sf::Keyboard::Key::Q:
            direction += sf::Vector2f(-1, 0);
            break;
        case sf::Keyboard::Key::S:
            direction += sf::Vector2f(0, 1);
            break;
        case sf::Keyboard::Key::D:
            direction += sf::Vector2f(1, 0);
            break;
        default :
            break;
        }
    }
    else
    {
        switch (input)
        {
        case sf::Keyboard::Key::Z:
            direction += sf::Vector2f(0, 1);
            break;
        case sf::Keyboard::Key::Q:
            direction += sf::Vector2f(1, 0);
            break;
        case sf::Keyboard::Key::S:
            direction += sf::Vector2f(0, -1);
            break;
        case sf::Keyboard::Key::D:
            direction += sf::Vector2f(-1, 0);
            break;
        default:
            break;
        }
    }
}
