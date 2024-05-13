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
    void run();

    void op_log(sf::TcpSocket& socket, string login,string password);
    void op_reg(sf::TcpSocket& scoket, string username, string login, string password);
    int get_login_id(string login);


    void send_message(int chat_id, int user_id, string & message);//

    void server_off();


    //Network objects
    void connect_client(sf::TcpSocket& socket);
    sf::Packet receive_packet(sf::TcpSocket& socket);
    int check_operation(sf::Packet& packet);
    pair<int,string> parce_message(sf::Packet& packet);
    void join_account(sf::TcpSocket& socket);


private:
    //network objects
    vector<pair<int,sf::TcpSocket*>> clients;
    sf::TcpListener listener;
    void set_server_online();


    int user_count = 0;
    vector <User> users;
    void reset_user_base();
    void set_user_from_file(ifstream& file);

    int chat_count = 0;
    vector <Chat> chats;
    void reset_chat_base();
    void set_chat_from_file(ifstream& file);

};
