#include "defines.h"

using namespace std;

Chat::Chat()
{

}

void Chat::add_message(int id, string message)
{
    chat.push_back(make_pair(id, message));
}

vector<pair<int, string>> Chat::get_chat()
{
    return this->chat;
}
