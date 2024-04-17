//
// Created by Андрей Степанов on 16.04.2024.
//

#include "App.h"

void App::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT), "Chat");
}

void App::initTextFields() {
    arial.loadFromFile("fonts/Arial.ttf");
    textbox1 = new Textbox(15, sf::Color::White, true);
    textbox1->setFont(arial);
    textbox1->setPosition({100, 100});
}

App::App() {
    initTextFields();
    initWindow();
}

App::~App() {
    delete this->window;
}

void App::update() {
    updateSFMLEvents();
}

void App::render() {
    this->window->clear();
    textbox1->drawTo(window);
    this->window->display();
}

void App::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void App::updateSFMLEvents() {
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
//        textbox1->setSelected(false);
//    }

    while (this->window->pollEvent(this->sfEvent)) {
        switch (this->sfEvent.type) {
            case sf::Event::Closed:
                this->window->close();
            case sf::Event::TextEntered:
                textbox1->typedOn(sfEvent);
            default:
                break;
        }
    }
}

