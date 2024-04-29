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
        text += charTyped;
    } else if (charTyped == DELETE_KEY) {
        if (text.getSize() > 0) {
            deleteLastChar();
        }
    }
    textbox.setString(text + "_");
}

void Textbox::deleteLastChar() {
    sf::String newT;
    for (int i = 0; i < text.getSize() - 1; i++) {
        newT += text[i];
    }
    text = "";
    text += newT;
    textbox.setString(text);
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
        sf::String t = text;
        sf::String newT;
        for (int i = 0; i < t.getSize(); i++) {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

std::string Textbox::getText() {
    return text;
}

void Textbox::drawTo(sf::RenderWindow *window) {
    window->draw(textbox);
}

void Textbox::typedOn(sf::Event input) {
    if(isSelected){
        unsigned int charTyped = input.text.unicode;
        std::cout << charTyped << ' ';
        if(hasLimit){
            if(text.getSize() <= limit){
                inputLogic(charTyped);
            }
            else if(text.getSize() > limit && charTyped == DELETE_KEY){
                deleteLastChar();
            }
        }
        else {
            inputLogic(charTyped);
        }
    }
}

void Textbox::clear() {
    textbox.setString("_");
    text = "";
}
