//
// Created by Андрей Степанов on 16.04.2024.
//

#include "App.h"

void App::initWindow() {
    backgroundTexture.loadFromFile("textures/trueBackground.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect({ 0, 0, reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT });
    uiGroupsTexture.loadFromFile("textures/uigroups.png");
    uiGroups.setTexture(uiGroupsTexture);
    this->window = new sf::RenderWindow(sf::VideoMode(reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT), "Chat", sf::Style::Close);
}

void App::initFonts() {
    arial.loadFromFile("fonts/SF-Compact-Display-Regular.otf");
}

void App::initTextFields() {
    textbox1 = new Textbox(15, sf::Color::Black, true);
    textbox1->setFont(arial);
    textbox1->setPosition({310, 766});
    textbox1->setLimit(true, 80);
}

void App::initButtons() {
    keymap = new Button({36, 36});
    keymap->setTexture("textures/globe.png");
    keymap->setPosition({917, 758});
    keymap->setFunction(onKeymapClick);

    send = new Button({36, 36});
    send->setTexture("textures/send.png");
    send->setPosition({958, 758});
    send->setFunction(onSendClick);
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
    this->window->draw(uiGroups);
    textbox1->drawTo(window);
    keymap->drawTo(window);
    send->drawTo(window);
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
                break;
            case sf::Event::MouseButtonPressed:
                if (keymap->isMouseOver(window)) {
                    keymap->doFunction();
                }
                if (send->isMouseOver(window)) {
                    send->doFunction();
                }
                break;
            default:
                break;
        }
    }
}

void App::onSendClick() {
    std::cout << textbox1->getText() << "\n";
    textbox1->clear();
}

void App::onKeymapClick() {
    Reader::isEng = !Reader::isEng;
    std::cout << "clicked\n";
}

sf::Texture App::backgroundTexture;
sf::Texture App::uiGroupsTexture;
sf::Sprite App::background;
sf::Sprite App::uiGroups;


sf::Font App::arial;
Textbox* App::textbox1;
Button* App::keymap;
Button* App::send;