#include "Board.h"

#include <iostream>

Robot::Robot(int boardWidth, int boardHeight)
    : _boardWidth(boardWidth)
    , _boardHeight(boardHeight)
    , _placed(false)
    , _x(0)
    , _y(0)
    , _direction(North)
{
}

bool Robot::determine(Command command, int x, int y)
{
    if (!_placed && command != Place)
    {
        std::cout << "Not placed yet." << std::endl;
        return false;
    }

    bool feasible = false;
    switch (command)
    {
    case Place:
        feasible = determinePlace(x, y);
        break;
    case Move:
        feasible = determineMove();
        break;
    case Left:
        feasible = true;
        break;
    case Right:
        feasible = true;
        break;
    case Report:
        feasible = true;
        break;
    default:
        throw "Unknown command.";
        break;
    }

    return feasible;
}

void Robot::exec(Command command, int x, int y, Direction direction)
{
    try
    {
        switch (command)
        {
        case Place:
            place(x, y, direction);
            break;
        case Move:
            move();
            break;
        case Left:
            left();
            break;
        case Right:
            right();
            break;
        case Report:
            report();
            break;
        default:
            break;
        }
    }
    catch (const char* e)
    {
        std::cerr << e << std::endl;
    }
}

bool Robot::determinePlace(int x, int y)
{
    if (x < 0 || x >= _boardWidth || y < 0 || y >= _boardHeight)
    {
        std::cout << "Unable to place robot." << std::endl;
        return false;
    }
    else
        return true;
}

bool Robot::determineMove()
{
    bool feasible = true;
    switch (_direction)
    {
    case North:
        if (_y + 1 >= _boardHeight)
        {
            feasible = false;
        }
        break;
    case East:
        if (_x + 1 >= _boardWidth)
        {
            feasible = false;
        }
        break;
    case South:
        if (_y <= 0)
        {
            feasible = false;
        }
        break;
    case West:
        if (_x <= 0)
        {
            feasible = false;
        }
        break;
    default:
        throw "Unknown direction.";
        break;
    }

    if (!feasible)
    {
        std::cout << "Unable to move robot." << std::endl;
    }
    return feasible;
}

void Robot::place(int x, int y, Direction direction)
{
    if (x < 0 || x >= _boardWidth || y < 0 || y >= _boardHeight)
    {
        throw "Wrong place parameters.";
    }

    _x = x;
    _y = y;
    _direction = direction;
    _placed = true;
}

void Robot::move()
{
    if (!_placed)
    {
        throw "Move before being placed.";
    }

    switch (_direction)
    {
    case North:
        if (_y + 1 >= _boardHeight)
        {
            throw "Out of the table.";
        }
        _y++;
        break;
    case East:
        if (_x + 1 >= _boardHeight)
        {
            throw "Out of the table.";
        }
        _x++;
        break;
    case South:
        if (_y <= 0)
        {
            throw "Out of the table.";
        }
        _y--;
        break;
    case West:
        if (_x <= 0)
        {
            throw "Out of the table.";
        }
        _x--;
        break;
    default:
        throw "Unknown direction.";
        break;
    }
}

void Robot::left()
{
    if (!_placed)
    {
        throw "Rotate before being placed.";
    }
    _direction = Direction(_direction == 0 ? 3 : _direction - 1);
}

void Robot::right()
{
    if (!_placed)
    {
        throw "Rotate before being placed.";
    }
    _direction = Direction(_direction == 3 ? 0 : _direction + 1);
}

void Robot::report()
{
    if (!_placed)
    {
        throw "Report before being placed.";
    }
    std::cout << "X:" << _x << " Y:" << _y << " Direction:" << directionStr[_direction] << std::endl;
}