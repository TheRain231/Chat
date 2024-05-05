#pragma once
#include "defines.h"
#include "User.h"
#include "Chat.h"

using namespace std;

class Server
{
public:
    // ��� �������� ���������� ������ ���������� � 1 �������!!!!!!!
    Server();
    void join();

    void send_message(int chat_id, int user_id, string & message);//

    void request_command();

    void server_off();
private:
    int user_count = 0;
    vector <User> users;
    void reset_user_base();
    void set_user_from_file(ifstream& file);

    int chat_count = 0;
    vector <Chat> chats;
    void reset_chat_base();
    void set_chat_from_file(ifstream& file);


    //�-�� ��� �����( join() )
    void op_log();
    void op_reg();
    string set_password();
    int get_login_id(string login);
};

