#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Constants.h"
#include "include/Enemy.h"
#include "include/Math.h"
#include "include/Game.h"

Enemy::Enemy(sf::Vector2f position, Game *game)
{
    this->game = game;
    this->player = game->getPlayer();
    this->position = position;
    this->hitbox = sf::RectangleShape({40, 40});
}

Enemy::~Enemy()
{
}

void Enemy::update(double deltaTime)
{
    // Moves projectile by the same distance every frame in direction given by normalized vector.
    sf::Vector2f direction = player->getPosition() + sf::Vector2f(20, 20) + game->getCamera()->getOffset() - position;
    direction = normalize(direction);
    position += sf::Vector2f(direction.x * deltaTime * 100 * speed, direction.y * deltaTime * 100 * speed);
}

void Enemy::draw()
{
    sf::CircleShape shapes(20);
    shapes.setFillColor(sf::Color(255, 255, 255));
    shapes.setPosition({position.x - 2 * game->getCamera()->getOffset().x - 20, position.y - 2 * game->getCamera()->getOffset().y - 20});
    game->getWindow()->draw(shapes);

    // Draws hitbox.
    // sf::RectangleShape hitboxShape(hitbox.getSize());
    // hitboxShape.setPosition(position);
    // game->getWindow()->draw(hitboxShape);
}

sf::Vector2f Enemy::getPosition()
{
    return position;
}

sf::Vector2f Enemy::getHitboxPosition()
{
    return position - sf::Vector2f(20, 20);
}

sf::Vector2f Enemy::getHitboxSize()
{
    return hitbox.getSize();
}

bool Enemy::dealDamage(int damage)
{
    health -= damage;
    return health < 0;
}