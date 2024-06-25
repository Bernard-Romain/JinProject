#include "MovingStrategy.h"

Context::Context(std::unique_ptr<MovingStrategy>&& strategy) : strategy_(std::move(strategy))
{
}

void Context::set_strategy(std::unique_ptr<MovingStrategy>&& strategy)
{
    strategy_ = std::move(strategy);
}

struct res Context::calculateDirection(sf::Vector2f position, sf::Vector2f pposition) const
{
    struct res result;
    if (strategy_) {
        result = strategy_->nextPosition(position, pposition);
    }
    return result;
}

struct res FatStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    struct res result;
    result.dir[0] = false;
    result.dir[1] = false;
    result.dir[2] = false;
    result.dir[3] = false;

    return result;
}

struct res AngryStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    struct res result;
    if (position.y < pposition.x)
    {
        result.dir[0] = false;
        result.dir[2] = true;
    }
    if (position.y > pposition.y)
    {
        result.dir[2] = false;
        result.dir[0] = true;
    }
    if (position.y == pposition.y)
    {
        result.dir[2] = false;
        result.dir[0] = false;
    }
    if (position.x < pposition.x)
    {
        result.dir[3] = false;
        result.dir[1] = true;
    }
    if (position.x > pposition.x)
    {
        result.dir[1] = false;
        result.dir[3] = true;
    }
    if (position.x == pposition.x)
    {
        result.dir[1] = false;
        result.dir[3] = false;
    }

    return result;
}

struct res DumbStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    struct res result;
    if (position.y <= 300 && position.x >= 200)
    {
        result.dir[3] = true;
        result.dir[1] = false;
        result.dir[2] = false;
        result.dir[0] = false;
    }
    if (position.y >= 700 && position.x <= 1600)
    {
        result.dir[1] = true;
        result.dir[3] = false;
        result.dir[2] = false;
        result.dir[0] = false;
    }
    if (position.x <= 200 && position.y <= 700)
    {
        result.dir[2] = true;
        result.dir[1] = false;
        result.dir[3] = false;
        result.dir[0] = false;
    }
    if (position.x >= 1600 && position.y >= 300)
    {
        result.dir[0] = true;
        result.dir[1] = false;
        result.dir[2] = false;
        result.dir[3] = false;
    }

    return result;
}

struct res CrazyStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    struct res result;
    int dir = rand() % 4;
    switch (dir)
    {
    case(0):
        result.dir[0] = true;
        result.dir[2] = false;
        break;
    case(1):
        result.dir[2] = true;
        result.dir[0] = false;
        break;
    case(2):
        result.dir[1] = true;
        result.dir[3] = false;
        break;
    case(3):
        result.dir[3] = true;
        result.dir[1] = false;
        break;
    }

    return result;
}
