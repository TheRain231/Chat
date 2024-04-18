//
// Created by Андрей Степанов on 18.04.2024.
//

#include "Button.h"

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color backgorundColor, sf::Color foregroundColor) {
    text.setString(t);
    text.setFillColor(foregroundColor);
    text.setCharacterSize(charSize);

    button.setSize(size);
    button.setFillColor(backgorundColor);
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
}

void Button::setBackgroundColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);
    float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void Button::drawTo(sf::RenderWindow *window) {
    window->draw(button);
    window->draw(text);
}

bool Button::isMouseOver(sf::RenderWindow *window) {
    int mouseX = sf::Mouse::getPosition(*window).x;
    int mouseY = sf::Mouse::getPosition(*window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnXPosWidth = btnPosX + button.getLocalBounds().width;
    float btnYPosHeight = btnPosY + button.getLocalBounds().height;

    if (mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY){
        return true;
    }
    return false;
}

