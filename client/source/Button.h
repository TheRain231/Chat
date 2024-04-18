//
// Created by Андрей Степанов on 18.04.2024.
//

#ifndef CLIENT_BUTTON_H
#define CLIENT_BUTTON_H

#include "SFML/Graphics.hpp"
#include "iostream"

class Button {
public:
    Button();
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color backgorundColor, sf::Color foregroundColor);

    void setFont(sf::Font &font);
    void setBackgroundColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
    void drawTo(sf::RenderWindow *window);
    bool isMouseOver(sf::RenderWindow *window);
private:
    sf::RectangleShape button;
    sf::Text text;
};


#endif //CLIENT_BUTTON_H
