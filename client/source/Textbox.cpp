//
// Created by Andrey Stepanov on 17.04.2024.
//

#include "Textbox.h"
#include "sstream"

Textbox::Textbox() = default;

Textbox::Textbox(int size, sf::Color color) {
    textbox.setCharacterSize(size);
    this->color = color;
    textbox.setFillColor(color);
    textbox.setString("_");
}

void Textbox::inputLogic(unsigned int charTyped) {
    if (textbox.getFillColor() != color){
        textbox.setFillColor(color);
    }
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

void Textbox::setLimit(bool Tof, float lim) {
    hasLimit = Tof;
    limit = lim;
}

void Textbox::setSelected(bool sel) {
    selected = sel;
    if (!selected) {
        sf::String t = text;
        sf::String newT;
        for (int i = 0; i < t.getSize(); i++) {
            newT += t[i];
        }
        textbox.setString(newT);
    } else {
        textbox.setString(text + "_");
    }
}

std::string Textbox::getText() {
    char32_t ch;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string str;
    for (int i = 0; i < text.getSize(); i++) {
        ch = static_cast<char32_t>(text[i]);
        str += converter.to_bytes(ch);
    }
    return str;
}

void Textbox::drawTo(sf::RenderWindow *window) {
    if (isStars && textbox.getFillColor() == color){
        sf::String zvzd;
        for (int i = 0; i < text.getSize(); i++){
            if (text[i] != '_')
                zvzd += "*";
        }
        if (isSelected())
            textbox.setString(zvzd + '_');
        else
            textbox.setString(zvzd);
    }
    window->draw(textbox);
}

void Textbox::typedOn(sf::Event input) {
    if (selected){
        unsigned int charTyped = input.text.unicode;
        if (getWidth() <= limit) {
            inputLogic(charTyped);
        } else if (getWidth() > limit && charTyped == DELETE_KEY) {
            deleteLastChar();
        }
    }
}

void Textbox::clear() {
    textbox.setString("_");
    text.clear();
}

float Textbox::getWidth() {
    return textbox.getLocalBounds().width;
}

sf::String Textbox::getSFText() {
    return text;
}

bool Textbox::isSelected() const {
    return selected;
}

void Textbox::setStars(bool sel) {
    isStars = sel;
}

void Textbox::setHint(const sf::String& hint) {
    if (selected)
        textbox.setString(hint + '_');
    else
        textbox.setString(hint);
    textbox.setFillColor(sf::Color(150, 150, 150, 255));
}
