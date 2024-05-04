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

    static sf::Texture backgroundTexture;
    static sf::Texture registerTexture;
    static sf::Sprite background;
    static sf::Texture chatTextTexture;
    static sf::Sprite chatText;
    static sf::Texture mouseTexture;
    static sf::Sprite mouse;
    static int clock;
    void renderChatText();

    static Textbox *usernameBox;
    static Textbox *loginBox;
    static Textbox *passwordBox;
    static Button *usernameBoxButton;
    static Button *loginBoxButton;
    static Button *passwordBoxButton;
    static Button *logInButton;
    static Button *registerButton;
    static void initUI();

    static void onUsernameBoxClick();
    static void onLoginBoxClick();
    static void onPasswordBoxClick();
    static void onLogInButtonClick();
    static void onRegisterButtonClick();
    static void switchBox();

    sf::String login;
    sf::String password;

    void update();
    void render();
    static bool valid;
    static bool isLogin;
public:
    Login();
    static bool isValid();
    void run();
};


#endif //CHAT_LOGIN_H
