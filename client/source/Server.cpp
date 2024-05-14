//
// Created by Андрей Степанов on 13.05.2024.
//

#include "Server.h"

sf::TcpSocket Server::socket;
sf::IpAddress Server::ip = sf::IpAddress::getLocalAddress();
sf::Socket::Status Server::status = Server::socket.connect(ip, 2000);

int Server::check_operation(sf::Packet &packet){
    int operation;
    packet >> operation;
    return operation;
}

void Server::send_message(sf::Packet packet) {
    socket.send(packet);
}

void Server::get_message() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done){
        int operation = check_operation(packet);
        switch (operation) {
            case 101: {std::cout << "You are in account";break;}
            case 102: {std::cout << "Password is incorrect";break;}
            case 103: {std::cout << "Login mismatch";break;}
        }
    }
}

sf::Packet Server::receive_packet(){
    sf::Packet packet;
    if (socket.receive(packet)==sf::Socket::Done){
        return packet;
    }
}
