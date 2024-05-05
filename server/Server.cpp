#include "defines.h"

using namespace std;

Server::Server()
{
    // Устанавливает user_count и с помощью set_user_from_file заполняет вектор users всеми пользователями
    reset_user_base();

    //Устанавливает chat_count и с помощью set_chat_from_file заполянет вектор chats всеми чатами
    reset_chat_base();
    cout << "Server is running.\nTotal users: " << user_count << endl << "Total chats: " << chat_count << endl << endl;
}

void Server::reset_user_base()
{
    ifstream file;
    file.open("./users/" + to_string(user_count) + ".txt");
    while (file.is_open()) {
        user_count++;
        set_user_from_file(file);
        file.open("./users/" + to_string(user_count) + ".txt");
    }
    file.close();
}

void Server::set_user_from_file(ifstream& file)
{
    string name; file >> name;
    string surname; file >> surname;
    string login; file >> login;
    string password; file >> password;
    int id; file >> id;

    //считка чатов пользователя
    vector<int>user_chats;int chat_id;
    while (file >> chat_id) {
        user_chats.push_back(chat_id);;
    }

    users.push_back(User(name, surname, login, password, id, user_chats));
    file.close();
}

void Server::reset_chat_base()
{
    ifstream file;
    file.open("./chats/" + to_string(chat_count) + ".txt");
    while (file.is_open()) {
        chat_count++;
        set_chat_from_file(file);
        file.open("./chats/" + to_string(chat_count) + ".txt");
    }
    file.close();
}

void Server::set_chat_from_file(ifstream& file)
{
    int id; string message;
    Chat cur_chat;
    while (1) {
        file >> id; file.get(); getline(file, message);
        if (!file.eof()){
            cur_chat.add_message(id,message);
        }
        else break;
    }
    chats.push_back(cur_chat);
    file.close();
}

void Server::join()
{
    cout << "Register = [r]  | Log in = [l]" << endl;
    string join_status; cin >> join_status;
    if (join_status == "l") {
        op_log();
    }
    else if (join_status == "r") {
        op_reg();
    }
    else {
        cout << "Your command is incorrect. Try againg" << endl;
        join();
    }
}


void Server::op_log()
{
    cout << "Enter your login" << endl;
    string login; cin >> login;
    int ind = get_login_id(login);
    if (ind!=-1) {
        cout << "Enter your password" << endl;
        string password; cin >> password;
        if (users[ind].get_password() == password) {
            cout << "You are in account" << endl;
        }
        else {
            cout << "Password is incorrect.Try again " << endl;
            // ввод пароля заново. мне впадлу...
        }
    }
    else {
        cout << "This login is unreg" << endl;
        op_log();
    }
}

void Server::op_reg()
{
    cout << "Enter your login" << endl;
    string login; cin >> login;
    if (get_login_id(login)==-1) {
        cout << "input your name" << endl;
        string name; cin >> name;
        cout << "input your surname" << endl;
        string surname; cin >> surname;

        string password = set_password();

        //Создание файла пользователя
        ofstream file_for_user;
        file_for_user.open("./users/" + to_string(user_count++) + ".txt");
        file_for_user << name << endl << surname << endl << login << endl << password << endl << user_count-1 << endl;
        file_for_user.close();
        vector<int>arr;
        users.push_back(User(name,surname,login,password,user_count-1,arr));

    }

    else {
        cout << "This login is already taken. Try again" << endl;
        op_reg();
    }
}

string Server::set_password() {
    cout << "Enter your first password" << endl;
    string password1; cin >> password1;
    cout << "Enter your second password" << endl;
    string password2; cin >> password2;
    if (password1 != password2) {
        cout << "Password mismatch. Try Again" << endl;
        set_password();
    }
    return password1;
}

int Server::get_login_id(string login)
{
    for (int i = 0; i < user_count; i++) {
        if (users[i].get_login() == login) return i;
    }
    return -1;
}


void Server::send_message(int chat_id, int user_id, string& message)
{
    chats[chat_id].add_message(user_id, message);
}

void Server::server_off()
{
    cout << "Do you wanna to off the server?" << endl << "[Y] - Yes" << endl << "[N] - NiGGer" << endl;
    string command; cin >> command;
    if (command == "Y") {
        ofstream file;
        for (int i = 0; i < user_count; i++) {
            file.open("./users/"+to_string(i)+".txt");
            file << users[i].get_name() << endl;
            file << users[i].get_surname() << endl;
            file << users[i].get_login() << endl;
            file << users[i].get_password() << endl;
            file << users[i].get_id() << endl;
            vector<int>cur_user_chats = users[i].get_user_chats();
            for (auto b: cur_user_chats) {
                file << b << endl;
            }
            file.close();
        }


        for (int i = 0; i < chat_count; i++) {
            file.open("./chats/" + to_string(i) + ".txt");
            for (auto b : chats[i].get_chat()) {
                file << to_string(b.first) << ' ' << b.second << endl;
            }
            file.close();
        }
        cout << "Server was stopped! " << endl;
    }
    else if (command == "N") {
        request_command();
    }
    else {
        cout << "Your command is incorrect. Try Again" << endl;
        server_off();
    }
}

void Server::request_command()
{
    cout << "What do you want to do?" << endl;
    cout << "[L] - Login" << endl << "[R] - Register" << endl << "[S] - Stop Server " << endl << "[P] - Stop the program" << endl;
    string command; cin >> command;
    if (command == "L") {
        op_log();
    }
    else if (command == "R") {
        op_reg();
    }
    else if (command == "S") {
        server_off();
        return;
    }
    else if (command == "P") {
        return;
    }
    else {
        cout << "Your command is incorrect. Try Again." << endl;
    }
    request_command();
}
