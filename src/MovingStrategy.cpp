#include "MovingStrategy.h"

Context::Context(std::unique_ptr<MovingStrategy>&& strategy) : strategy_(std::move(strategy))
{
}

void Context::set_strategy(std::unique_ptr<MovingStrategy>&& strategy)
{
    strategy_ = std::move(strategy);
}

bool* Context::calculateDirection(sf::Vector2f position, sf::Vector2f pposition) const
{
    if (strategy_) {
        return strategy_->nextPosition(position, pposition);
    }
    else {
        return 0;
    }
}

bool* FatStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    static bool res[4];
    res[0] = false;
    res[1] = false;
    res[2] = false;
    res[3] = false;

    return res;
}

bool* AngryStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    static bool res[4];
    if (position.y < pposition.x)
    {
        res[0] = false;
        res[2] = true;
    }
    if (position.y > pposition.y)
    {
        res[2] = false;
        res[0] = true;
    }
    if (position.y == pposition.y)
    {
        res[2] = false;
        res[0] = false;
    }
    if (position.x < pposition.x)
    {
        res[3] = false;
        res[1] = true;
    }
    if (position.x > pposition.x)
    {
        res[1] = false;
        res[3] = true;
    }
    if (position.x == pposition.x)
    {
        res[1] = false;
        res[3] = false;
    }

    return res;
}

bool* DumbStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    static bool res[4];
    if (position.y < 300 && position.x > 500)
    {
        res[0] = false;
        res[3] = true;
    }
    if (position.y > 700 && position.x < 500)
    {
        res[2] = false;
        res[1] = true;
    }
    if (position.x < 200 && position.y < 500)
    {
        res[3] = false;
        res[2] = true;
    }
    if (position.x > 1600 && position.y > 500)
    {
        res[1] = false;
        res[0] = true;
    }

    return res;
}

bool* CrazyStrategy::nextPosition(sf::Vector2f position, sf::Vector2f pposition) const
{
    static bool res[4];
    int dir = rand() % 4;
    switch (dir)
    {
    case(0):
        res[0] = true;
        res[2] = false;
        break;
    case(1):
        res[2] = true;
        res[0] = false;
        break;
    case(2):
        res[1] = true;
        res[3] = false;
        break;
    case(3):
        res[3] = true;
        res[1] = false;
        break;
    }

    return res;
}
