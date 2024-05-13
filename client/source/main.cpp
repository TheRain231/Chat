#include "App.h"
using namespace std;
#include <SFML/Network.hpp>

int check_operation(sf::Packet& packet){
    int operation; packet >> operation;
    return operation;
}


void send_message(sf::TcpSocket& socket, int operation, int id, const string& message){
    sf::Packet packet;
    packet << operation << id << message;
    socket.send(packet);
}


string get_message(sf::TcpSocket&socket){
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done){
        int operation = check_operation(packet);
        switch (operation) {
            case 101: {cout << "You are in account";break;}
            case 102: {cout << "Password is incorrect";break;}
            case 103: {cout << "Login mismatch";break;}
        }
    }
}

int main() {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(ip, 2000);
    if (status != sf::Socket::Done)
    {
        cout << "error";
    }
    else{
        App app;
        app.run();
    }
}
