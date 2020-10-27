#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Collider.h"
#include <iostream>
using namespace std;

class bullet
{
public:
    bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f pos);
    ~bullet();
    void update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    bool isAvaliable();
    void attack(sf::Vector2f pos);
    void del();

    sf::Vector2f GetPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }

private:
    Animation animation;
    float speed;
    sf::RectangleShape body;
    unsigned int row;
    sf::Vector2f velocity;
    bool isAva = true;
};
