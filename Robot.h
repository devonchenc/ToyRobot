#pragma once

enum Direction { North, East, South, West };
enum Command { Unknown, Place, Move, Left, Right, Report };
const int directionNum = 4;
const std::string directionStr[directionNum] = { "NORTH", "EAST", "SOUTH", "WEST" };

class Robot
{
public:
    Robot(int boardWidth, int boardHeight);

    void setBoardWidth(int width) { _boardWidth = width; }
    void setBoardHeight(int height) { _boardHeight = height; }

    bool isPlaced() const { return _placed; }

    int x() const { return _x; }
    int y() const { return _y; }
    Direction direction() const { return _direction; }

    // Determine if this command is feasible
    bool determine(Command command, int x, int y);

    // Execute the command
    void exec(Command command, int x, int y, Direction direction);

private:
    bool determinePlace(int x, int y);

    bool determineMove();

    void place(int x, int y, Direction direction);

    void move();

    void left();

    void right();

    void report();

private:
    int _boardWidth;
    int _boardHeight;
    bool _placed;
    int _x;
    int _y;
    Direction _direction;
};
