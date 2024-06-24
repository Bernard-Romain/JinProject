#include "Player.h"
#include <sstream>
#include <iostream>
#include "Game.h"

using namespace std;

Player::Player(pugi::xml_node node)
    : LivingEntity(node)
{
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));

    for (int i = 0; i < 10; i ++ ) {
        inactiveProjectiles.push_back(make_unique<Projectile>(position, (string)"Tear", 25, sf::Vector2f(0, 0), 1));
    }
}

void Player::updatePositionWhenChangingRoom() {

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
        isMovingUp = active;
        break;
    case sf::Keyboard::Key::Q:
        isMovingLeft = active;
        break;
    case sf::Keyboard::Key::S:
        isMovingDown = active;
        break;
    case sf::Keyboard::Key::D:
        isMovingRight = active;
        break;
    default :
        //DONOTHIN
        break;
    }
}

void Player::shoot(sf::Vector2i mousePosition) {
    if (!inactiveProjectiles.empty()) {
        activeProjectiles.push_back(std::move(inactiveProjectiles.back()));
        inactiveProjectiles.pop_back();

        sf::Vector2f direction = (sf::Vector2f)mousePosition - position;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

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
    move();

    //Pour chaque projectile actif, on le fait bouger et on regarde ses collisions
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
    if ((entity->getLabel() == "Monster"sv) || (entity->getLabel() == "Door"sv)) {
        updatePositionWhenChangingRoom();
        (callbackInstance->*collisionCallback)(entity);
    }
}

void Player::move()
{
    lastPosition = position;

    direction = sf::Vector2f();
    if (isMovingUp)
        direction += sf::Vector2f(0, -1);
    if (isMovingDown)
        direction += sf::Vector2f(0, 1);
    if (isMovingLeft)
        direction += sf::Vector2f(-1, 0);
    if (isMovingRight)
        direction += sf::Vector2f(1, 0);

    position += direction * speed;
    sprite.setPosition(position);
}

void Player::collide_with(Wall& other) {
    position = lastPosition;
    sprite.setPosition(lastPosition);
}

void Player::collide_with(Door& other) {
    lastPosition = sf::Vector2f(1000, 500);
    sprite.setPosition(lastPosition);
}

void Player::collide_with(Monster& other) {
    callbackInstance->triggerLoose();
}