#include "defines.h"

using namespace std;

User::User(string name,string surname,string login, string password, int id,vector<int>&chats)
{
    this->name = name;
    this->surname = surname;
    this->login = login;
    this->password = password;
    this->id = id;
    this->user_chats = chats;
}

string User::get_name()
{
    return this->name;
}

string User::get_surname()
{
    return this->surname;
}

string User::get_login()
{
    return this->login;
}

string User::get_password()
{
    return this->password;
}

int User::get_id()
{
    return this->id;
}

vector<int> User::get_user_chats()
{
    return this->user_chats;
}

void User::select_chat(int id)
{
    this->selected_chat = id;
}

