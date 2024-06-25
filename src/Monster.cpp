#include "Monster.h"
#include <sstream>
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
        type = Monster_Type::Fat;
    else if (stype == "Angry")
        type = Monster_Type::Angry;
    else if (stype == "Dumb")
        type = Monster_Type::Dumb;
    else if (stype == "Crazy")
        type = Monster_Type::Crazy;

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
    switch (type)
    {
    case(Monster_Type::Fat):
        isMovingDown = false;
        isMovingLeft = false;
        isMovingRight = false;
        isMovingUp = false;
        break;
    case(Monster_Type::Angry):
        if (position.y < pposition.x)
        {
            isMovingUp = false;
            isMovingDown = true;
        }
        if (position.y > pposition.y)
        {
            isMovingDown = false;
            isMovingUp = true;
        }
        if (position.x < pposition.x)
        {
            isMovingLeft = false;
            isMovingRight = true;
        }
        if (position.x > pposition.x)
        {
            isMovingRight = false;
            isMovingLeft = true;
        }
        break;
    case(Monster_Type::Dumb):
        if (position.y < 200 && position.x > 500)
        {
            isMovingUp = false;
            isMovingLeft = true;
        }
        if (position.y > 700 && position.x < 500)
        {
            isMovingDown = false;
            isMovingRight = true;
        }
        if (position.x < 200 && position.y < 500)
        {
            isMovingLeft = false;
            isMovingDown = true;
        }
        if (position.x > 1600 && position.y > 500)
        {
            isMovingRight = false;
            isMovingUp = true;
        }
        break;
    case(Monster_Type::Crazy):
        int dir = rand() % 4;
        switch (dir)
        {
        case(0):
            isMovingUp = true;
            isMovingDown = false;
            break;
        case(1):
            isMovingDown = true;
            isMovingUp = false;
            break;
        case(2):
            isMovingRight = true;
            isMovingLeft = false;
            break;
        case(3):
            isMovingLeft = true;
            isMovingRight = false;
            break;
        }
    }

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