//
// Created by Андрей Степанов on 29.04.2024.
//

#ifndef CHAT_BUBBLE_H
#define CHAT_BUBBLE_H

#include "SFML/Graphics.hpp"
#include "RoundedRect.h"
#include "Reader.h"


class Bubble {
public:
    enum owner{
        me, mynigga
    };

    Bubble(const sf::String& txt, owner own, float y);

    void drawTo(sf::RenderWindow *window);
    void moveUp();
private:
    RoundRect bubble;
    sf::Text text;
    owner ownership;
};


#endif //CHAT_BUBBLE_H
