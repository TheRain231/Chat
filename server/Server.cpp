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
        set_chat_from_file(file);
        chat_count++;
        file.open("./chats/" + to_string(chat_count) + ".txt");
    }
    file.close();
}

void Server::set_chat_from_file(ifstream &file) {
    int id;
    string message;
    Chat cur_chat;
    getline(file,message);
    cur_chat.set_name(message);
    cur_chat.set_id(chat_count);
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
    if (!join_account(socket)) return;
    while (true) {
        sf::Packet packet;
        update_clients(socket,packet);
        int operation = check_operation(packet);
        if (operation == 0){
            int chat_id,client_id;
            string message;
            packet >> chat_id >> client_id >> message;
            send_message_for_online(chat_id,client_id,message);
        }
        else if (operation == 1){

        }
    }
}

bool Server::join_account(sf::TcpSocket &socket) {
    sf::Packet packet;
    if (socket.receive(packet)!=sf::Socket::Done) return 0;
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
    return 1;
}

void Server::get_chats(sf::Packet &packet, int ind) {
    vector<int> user_chats = users[ind].get_user_chats();
    int len = user_chats.size();
    packet << len;
    for (int i = 0; i < len; i++) {
        vector<pair<int, string>> cht = chats[user_chats[i]].get_chat();
        packet << chats[user_chats[i]].get_id() << chats[user_chats[i]].get_name() << int(cht.size());
        for (int j = 0; j < cht.size(); j++) {
            packet << cht[j].first << cht[j].second;
        }
    }
}


void Server::op_log(sf::TcpSocket &socket, string login, string password) {
    sf::Packet packet;
    int id = get_login_id(login);
    if (id != -1) {
        if (users[id].get_password() == password) {
            packet << 0;
            packet << id;
            get_chats(packet,id);
            socket.send(packet);
            clients.push_back({id,&socket});
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
    int id = get_login_id(login);
    if (id == -1) {
        //Создание файла пользователя
        ofstream file_for_user;
        file_for_user.open("./users/" + to_string(user_count++) + ".txt");
        file_for_user << username << endl << login << endl << password << endl << user_count - 1 << endl;
        file_for_user.close();
        vector<int> arr;
        users.push_back(User(username, login, password, user_count - 1, arr));
        packet << 0;
        packet << id;
        socket.send(packet);
        clients.push_back({get_login_id(login),&socket});
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
            file << chats[i].get_name() << endl;
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

void Server::send_message_for_online(int chat_id, int client_id, string message) {
    chats[chat_id].add_message(client_id,message);
    for (int i = 0 ; i < clients.size(); i++){
        if (clients[i].first==client_id) continue;
        vector <int> cur_chats = users[clients[i].first].get_user_chats();

        if (std::find(cur_chats.begin(), cur_chats.end(),chat_id)!=cur_chats.end()){

            sf::Packet packet;
            packet << 0 << chat_id << client_id << message;
            clients[i].second->send(packet);
        }
    }
}

void Server::update_clients(sf::TcpSocket& socket,sf::Packet& packet) {
    if (socket.receive(packet) != sf::Socket::Done) {
        for (int i = 0 ; i < clients.size(); i++){
            if (&socket==clients[i].second) {
                // delete this socket
                //delete clients[i].second;
                clients.erase(clients.begin() + i);
            }
        }
    }
}


