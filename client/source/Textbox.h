//
// Created by Andrey Stepanov on 17.04.2024.
//

#ifndef CLIENT_TEXTBOX_H
#define CLIENT_TEXTBOX_H

#include "SFML/Graphics.hpp"
#include "sstream"
#include "Reader.h"
#include <codecvt>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
    Textbox();
    Textbox(int size, sf::Color color);

    void setFont(sf::Font &font);
    void setPosition(sf::Vector2f pos);
    void setLimit(bool Tof);
    void setLimit(bool Tof, float lim);
    void setSelected(bool sel);
    void setStars(bool sel);
    void setHint(const sf::String& hint);
    bool isSelected() const;

    std::string getText();
    sf::String getSFText();
    void drawTo(sf::RenderWindow *window);
    void clear();
    void typedOn(sf::Event input);

    float getWidth();
private:
    sf::Text textbox;
    sf::String text;
    sf::Color color;
    bool hasLimit = false;
    bool selected = true;
    bool isStars = false;
    float limit;

    void inputLogic(unsigned int charTyped);
    void deleteLastChar();
};


#endif //CLIENT_TEXTBOX_H
