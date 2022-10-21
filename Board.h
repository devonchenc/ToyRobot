#pragma once

#include <string>

#include "Robot.h"

class Board
{
public:
    Board();
    Board(int width, int height);

    const Robot& robot() { return _robot; }

    int width() const { return _width; }
    int height() const { return _height; }

    void setWidth(int width);
    void setHeight(int height);

    void execCommand(const std::string & command);

private:
    bool parseCommand(const std::string& command);

private:
    Robot _robot;
    int _width;
    int _height;

    Command _command;
    int _placeX, _placeY;
    Direction _placeDirection;
};
