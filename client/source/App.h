//
// Created by Андрей Степанов on 16.04.2024.
//

#ifndef CHAT_APP_H
#define CHAT_APP_H

#include <SFML/Graphics.hpp>
#include "Reader.h"

class App {
private:
    const Reader reader;

    sf::RenderWindow *window;
    sf::Event sfEvent;

    void initWindow();
    void updateSFMLEvents();
public:
    App();
    ~App();
    void update();
    void render();
    void run();
};


#endif //CHAT_APP_H
