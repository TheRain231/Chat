//
// Created by Андрей Степанов on 03.05.2024.
//

#ifndef CHAT_LOGIN_H
#define CHAT_LOGIN_H

#include "SFML/Graphics.hpp"
#include "Textbox.h"
#include "Button.h"
#include "iostream"

class Login {
private:
    sf::RenderWindow *loginScreen{};
    sf::Event sfEvent{};

    sf::Texture backgroundTexture;
    sf::Sprite background;

    static Textbox *loginBox;
    static Textbox *passwordBox;
    static Button *loginBoxButton;
    static Button *passwordBoxButton;
    static Button *logInButton;
    static Button *registerButton;
    static void initUI();

    static void onLoginBoxClick();
    static void onPasswordBoxClick();
    static void onLogInButtonClick();
    static void onRegisterButtonClick();

    sf::String login;
    sf::String password;

    void update();
    void render();
public:
    Login();
    void run();
};


#endif //CHAT_LOGIN_H
