#include "Player.h"
#include <sstream>
#include <iostream>
#include "Game.h"

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
    move(entities);

    for (auto it = activeProjectiles.begin(); it != activeProjectiles.end();) {
        (*it)->update(entities);
        (*it)->isColliding = false;
        for (int i = 0; i < entities.size(); i++)
        {
            if ((*it)->collide(*entities[i])) {
                (*it)->isColliding = true;
                if (entities[i].get()->getLabel() == "Monster"sv) (callbackInstance->*killCallback)(i);
            }
        }
        if ((*it)->isColliding) {
            inactiveProjectiles.push_back(std::move(*it));
            it = activeProjectiles.erase(it);
        }
        else
            ++it;
    }

}

void Player::handleCollision(Entity* const entity) {

    if (entity->getLabel() == "Door"sv) {
        cout << "a\n";
        (callbackInstance->*collisionCallback)(entity);
    }

}

void Player::move(std::vector<std::unique_ptr<Entity>> const& entities)
{
    sf::Vector2f memo = position;
    direction = sf::Vector2f();
    if (isMovingUp)
        direction += sf::Vector2f(0, 1);
    if (isMovingDown)
        direction += sf::Vector2f(0, -1);
    if (isMovingLeft)
        direction += sf::Vector2f(1, 0);
    if (isMovingRight)
        direction += sf::Vector2f(-1, 0);

    position += direction * speed;
    sprite.setPosition(position);

    isColliding = false;
    for (int i = 0; i < entities.size(); i++)
    {
        if (collide(*entities[i])) {
            isColliding = true;
            this->handleCollision(entities[i].get());
        }
    }
    if (isColliding) {
        position = memo;
        sprite.setPosition(memo);
    }
}