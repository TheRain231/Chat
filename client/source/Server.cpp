//
// Created by Андрей Степанов on 13.05.2024.
//

#include "Server.h"
#include "App.h"

sf::TcpSocket Server::socket;
sf::IpAddress Server::ip = sf::IpAddress::getLocalAddress();
sf::Socket::Status Server::status = Server::socket.connect(ip, 2000);
int Server::id;

int Server::check_operation(sf::Packet &packet){
    int operation;
    packet >> operation;
    return operation;
}

void Server::send_message(sf::Packet packet) {
    socket.send(packet);
}

sf::Packet Server::receive_packet(){
    sf::Packet packet;
    if (socket.receive(packet)==sf::Socket::Done){
        return packet;
    }
}

void Server::updateOperations() {
    sf::Packet packet;
    while (true) {
        if (socket.receive(packet) == sf::Socket::Done) {
            int operation = check_operation(packet);
            if (operation == 0) {
                int chat_id, client_id;
                string message;
                packet >> chat_id >> client_id >> message;
                for (int i = 0 ; i < chats.size();i++){
                    if (chats[i].get_id()==chat_id) {
                        Server::chats[i].add_message(client_id, message);
                        break;
                    }
                }
                if (chats[App::currentChat].get_id()==chat_id) messageCum = true;
            }
            else if (operation==1){
                int chat_id;
                packet >> chat_id;
                chats.back().set_id(chat_id);
            }
        }
    }
}

vector<Chat> Server::chats;
bool Server::messageCum = false;