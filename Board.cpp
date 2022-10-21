#include "Board.h"

#include <iostream>
#include <algorithm>

const std::string placeCmdStr = "PLACE";
const std::string moveCmdStr = "MOVE";
const std::string leftCmdStr = "LEFT";
const std::string rightCmdStr = "RIGHT";
const std::string reportCmdStr = "REPORT";

Board::Board()
    : _robot(1, 1)
    , _width(1)
    , _height(1)
    , _command(Unknown)
    , _placeX(0)
    , _placeY(0)
    , _placeDirection(North)
{

}

Board::Board(int width, int height)
    : _robot(width, height)
    , _width(width)
    , _height(height)
    , _command(Unknown)
    , _placeX(0)
    , _placeY(0)
    , _placeDirection(North)
{
    if (_width <= 0)
    {
        throw "Invalid board width.";
    }
    if (_height <= 0)
    {
        throw "Invalid board height.";
    }
}
void Board::setWidth(int width)
{
    if (_width <= 0)
    {
        throw "Invalid board width.";
    }
    _width = width;
    _robot.setBoardWidth(width);
}

void Board::setHeight(int height)
{
    if (_height <= 0)
    {
        throw "Invalid board height.";
    }
    _height = height;
    _robot.setBoardHeight(height);
}

void Board::execCommand(const std::string& command)
{
    if (command.empty())
        return;

    if (!parseCommand(command))
    {
        std::cout << "Ignore Command: " << command << std::endl;
        return;
    }

    // Determine if this command is feasible
    try
    {
        if (!_robot.determine(_command, _placeX, _placeY))
            return;

        // Execute the command
        _robot.exec(_command, _placeX, _placeY, _placeDirection);
    }
    catch (const char* e)
    {
        std::cerr << e << std::endl;
    }
}

bool Board::parseCommand(const std::string& command)
{
    _command = Unknown;

    std::string noSpaceCmd = command;
    noSpaceCmd.erase(std::remove_if(noSpaceCmd.begin(), noSpaceCmd.end(), [](unsigned char x) {return std::isspace(x); }), noSpaceCmd.end());

    if (noSpaceCmd.compare(moveCmdStr) == 0)
    {
        _command = Move;
    }
    else if (noSpaceCmd.compare(leftCmdStr) == 0)
    {
        _command = Left;
    }
    else if (noSpaceCmd.compare(rightCmdStr) == 0)
    {
        _command = Right;
    }
    else if (noSpaceCmd.compare(reportCmdStr) == 0)
    {
        _command = Report;
    }
    else
    {
        size_t lenght = placeCmdStr.length();
        std::string sub = noSpaceCmd.substr(0, lenght);
        if (sub.compare(placeCmdStr) != 0)
        {
            std::cout << command << "is an unknown command." << std::endl;
            return false;
        }

        std::string::size_type firstComma = noSpaceCmd.find(',', lenght);
        if (firstComma == std::string::npos)
        {
            std::cout << "No X coordinate in place command." << std::endl;
            return false;
        }

        std::string placeXStr = noSpaceCmd.substr(lenght, firstComma - lenght);
        if (placeXStr.empty())
        {
            std::cout << "No valid X coordinate in place command." << std::endl;
            return false;
        }
        _placeX = std::stoi(placeXStr);

        firstComma++;
        std::string::size_type secondComma = noSpaceCmd.find(',', firstComma);
        if (secondComma == std::string::npos)
        {
            std::cout << "No Y coordinate in place command." << std::endl;
            return false;
        }

        std::string placeYStr = noSpaceCmd.substr(firstComma, secondComma - firstComma);
        if (placeYStr.empty())
        {
            std::cout << "No valid Y coordinate in place command." << std::endl;
            return false;
        }
        _placeY = std::stoi(placeYStr);

        std::string direction = noSpaceCmd.substr(secondComma + 1);
        for (int i = 0; i < directionNum; i++)
        {
            if (direction.compare(directionStr[i]) == 0)
            {
                _placeDirection = Direction(i);
                _command = Place;
                return true;
            }
        }

        std::cout << "No proper direction in place command." << std::endl;
        return false;
    }

    return true;
}