//
// Created by Andrey Stepanov on 17.04.2024.
//

#ifndef CLIENT_TEXTBOX_H
#define CLIENT_TEXTBOX_H

#include "SFML/Graphics.hpp"
#include "sstream"
#include "Reader.h"
#include "locale"
#include <codecvt>
#include <SFML/System/Utf.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
    Textbox();
    Textbox(int size, sf::Color color, bool selected);

    void setFont(sf::Font &font);
    void setPosition(sf::Vector2f pos);
    void setLimit(bool Tof);
    void setLimit(bool Tof, int lim);
    void setSelected(bool sel);

    std::string getText();
    void clear();
    void drawTo(sf::RenderWindow *window);
    void typedOn(sf::Event input);
private:
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit{};

    void inputLogic(unsigned int charTyped);
    void deleteLastChar();
};


#endif //CLIENT_TEXTBOX_H
