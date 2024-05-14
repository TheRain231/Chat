//
// Created by Андрей Степанов on 16.04.2024.
//

#include "App.h"
#include <thread>

void App::initWindow() {
    backgroundTexture.loadFromFile("textures/trueBackground.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect({0, 0, reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT});
    uiGroupsTexture.loadFromFile("textures/uigroups.png");
    uiGroups.setTexture(uiGroupsTexture);
}

void App::initChats() {
    for (int i = 0; i < Server::chats.size(); i++) {
        ChatLabel::chatLabels.push_back(new ChatLabel({0, yChats += 61}, Server::chats[i].get_name(), Server::chats[i].get_last_message().second));
    }

    if (!ChatLabel::chatLabels.empty()){
        ChatLabel::chatLabels[0]->doFunc();
        isScrollable = ChatLabel::chatLabels[0]->isScrollable();
    }


    if (ChatLabel::chatLabels.size() > 12) {
        isChatsScrollable = true;
    }
}

void App::initTextFields() {
    textbox1 = new Textbox(15, sf::Color::Black);
    textbox1->setFont(Reader::arial);
    textbox1->setPosition({310, 766});
    textbox1->setLimit(true, 650);
}

void App::initButtons() {
    send = new Button({36, 36});
    send->setTexture("textures/send.png");
    send->setPosition({958, 758});
    send->setFunction(onSendClick);
    
    newChat = new Button({35, 35});
    newChat->setTexture("textures/newChat.png");
    newChat->setPosition({258, 8});
    newChat->setFunction(onNewChatClick);

    newUser = new Button({35, 35});
    newUser->setTexture("textures/newPerson.png");
    newUser->setPosition({958, 10});
    newUser->setFunction(onNewPersonClick);
}

App::App() {
    initTextFields();
    initButtons();
    initWindow();
}

App::~App() {
    delete this->window;
}

void App::update() {
    receiveMessage();
    updateSFMLEvents();
}

void App::render() {
    this->window->clear();

    this->window->draw(background);

    for (auto i: ChatLabel::chatLabels) {
        i->drawTo(window);
    }
    for (auto i: Bubble::bubbles) {
        i->drawTo(window);
    }

    this->window->draw(uiGroups);
    textbox1->drawTo(window);
    send->drawTo(window);
    newChat->drawTo(window);
    newUser->drawTo(window);

    this->window->display();
}

void App::run() {
    if (Server::status != sf::Socket::Done) {
        std::cout << "error";
    } else {
        //login screen
        login.run();

        std::thread receive_message(Server::updateOperations);
        receive_message.detach();

        initChats();
        //main screen init
        if (Login::isValid()) {
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;
            this->window = new sf::RenderWindow(sf::VideoMode(reader.WINDOW_WIDTH, reader.WINDOW_HEIGHT), "Chat",
                                                sf::Style::Close, settings);

            //main screen run
            while (this->window->isOpen()) {
                this->update();
                this->render();
            }
        }
    }
}

void App::updateSFMLEvents() {
    sf::Packet packet;
    while (this->window->pollEvent(this->sfEvent)) {
        switch (this->sfEvent.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::TextEntered:
                if (sfEvent.text.unicode == 10) {
                    send->doFunction();
                } else {
                    textbox1->typedOn(sfEvent);
                }
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseButtonPressed:
                if (send->isMouseOver(window)) {
                    send->doFunction();
                }
                else if (newChat->isMouseOver(window)){
                    newChat->doFunction();
                }
                else if (newUser->isMouseOver(window)){
                    newUser->doFunction();
                }
                else {
                    for (int i = 0; i < ChatLabel::chatLabels.size(); i++) {
                        if (ChatLabel::chatLabels[i]->isMouseOver(window)){
                            ChatLabel::chatLabels[i]->doFunc();
                            currentChat = i;
                            break;
                        }
                    }
                }
                break;
            case sf::Event::MouseWheelScrolled:
                if (isScrollable && sf::Mouse::getPosition().x - window->getPosition().x * 2 > 600) {
                    if (sfEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                        if (Bubble::bubbles[0]->getY() >= 60) {
                            if (sfEvent.mouseWheelScroll.delta < 0) {
                                for (auto i: Bubble::bubbles) {
                                    i->moveUp(sfEvent.mouseWheelScroll.delta * 5);
                                }
                            }
                        } else if (Bubble::bubbles.back()->getY() <= 700) {
                            if (sfEvent.mouseWheelScroll.delta > 0) {
                                for (auto i: Bubble::bubbles) {
                                    i->moveUp(sfEvent.mouseWheelScroll.delta * 5);
                                }
                            }
                        } else {
                            for (auto i: Bubble::bubbles) {
                                i->moveUp(sfEvent.mouseWheelScroll.delta * 5);
                            }
                            if (Bubble::bubbles[0]->getY() >= 60) {
                                float dy = 60 - Bubble::bubbles[0]->getY();
                                for (auto i: Bubble::bubbles) {
                                    i->moveUp(dy);
                                }
                            }
                            if (Bubble::bubbles.back()->getY() <= 700) {
                                float dy = 700 - Bubble::bubbles.back()->getY();
                                for (auto i: Bubble::bubbles) {
                                    i->moveUp(dy);
                                }
                            }
                        }
                    }
                } else if (isChatsScrollable && sf::Mouse::getPosition().x - window->getPosition().x * 2 < 600) {
                    if (sfEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                        ChatLabel::move(sfEvent.mouseWheelScroll.delta * 5);
                    }
                }
            default:
                break;
        }
    }
}

void App::onSendClick() {
    sf::Packet packet;
    packet << 0 << currentChat << Server::id << textbox1->getText();
    cout << Server::id << currentChat << textbox1->getText() << endl;
    Server::socket.send(packet);
    yBubbles = Bubble::bubbles.back()->getY() + 35;
    if (isScrollable) {
        float dy = 735 - Bubble::bubbles.back()->getY();
        for (auto i: Bubble::bubbles) {
            i->moveUp(dy - 45);
        }
        yBubbles = 735;
    }
    Bubble::bubbles.push_back(new Bubble(textbox1->getSFText(), Bubble::me, yBubbles));
    if (yBubbles > 700) {
        for (auto i: Bubble::bubbles) {
            i->moveUp();
        }
        isScrollable = true;
    } else {
        yBubbles += 45;
    }
    textbox1->clear();
}

void App::receiveMessage() {
    if (Server::messageCum){
        Server::messageCum = false;
        yBubbles = Bubble::bubbles.back()->getY() + 35;
        if (isScrollable) {
            float dy = 735 - Bubble::bubbles.back()->getY();
            for (auto i: Bubble::bubbles) {
                i->moveUp(dy - 45);
            }
            yBubbles = 735;
        }
        Bubble::bubbles.push_back(new Bubble(Server::chats[currentChat].get_last_message().second, Bubble::mynigga, yBubbles));
        if (yBubbles > 700) {
            for (auto i: Bubble::bubbles) {
                i->moveUp();
            }
            isScrollable = true;
        } else {
            yBubbles += 45;
        }
    }
}

void App::onNewChatClick() {
    std::cout << "new chat" << '\n';
}

void App::onNewPersonClick() {
    std::cout << "new person" << '\n';
}

sf::Texture App::backgroundTexture;
sf::Texture App::uiGroupsTexture;
sf::Sprite App::background;
sf::Sprite App::uiGroups;


Textbox *App::textbox1;
Button *App::send;
Button *App::newUser;
Button *App::newChat;

float App::yBubbles = 60;
float App::yChats = -10;
bool App::isScrollable = false;
bool App::isChatsScrollable = false;
int App::currentChat = 0;