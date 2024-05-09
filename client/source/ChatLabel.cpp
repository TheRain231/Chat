//
// Created by Андрей Степанов on 06.05.2024.
//

#include "ChatLabel.h"

ChatLabel::ChatLabel(sf::Vector2f pos, sf::String label, sf::String lastMessage) {
    this->base.setPosition(pos);
    this->base.setSize({300, 60});
    this->outline.setPosition({pos.x + 10, pos.y + 60});
    this->outline.setSize({280, 1});
    this->outline.setFillColor(sf::Color(0, 0, 0, 40));

    this->label.setFont(Reader::arial);
    this->label.setFillColor(sf::Color::Black);
    this->label.setCharacterSize(20);
    this->label.setString(label);
    this->label.setPosition(pos.x + 10, pos.y + 10);

    this->lastMessage.setFont(Reader::arial);
    this->lastMessage.setFillColor(sf::Color::Black);
    this->lastMessage.setCharacterSize(15);
    this->lastMessage.setString(lastMessage);
    this->lastMessage.setPosition(pos.x + 10, pos.y + 35);

    this->button = new Button({300, 60});
    this->button->setPosition(pos);
    void func();
    this->button->setFunction(func);
}

void func(){

}

void ChatLabel::drawTo(sf::RenderWindow *target) {
    target->draw(base);
    target->draw(outline);
    target->draw(label);
    target->draw(lastMessage);
}

void ChatLabel::setSelected(bool sel) {
    if (isSelected != sel){
        if (sel){
            this->base.setFillColor(sf::Color(93, 143, 194, 255));
            this->label.setFillColor(sf::Color::White);
            this->lastMessage.setFillColor(sf::Color::White);
        }
        else {
            this->base.setFillColor(sf::Color::Transparent);
            this->label.setFillColor(sf::Color::Black);
            this->lastMessage.setFillColor(sf::Color::Black);
        }
        isSelected = sel;
    }
}

void ChatLabel::doFunc(sf::RenderWindow* target) {
    if (button->isMouseOver(target)) {
        button->doFunction();
    }
}
