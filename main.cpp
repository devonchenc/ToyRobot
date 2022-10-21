#include <iostream>
#include <string>
#include <fstream>

#include "Board.h"

const int width = 5;
const int height = 5;

int main(int argc, char* argv[])
{
    std::string fileName;
    if (argc > 1)
    {
        fileName = argv[1];
    }
    if (fileName.empty())
    {
        std::cout << "Empty file name." << std::endl;
        return 1;
    }

    std::ifstream fin(fileName);
    if (!fin)
    {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    Board board(width, height);
    for (std::string line; getline(fin, line, '\n');)
    {
        board.execCommand(line);
    }
    fin.close();

    return 0;
}

