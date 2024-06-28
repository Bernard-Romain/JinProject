#include "Monster.h"
#include <sstream>
#include <iostream>
#include "Room.h"
#include "Player.h"

using namespace std;

Monster::Monster(pugi::xml_node node, Room* room, Player* player)
    : LivingEntity(node)
    , room(room)
    , player(player)
{
    string stype = node.attribute("type").as_string();
    if (stype == "Fat")
        context.set_strategy(std::make_unique<FatStrategy>());
    else if (stype == "Angry")
        context.set_strategy(std::make_unique<AngryStrategy>());
    else if (stype == "Dumb")
        context.set_strategy(std::make_unique<DumbStrategy>());
    else if (stype == "Crazy")
        context.set_strategy(std::make_unique<CrazyStrategy>());

    isMovingLeft = true;

}

std::string Monster::dump(std::string const& indent) const {

    ostringstream oss;
    oss << indent <<
        "Monster " << LivingEntity::dump(indent) << endl;
    return oss.str();
}

void Monster::collide_with(Projectile& other) {
    room->killMonster(this);
}

void Monster::move()
{
    sf::Vector2f pposition = player->getPosition();
    lastPosition = position;
    position += context.updatePosition(position, pposition, speed);
    cout << "This monster : LastPosition : " << lastPosition.x << "," << lastPosition.y << "and now " << position.x << endl;
}

void Monster::update(std::vector<std::unique_ptr<Entity>> const& entities)
{
    move();
    sprite.setPosition(position);
}

void Monster::collide_with(Wall& other) {
    if (position.y < lastPosition.y)
    {
        isMovingUp = false;
        isMovingDown = true;
    }
    if (position.y > lastPosition.y)
    {
        isMovingDown = false;
        isMovingUp = true;
    }
    if (position.x < lastPosition.x)
    {
        isMovingLeft = false;
        isMovingRight = true;
    }
    if (position.x > lastPosition.x)
    {
        isMovingRight = false;
        isMovingLeft = true;
    }


    position = lastPosition;
    sprite.setPosition(lastPosition);
}