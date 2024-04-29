//
// Created by Андрей Степанов on 16.04.2024.
//

#ifndef CHAT_READER_H
#define CHAT_READER_H

#include <string>
#include <fstream>
#include <iostream>

class Reader {
public:
    Reader();
    static bool isEng;
    int WINDOW_HEIGHT;
    int WINDOW_WIDTH;
private:
    std::ifstream file;

    int currentValue;
    std::string currentVariable;

    void read(int& num, const std::string& name);
};


#endif //CHAT_READER_H
