//
// Created by Андрей Степанов on 30.04.2024.
//

#ifndef CHAT_ROUNDEDRECT_H
#define CHAT_ROUNDEDRECT_H

#include <SFML/Graphics.hpp>

class RoundedRect : sf::Shape{
public:
    RoundedRect(sf::Vector2f size, sf::Vector2f pos, float rad, sf::Color color);
private:
    sf::Shape* rrect;
    sf::Vector2f size;
    sf::Vector2f pos;
    float radius;
};

#endif //CHAT_ROUNDEDRECT_H
