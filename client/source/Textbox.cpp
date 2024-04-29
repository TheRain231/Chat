//
// Created by Andrey Stepanov on 17.04.2024.
//

#include "Textbox.h"

Textbox::Textbox() = default;

Textbox::Textbox(int size, sf::Color color, bool selected) {
    textbox.setCharacterSize(size);
    textbox.setFillColor(color);
    isSelected = selected;
    if (isSelected) {
        textbox.setString("_");
    } else {
        textbox.setString("");
    }
}

void Textbox::inputLogic(unsigned int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        text <<  static_cast<char>(charTyped);
    } else if (charTyped == DELETE_KEY) {
        if (!text.str().empty()) {
            deleteLastChar();
        }
    }
    textbox.setString(text.str() + "_");
}

void Textbox::deleteLastChar() {
    std::string t = text.str();
    std::string newT;
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    text.str("");
    text << newT;
    textbox.setString(text.str());
}

void Textbox::setFont(sf::Font &font) {
    textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos) {
    textbox.setPosition(pos);
}

void Textbox::setLimit(bool Tof) {
    hasLimit = Tof;
}

void Textbox::setLimit(bool Tof, int lim) {
    hasLimit = Tof;
    limit = lim - 1;
}

void Textbox::setSelected(bool sel) {
    isSelected = sel;
    if (!isSelected) {
        std::string t = text.str();
        std::string newT;
        for (int i = 0; i < t.length(); i++) {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

std::string Textbox::getText() {
    return text.str();
}

void Textbox::drawTo(sf::RenderWindow *window) {
    window->draw(textbox);
}

void Textbox::typedOn(sf::Event input) {
    if(isSelected){
        unsigned int charTyped = input.text.unicode;
        if(hasLimit){
            if(text.str().length() <= limit){
                inputLogic(charTyped);
            }
            else if(text.str().length() > limit && charTyped == DELETE_KEY){
                deleteLastChar();
            }
        } else {
            inputLogic(charTyped);
        }
    }
}

void Textbox::clear() {
    textbox.setString("_");
    text.str("");
}
