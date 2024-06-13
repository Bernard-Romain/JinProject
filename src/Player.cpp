#include "Player.h"
#include <sstream>

using namespace std;

Player::Player(pugi::xml_node node)
    : LivingEntity(node)
{
    sprite.setScale(sf::Vector2f(0.35, 0.35));

    for (int i = 0; i < 10; i ++ ) {
        inactiveProjectiles.push_back(make_unique<Projectile>(position, (string)"Tear", 8, sf::Vector2f(0, 0), 1));
    }
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
    case sf::Event::MouseButtonPressed:
        printf("aaa\n");
    default :
        break;
    }
}

void Player::shoot(sf::Vector2i mousePosition) {
    if (!inactiveProjectiles.empty()) {
        activeProjectiles.push_back(std::move(inactiveProjectiles.back()));
        inactiveProjectiles.pop_back();

        sf::Vector2f direction = (sf::Vector2f)mousePosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f normalise = direction;
        if (length != 0) normalise = sf::Vector2f(direction.x / length, direction.y / length);
        
        activeProjectiles.back()->setDirection(normalise);
        activeProjectiles.back()->setPosition(position);
    }
}

void Player::render(sf::RenderWindow* mWindow) const {
    mWindow->draw(sprite);
    for (auto const& projectile : activeProjectiles) {
        mWindow->draw(projectile->getSprite());
    }
}

void Player::update(std::vector<std::unique_ptr<Entity>> const &entities)
{
    isColliding = false;
    for (int i = 0; i < entities.size(); i++)
    {
        if (collide(*entities[i]))
            isColliding = true;
    }
    if (isColliding)
        position = lastPosition;
    else
        move();
    sprite.setPosition(position);
    for (auto const& projectile : activeProjectiles) {
        projectile->update(entities);
    }

}