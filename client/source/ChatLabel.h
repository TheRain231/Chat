//
// Created by Андрей Степанов on 06.05.2024.
//
#ifndef CHAT_CHATLABEL_H
#define CHAT_CHATLABEL_H

#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Reader.h"

class ChatLabel {
public:
    ChatLabel(sf::Vector2f pos, sf::String label, sf::String lastMessage);
    void drawTo(sf::RenderWindow *target);

    void setSelected(bool sel);
    void doFunc(sf::RenderWindow* target);
    static void move(float delta);

    static std::vector<ChatLabel*> chatLabels;
private:
    sf::RectangleShape outline;
    sf::RectangleShape base;
    sf::Text label;
    sf::Text lastMessage;
    Button *button;
    bool isSelected = false;

    static void moveUp(float delta);
};


#endif //CHAT_CHATLABEL_H
