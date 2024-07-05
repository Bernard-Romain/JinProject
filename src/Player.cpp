#include "Player.h"
#include "Projectile.h"
#include <sstream>
#include <iostream>
#include "Game.h"

using namespace std;

Player::Player(pugi::xml_node node, Game* game)
    : LivingEntity(node)
    , game(game)
{
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));

    for (int i = 0; i < 10; i ++ ) {
        inactiveProjectiles.push_back(make_unique<Projectile>(position, (string)"Tear", 25, sf::Vector2f(0, 0), 1, this));
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

void Player::desactiveProjectile(Projectile* projectile) {
    toRemoveProjectiles.push_back(projectile);
}

void Player::removeProjectile() {
    for (auto projectile : toRemoveProjectiles) {
        auto it = std::find_if(activeProjectiles.begin(), activeProjectiles.end(),
            [projectile](const std::unique_ptr<Projectile>& p) {
                return p.get() == projectile;
            });

        if (it != activeProjectiles.end()) {
            inactiveProjectiles.push_back(std::move(*it));
            activeProjectiles.erase(it);
        }
        else {
            std::cerr << "Projectile not found in activeProjectiles." << std::endl;
        }
    }
    toRemoveProjectiles.clear();
}

void collideWith(Entity& first, Entity& second) { 
    first.collide_with(second);
}

void Player::update(std::vector<std::unique_ptr<Entity>> const &entities)
{
    move();
    
    //Pour chaque projectile actif, on le fait bouger et on regarde ses collisions
    for (auto& projectile : activeProjectiles) {
        projectile->update(entities);
        for (auto const& entity : entities)
        {
            if (projectile->collide(*entity)) {
                collideWith(*projectile, *entity);
                break;
            }
        }
    }
    removeProjectile();
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
    position = sf::Vector2f(1000, 500);
    sprite.setPosition(position);
}

void Player::collide_with(Monster& other) {
    game->triggerLoss();
}