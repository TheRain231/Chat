#pragma once
#include "defines.h"

using namespace std;

class User
{
public:
    User(string name, string surname, string login, string password, int id,vector<int>&chats);
    string get_name();
    string get_surname();
    string get_login();
    string get_password();
    int get_id();
    vector <int> get_user_chats();

    void select_chat(int id);
    int get_selected_chat();

private:
    string name;
    string surname;
    string login;
    string password;
    int id;
    vector <int> user_chats;

    int selected_chat;
};

