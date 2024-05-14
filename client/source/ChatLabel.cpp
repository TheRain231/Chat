//
// Created by Андрей Степанов on 06.05.2024.
//

#include "ChatLabel.h"

ChatLabel::ChatLabel(sf::Vector2f pos, sf::String label, sf::String lastMessage) {
    id = ++maxId;
    this->base.setPosition(pos);
    this->base.setSize({300, 60});
    this->outline.setPosition({pos.x + 10, pos.y + 60});
    this->outline.setSize({280, 1});
    this->outline.setFillColor(sf::Color(0, 0, 0, 40));

    this->label.setFont(Reader::arial);
    this->label.setFillColor(sf::Color::Black);
    this->label.setCharacterSize(20);
    this->label.setString(label);
    this->label.setPosition(pos.x + 10, pos.y + 10);

    this->lastMessage.setFont(Reader::arial);
    this->lastMessage.setFillColor(sf::Color::Black);
    this->lastMessage.setCharacterSize(15);
    this->lastMessage.setString(lastMessage);
    this->lastMessage.setPosition(pos.x + 10, pos.y + 35);

    this->button = new Button({300, 60});
    this->button->setPosition(pos);
}

void ChatLabel::drawTo(sf::RenderWindow *target) {
    target->draw(base);
    target->draw(outline);
    target->draw(label);
    target->draw(lastMessage);
}

void ChatLabel::setSelected(bool sel) {
    if (isSelected != sel) {
        if (sel) {
            this->base.setFillColor(sf::Color(93, 143, 194, 255));
            this->label.setFillColor(sf::Color::White);
            this->lastMessage.setFillColor(sf::Color::White);
        } else {
            this->base.setFillColor(sf::Color::Transparent);
            this->label.setFillColor(sf::Color::Black);
            this->lastMessage.setFillColor(sf::Color::Black);
        }
        isSelected = sel;
    }
}

void ChatLabel::doFunc() {
    for (auto i: ChatLabel::chatLabels) {
        i->setSelected(false);
    }
    this->setSelected(true);
    auto chat = Server::chats[id].get_chat();
    Bubble::bubbles.clear();
    yBubbles = 60;
    for (const auto &message: chat) {
        Bubble::bubbles.push_back(
                new Bubble(message.second, message.first == 0 ? Bubble::me : Bubble::mynigga, yBubbles));
        if (yBubbles > 700) {
            for (auto i: Bubble::bubbles) {
                i->moveUp();
            }
            isScroll = true;
        } else {
            yBubbles += 45;
        }
    }
}

void ChatLabel::moveUp(float delta) {
    for (auto i: ChatLabel::chatLabels) {
        i->outline.move({0, delta});
        i->base.move({0, delta});
        i->label.move({0, delta});
        i->lastMessage.move({0, delta});
        i->button->move({0, delta});
    }
}

void ChatLabel::move(float delta) {
    float upperBorder = 50;
    float downerBorder = 740;
    if (ChatLabel::chatLabels[0]->base.getPosition().y >= upperBorder) {
        if (delta < 0) {
            moveUp(delta);
        }
    } else if (ChatLabel::chatLabels.back()->base.getPosition().y <= downerBorder) {
        if (delta > 0) {
            moveUp(delta);
        }
    } else {
        moveUp(delta);
        if (ChatLabel::chatLabels[0]->base.getPosition().y >= upperBorder) {
            float dy = upperBorder - ChatLabel::chatLabels[0]->base.getPosition().y;
            moveUp(dy);
        }
        if (ChatLabel::chatLabels.back()->base.getPosition().y <= downerBorder) {
            float dy = downerBorder - ChatLabel::chatLabels.back()->base.getPosition().y;
            moveUp(dy);
        }
    }
}

int ChatLabel::maxId = -1;

bool ChatLabel::isMouseOver(sf::RenderWindow *target) {
    if (button->isMouseOver(target))
        return true;
    return false;
}

bool ChatLabel::isScrollable() {
    return isScroll;
}

std::vector<ChatLabel *> ChatLabel::chatLabels;