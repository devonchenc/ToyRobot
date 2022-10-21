# ToyRobot

## Prerequisite

- google test

It can be installed by this command:
```
sudo apt install libgtest-dev
```

## Compilation

ToyRobot project can be compiled with Make.

```
make
make runtest
```

## Run

ToyRobot project accepts text files as the program input. All robot commands should be written in the file line by line. Spaces are allowed inside the command line. The following code demonstrates using an existing file called move.txt as input to the program.

```
./toyrobot move.txt
```

## Structure

This program has two main classes called *Robot* and *Board*, declared in Robot.h and Board.h, respectively.

main.cpp is the main program while test.cpp is the test program.