#include "defines.h"
#include "Server.h"


using namespace std;

Server::Server() {
    // Устанавливает user_count и с помощью set_user_from_file заполняет вектор users всеми пользователями
    reset_user_base();

    //Устанавливает chat_count и с помощью set_chat_from_file заполянет вектор chats всеми чатами
    reset_chat_base();

    set_server_online();

    cout << "Total users: " << user_count << endl << "Total chats: " << chat_count << endl << endl;
}

void Server::reset_user_base() {
    ifstream file;
    file.open("./users/" + to_string(user_count) + ".txt");
    while (file.is_open()) {
        user_count++;
        set_user_from_file(file);
        file.open("./users/" + to_string(user_count) + ".txt");
    }
    file.close();
}

void Server::set_user_from_file(ifstream &file) {
    string username;
    file >> username;
    string login;
    file >> login;
    string password;
    file >> password;
    int id;
    file >> id;
    //считка чатов пользователя
    vector<int> user_chats;
    int chat_id;
    while (file >> chat_id) {
        user_chats.push_back(chat_id);;
    }

    users.push_back(User(username, login, password, id, user_chats));
    file.close();
}

void Server::reset_chat_base() {
    ifstream file;
    file.open("./chats/" + to_string(chat_count) + ".txt");
    while (file.is_open()) {
        chat_count++;
        set_chat_from_file(file);
        file.open("./chats/" + to_string(chat_count) + ".txt");
    }
    file.close();
}

void Server::set_chat_from_file(ifstream &file) {
    int id;
    string message;
    Chat cur_chat;
    while (1) {
        file >> id;
        file.get();
        getline(file, message);
        if (!file.eof()) {
            cur_chat.add_message(id, message);
        } else break;
    }
    chats.push_back(cur_chat);
    file.close();
}

void Server::set_server_online() {
    if (listener.listen(2000) != sf::Socket::Done) {
        cout << "Server can not be online!";
    } else {
        cout << "Server is online!" << endl;
    }
}

void Server::run() {
    while (true) {
        sf::TcpSocket *client = new sf::TcpSocket;
        if (listener.accept(*client) != sf::Socket::Done) {
            cout << "error to connect user" << endl;
            delete client;
        } else {
            cout << "Connetcted client " << clients.size() + 1 << endl;
            thread client_thread(&Server::connect_client, this, ref(*client));
            client_thread.detach();
        }
    }
    //удалить вектор сокетов
}

void Server::connect_client(sf::TcpSocket &socket) {
    join_account(socket);
    while (true) {
        sf::Packet packet = receive_packet(socket);
    }
}

void Server::join_account(sf::TcpSocket &socket) {
    sf::Packet packet = receive_packet(socket);
    int operation = check_operation(packet);
    string login;
    string password;
    if (operation == 0) {
        string username;
        packet >> username >> login >> password;
        op_reg(socket, username, login, password);
    } else if (operation == 1) {
        packet >> login >> password;
        op_log(socket, login, password);
    }
}

void Server::op_log(sf::TcpSocket &socket, string login, string password) {
    sf::Packet packet;
    int ind = get_login_id(login);
    if (ind != -1) {
        if (users[ind].get_password() == password) {
            packet << 0;
            socket.send(packet);
        } else {
            packet << 2;
            socket.send(packet);
            join_account(socket);
        }
    } else {
        packet << 1;
        socket.send(packet);
        join_account(socket);
    }
}

void Server::op_reg(sf::TcpSocket &socket, string username, string login, string password) {
    sf::Packet packet;
    if (get_login_id(login) == -1) {
        //Создание файла пользователя
        ofstream file_for_user;
        file_for_user.open("./users/" + to_string(user_count++) + ".txt");
        file_for_user << username << endl << login << endl << password << endl << user_count - 1 << endl;
        file_for_user.close();
        vector<int> arr;
        users.push_back(User(username, login, password, user_count - 1, arr));
        packet << 0;
        socket.send(packet);
    } else {
        packet << 1;
        socket.send(packet);
        join_account(socket);
    }

}


int Server::get_login_id(string login) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].get_login() == login) return i;
    }
    return -1;
}

void Server::send_message(int chat_id, int user_id, string &message) {
    chats[chat_id].add_message(user_id, message);
}

void Server::server_off() {
    cout << "Do you wanna to off the server?" << endl << "[Y] - Yes" << endl << "[N] - NiGGer" << endl;
    string command;
    cin >> command;
    if (command == "Y") {
        ofstream file;
        for (int i = 0; i < user_count; i++) {
            file.open("./users/" + to_string(i) + ".txt");
            file << users[i].get_username() << endl;
            file << users[i].get_login() << endl;
            file << users[i].get_password() << endl;
            file << users[i].get_id() << endl;
            vector<int> cur_user_chats = users[i].get_user_chats();
            for (auto b: cur_user_chats) {
                file << b << endl;
            }
            file.close();
        }


        for (int i = 0; i < chat_count; i++) {
            file.open("./chats/" + to_string(i) + ".txt");
            for (auto b: chats[i].get_chat()) {
                file << to_string(b.first) << ' ' << b.second << endl;
            }
            file.close();
        }
        cout << "Server was stopped! " << endl;
    } else {
        cout << "Your command is incorrect. Try Again" << endl;
        server_off();
    }
}


pair<int, string> Server::parce_message(sf::Packet &packet) {
    pair<int, string> message;
    packet >> message.first >> message.second;
    return message;
}

sf::Packet Server::receive_packet(sf::TcpSocket &socket) {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done)
        return packet;
}


int Server::check_operation(sf::Packet &packet) {
    int operation;
    packet >> operation;
    return operation;
}