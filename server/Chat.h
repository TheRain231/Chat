#pragma once
#include "defines.h"

using namespace std;

class Chat
{
public:
    Chat();
    void add_message(int id, string message);
    vector<pair<int, string>> get_chat();
private:
    vector<pair<int, string>>chat;
};
