//
// Created by Андрей Степанов on 16.04.2024.
//

#ifndef CHAT_APP_H
#define CHAT_APP_H

#include <SFML/Graphics.hpp>
#include "Reader.h"
#include "Textbox.h"
#include "Button.h"
#include "Bubble.h"

class App {
private:
    const Reader reader;
    static Textbox *textbox1;
    static Button *send;
    static std::vector<Bubble> bubbles;

    static sf::Texture backgroundTexture;
    static sf::Texture uiGroupsTexture;
    static sf::Sprite background;
    static sf::Sprite uiGroups;
    sf::RenderWindow *window{};
    sf::Event sfEvent{};

    void initWindow();
    static void initTextFields();
    static void initButtons();
    void updateSFMLEvents();

    static void onSendClick();
    static void receiveMessage();

    static float y;
public:
    App();
    ~App();
    void update();
    void render();
    void run();
};

#endif //CHAT_APP_H
