#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class MovingStrategy
{
public:
    virtual ~MovingStrategy() = default;
    virtual sf::Vector2f nextPosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const = 0;
};

class Context
{
private:
    std::unique_ptr<MovingStrategy> strategy = nullptr;

public:
    explicit Context(std::unique_ptr<MovingStrategy>&& strategy = {});

    void set_strategy(std::unique_ptr<MovingStrategy>&& strategy);

    sf::Vector2f updatePosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const;
};

class FatStrategy : public MovingStrategy
{
public:
    sf::Vector2f nextPosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const override;
};
class AngryStrategy : public MovingStrategy
{
public:
    sf::Vector2f nextPosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const override;
};
class DumbStrategy : public MovingStrategy
{
public:
    sf::Vector2f nextPosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const override;
};
class CrazyStrategy : public MovingStrategy
{
public:
    sf::Vector2f nextPosition(sf::Vector2f position, sf::Vector2f pposition, float speed) const override;
};