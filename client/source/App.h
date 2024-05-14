//
// Created by Андрей Степанов on 16.04.2024.
//

#ifndef CHAT_APP_H
#define CHAT_APP_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Reader.h"
#include "Textbox.h"
#include "Button.h"
#include "Bubble.h"
#include "Login.h"
#include "ChatLabel.h"
#include "Server.h"

class App {
private:
    const Reader reader;
    static Textbox *textbox1;
    static Button *send;
    static Button *newChat;
    static Button *newUser;
    static std::vector<Bubble*> bubbles;

    static sf::Texture backgroundTexture;
    static sf::Texture uiGroupsTexture;
    static sf::Sprite background;
    static sf::Sprite uiGroups;
    sf::RenderWindow *window{};
    Login login;
    sf::Event sfEvent{};

    sf::RenderWindow *newChatWindow{};
    sf::RenderWindow *newUserWindow{};

    void initWindow();
    static void initChats();
    static void initTextFields();
    static void initButtons();
    void updateSFMLEvents();

    static void onSendClick();
    static void receiveMessage();
    static void onNewChatClick();
    static void onNewPersonClick();

    static float yBubbles;
    static float yChats;
    static bool isScrollable;
    static bool isChatsScrollable;
    static bool isNewChatWindowOpen;
    static bool isNewUserWindowOpen;
public:
    App();
    ~App();
    void update();
    void render();
    void run();
};

#endif //CHAT_APP_H
