//
// Created by Андрей Степанов on 16.04.2024.
//

#include "App.h"

void App::initWindow() {
    this->backgroundTexture.loadFromFile("textures/background.png");
    this->backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect({ 0, 0, reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT });
    this->window = new sf::RenderWindow(sf::VideoMode(reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT), "Chat", sf::Style::Close);
}

void App::initFonts() {
    arial.loadFromFile("fonts/Arial.ttf");
}

void App::initTextFields() {
    textbox1 = new Textbox(15, sf::Color::White, true);
    textbox1->setFont(arial);
    textbox1->setPosition({100, 100});
}

void App::initButtons() {
    button1 = new Button("Click", {200, 100}, 20);
    button1->setFont(arial);
    button1->setPosition({100, 300});

    button2 = new Button({72, 72});
    button2->setTexture("textures/send.png");
    button2->setPosition({200, 100});
    button2->setFunction(onButton2Click);
}

App::App() {
    initFonts();
    initTextFields();
    initButtons();
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
    this->window->draw(background);
    textbox1->drawTo(window);
    button1->drawTo(window);
    button2->drawTo(window);
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
                break;
            case sf::Event::TextEntered:
                textbox1->typedOn(sfEvent);
                break;
            case sf::Event::MouseMoved:
                if (button1->isMouseOver(window)) {
                    button1->setBackgroundColor(sf::Color(100, 100, 100, 255));
                } else {
                    button1->setBackgroundColor(sf::Color::White);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (button1->isMouseOver(window)) {
                    if (sfEvent.mouseButton.button == sf::Mouse::Left){
                        std::cout << "You clicked the button\n";
                    }
                    if (sfEvent.mouseButton.button == sf::Mouse::Right){
                        std::cout << "You rightclicked the button\n";
                    }
                }
                if (button2->isMouseOver(window)) {
                    button2->doFunction();
                }
                break;
            default:
                break;
        }
    }
}

void App::onButton2Click() {
    std::cout << "Работает\n";
}

