//
// Created by Андрей Степанов on 29.04.2024.
//

#include "Bubble.h"

Bubble::Bubble(const sf::String& txt, owner own, float y) {
    text.setCharacterSize(15);
    text.setString(txt);
    text.setFont(Reader::arial);
    text.setFillColor(sf::Color::Black);
    ownership = own;
    bubble.setSize({text.getLocalBounds().width + 20, 35});
    bubble.setRadius(10);
    switch (ownership) {
        case me:
            bubble.setPosition(1000 - bubble.getLocalBounds().width - 10, y);
            bubble.setFillColor(sf::Color(231, 254, 204, 255));
            break;
        case mynigga:
            bubble.setPosition(310, y);
            break;
    }
    text.setPosition(bubble.getPosition().x + 10, y + 10);
}

void Bubble::drawTo(sf::RenderWindow *window) {
    window->draw(bubble);
    window->draw(text);
}

void Bubble::moveUp(const float y) {
    bubble.move({0, y});
    text.move({0, y});
}

float Bubble::getY() {
    return bubble.getPosition().y;
}
