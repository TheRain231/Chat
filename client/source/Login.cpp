//
// Created by Андрей Степанов on 03.05.2024.
//

#include "Login.h"

Login::Login() {
    backgroundTexture.loadFromFile("textures/loginUI.png");
    background.setTexture(backgroundTexture);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    initUI();
    this->loginScreen = new sf::RenderWindow(sf::VideoMode(500, 400), "Chat", sf::Style::Close, settings);
}

void Login::initUI() {
    loginBox = new Textbox(15, sf::Color::Black);
    loginBox->setFont(Reader::arial);
    loginBox->setPosition({109, 164});
    loginBox->setLimit(true, 275);

    loginBoxButton = new Button({300, 50});
    loginBoxButton->setBackgroundColor(sf::Color::Transparent);
    loginBoxButton->setPosition({100, 150});
    loginBoxButton->setFunction(onLoginBoxClick);

    passwordBox = new Textbox(15, sf::Color::Black);
    passwordBox->setSelected(false);
    passwordBox->setFont(Reader::arial);
    passwordBox->setPosition({109, 225});
    passwordBox->setLimit(true, 275);
    passwordBox->setStars(true);

    passwordBoxButton = new Button({300, 50});
    passwordBoxButton->setBackgroundColor(sf::Color::Transparent);
    passwordBoxButton->setPosition({100, 211});
    passwordBoxButton->setFunction(onPasswordBoxClick);

    logInButton = new Button({125, 30.5});
    logInButton->setBackgroundColor(sf::Color::Transparent);
    logInButton->setPosition({187.5, 293});
    logInButton->setFunction(onLogInButtonClick);

    registerButton = new Button({60, 22});
    registerButton->setBackgroundColor(sf::Color::Transparent);
    registerButton->setPosition({220, 353.5});
    registerButton->setFunction(onRegisterButtonClick);
}

void Login::update() {
    while (this->loginScreen->pollEvent(sfEvent)){
        switch (sfEvent.type) {
            case sf::Event::Closed:
                this->loginScreen->close();
                break;
            case sf::Event::TextEntered:
//                if (sfEvent.text.unicode == ENTER_KEY){
//                    App::receiveMessage();
//                } else {
                        if(loginBox->isSelected())
                            loginBox->typedOn(sfEvent);
                        else if(passwordBox->isSelected())
                            passwordBox->typedOn(sfEvent);
//                }
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseButtonPressed:
                if (logInButton->isMouseOver(loginScreen)) {
                    logInButton->doFunction();
                    loginScreen->close();
                } else if (registerButton->isMouseOver(loginScreen)){
                    registerButton->doFunction();
                } else if (loginBoxButton->isMouseOver(loginScreen)){
                    loginBoxButton->doFunction();
                } else if (passwordBoxButton->isMouseOver(loginScreen)) {
                    passwordBoxButton->doFunction();
                }
                break;
            default:
                break;
        }
    }
}

void Login::render() {
    this->loginScreen->clear();
    this->loginScreen->draw(background);

    loginBox->drawTo(loginScreen);
    passwordBox->drawTo(loginScreen);

    loginBoxButton->drawTo(loginScreen);
    passwordBoxButton->drawTo(loginScreen);
    logInButton->drawTo(loginScreen);
    registerButton->drawTo(loginScreen);

    this->loginScreen->display();
}

void Login::run() {
    while (this->loginScreen->isOpen()){
        update();
        render();
    }
}

void Login::onLogInButtonClick() {
    std::cout << "login: " << loginBox->getText() << "\n";
    std::cout << "password: " << passwordBox->getText() << "\n";
}

void Login::onRegisterButtonClick() {
    std::cout << "register\n";
}

void Login::onLoginBoxClick() {
    loginBox->setSelected(true);
    passwordBox->setSelected(false);
}

void Login::onPasswordBoxClick() {
    loginBox->setSelected(false);
    passwordBox->setSelected(true);
}

Textbox* Login::loginBox;
Textbox* Login::passwordBox;
Button* Login::loginBoxButton;
Button* Login::passwordBoxButton;
Button* Login::logInButton;
Button* Login::registerButton;