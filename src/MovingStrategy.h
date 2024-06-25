#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

struct res
{
    bool dir[4];
};

class MovingStrategy
{
public:
    virtual ~MovingStrategy() = default;
    virtual struct res nextPosition(sf::Vector2f position, sf::Vector2f pposition) const = 0;
};

class Context
{
private:
    std::unique_ptr<MovingStrategy> strategy_;

public:
    explicit Context(std::unique_ptr<MovingStrategy>&& strategy = {});

    void set_strategy(std::unique_ptr<MovingStrategy>&& strategy);

    struct res calculateDirection(sf::Vector2f position, sf::Vector2f pposition) const;
};

class FatStrategy : public MovingStrategy
{
public:
    struct res nextPosition(sf::Vector2f position, sf::Vector2f pposition) const override;
};
class AngryStrategy : public MovingStrategy
{
public:
    struct res nextPosition(sf::Vector2f position, sf::Vector2f pposition) const override;
};
class DumbStrategy : public MovingStrategy
{
public:
    struct res nextPosition(sf::Vector2f position, sf::Vector2f pposition) const override;
};
class CrazyStrategy : public MovingStrategy
{
public:
    struct res nextPosition(sf::Vector2f position, sf::Vector2f pposition) const override;
};