//
// Created by Андрей Степанов on 13.05.2024.
//

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "SFML/Network.hpp"
#include "iostream"
#include "Chat.h";
class Server {
public:
    static vector<Chat>chats;
    static sf::IpAddress ip;
    static sf::TcpSocket socket;
    static sf::Socket::Status status;

    static int check_operation(sf::Packet &packet);

    static void send_message(sf::Packet packet);

    static void get_message();

    static sf::Packet receive_packet();
};

#endif //CHAT_SERVER_H
vector<Chat>chats;