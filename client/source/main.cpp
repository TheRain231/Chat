#include "App.h"
using namespace std;

int main() {
    App app;
    app.run();
}

















#include <SFML/Network.hpp>
#include <thread>

int check_operation(sf::Packet& packet){
    int operation; packet >> operation;
    return operation;
}


void send_message(sf::TcpSocket& socket, int id, const string& message){
    sf::Packet packet;
    packet << id << message;
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


cout << "Enter your id" << endl;
int id;
cin >> id;
sf::Packet packet; packet << id; socket.send(packet);

string message;
getline(cin,message);

while (true) {
cout << "Enter your message " << endl;
getline(cin, message);
send_message(socket, id, message);
get_message(socket);
}