/****************************************************
 *   Functions to solve mazes.                       *
 *                                                   *
 *   Datafile must still contain size as first data. *
 *                                                   *
 *   Four functions are only stubs.                  *
 ****************************************************/
/*
 *Assignment Step3 Maze.cpp
 *Au:Lost_Deviation
 */
#include "Maze.h"
#include <bits/stdc++.h>
#ifndef open_dbg_func
#define err(args...)
#endif
using namespace std;

//	The following enumerated type indicates directions within the maze

enum Direction { DOWN, LEFT, UP, RIGHT };

//	This struct is used for locations within the maze

struct Position {
    int H, V;
};

//	The maze itself is indicated by # for the walls
//	All other locations in the maze can be any other character
//	Global variables defining the maze to be solved

char *maze;
int mazeWidth, mazeHeight;
int *posi;
int i = 0;
//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

void FindEntrance(int &);
bool AtExit(int);
void ReportPosition(int);
void WheresRight(int, Direction, int &);
void WheresLeft(int, Direction, int &);
void HeadingBack(int, Direction &);
bool Wall(int);
void TurnRight(Direction &);
void MoveForward(int &, Direction);
void WheresAhead(int, Direction, int &);
void TurnLeft(Direction &);

//	This function loads the maze from the specified file
//	returning the maze and its dimensions
//	The height of the maze is not actually used anywhere but here

bool LoadMaze(const char fname[]) {
    ifstream ifs(fname);
    if (ifs.good()) {
        ifs >> mazeWidth >> mazeHeight;
        maze = new char[mazeWidth * mazeHeight];
        posi = new int[mazeWidth * mazeHeight];
        for (int i = 0; i < mazeHeight; i++)
            for (int j = 0; j < mazeWidth; j++)
                ifs >> maze[i * mazeWidth + j];
        ifs.close();
        return true;
    } else {
        cerr << "File not found." << endl;
        return false;
    }
    // if (ifs.good()) {
    //     char r = ' ';
    //     while (r < '0' || r > '9') {
    //         ifs.get(r);
    //         err(r);
    //     }
    //     while (r >= '0' && r <= '9') {
    //         mazeWidth = mazeWidth * 10 + (r - '0');
    //         err(mazeWidth);
    //         ifs.get(r);
    //         err(r);
    //     }
    //     ifs.get(r);
    //     while (r >= '0' && r <= '9') {
    //         mazeHeight = mazeHeight * 10 + (r - '0');
    //         err(mazeHeight);
    //         ifs.get(r);
    //         err(r);
    //     }
    //     while (r != '#')
    //         ifs.get(r);
    //     maze[0] = r;
    //     err(mazeHeight, mazeWidth);
    //     for (int i = 0; i < mazeHeight; i++)
    //         for (int j = 0; j < mazeWidth; j++) {
    //             err(mazeHeight, mazeWidth, i * mazeWidth + j + 1);
    //             ifs >> maze[i * mazeWidth + j + 1];
    //         }
    //     ifs.close();
    //     return true;
    // } else {
    //     cerr << "File not found." << endl;
    //     return false;
    // }
}

//	This function solves the maze using the 'hand on left wall'
//	rule, printing the maze position as it proceeds

void SolveMaze() {
    err(mazeHeight, mazeWidth);
    // for (int i = 0; i < mazeHeight; i++) {
    //     for (int j = 0; j < mazeWidth; j++)
    //         cout << maze[i * mazeWidth + j];
    //     cout << endl;
    // }
    int pos, Right, Left, Head;
    Direction heading;
    vector<int> last_choice;
    vector<int> last_heading;
    map<int, int> last_pos;
    FindEntrance(pos);
    heading = DOWN;
    while (!AtExit(pos)) {
        posi[i] = pos;
        int x = pos / mazeWidth;
        int y = pos % mazeWidth;
        err(x, y, heading, i, last_choice);
        i++;
        if (i >= mazeHeight * mazeWidth) {
            cout << "array too small\n";
            abort();
        }
        WheresRight(pos, heading, Right);
        WheresAhead(pos, heading, Head);
        WheresLeft(pos, heading, Left);
        int dep = 0;
        if (!Wall(Right)) dep++;
        if (!Wall(Head)) dep++;
        if (!Wall(Left)) dep++;
        if (dep > 1) {
            last_choice.push_back(i - 1);
            last_heading.push_back(heading);
            if (!Wall(Right)) {
                TurnRight(heading);
                MoveForward(pos, heading);
                last_pos[i - 1] = Right;
            } else {
                if (!Wall(Head)) {
                    MoveForward(pos, heading);
                    last_pos[i - 1] = Head;
                } else if (!Wall(Left)) {
                    TurnLeft(heading);
                    MoveForward(pos, heading);
                    last_pos[i - 1] = Left;
                } else {
                    int x = pos / mazeWidth;
                    int y = pos % mazeWidth;
                    err(x, y, last_heading.back());
                    i = last_choice.back();
                    pos = posi[i];
                    maze[last_pos[i]] = '#';
                    last_choice.pop_back();
                    int now_heading = last_heading.back();
                    HeadingBack(now_heading, heading);
                    last_heading.pop_back();
                }
            }
        } else {
            if (!Wall(Right)) {
                TurnRight(heading);
                MoveForward(pos, heading);
            } else {
                if (!Wall(Head)) {
                    MoveForward(pos, heading);
                } else if (!Wall(Left)) {
                    TurnLeft(heading);
                    MoveForward(pos, heading);
                } else {
                    int x = pos / mazeWidth;
                    int y = pos % mazeWidth;
                    err(x, y, last_choice.back(), last_heading.back());
                    i = last_choice.back();
                    pos = posi[i];
                    maze[last_pos[i]] = '#';
                    last_choice.pop_back();
                    int now_heading = last_heading.back();
                    HeadingBack(now_heading, heading);
                    last_heading.pop_back();
                }
            }
        }
    }
    posi[i] = pos;
    i++;
    if (i >= 400) {
        cout << "array too small\n";
        abort();
    }
    int counter = 0;
    for (int j = 0; j < i; j++) {
        if (posi[j] < 0) continue;
        cout << "Current position: (" << posi[j] / mazeWidth << ','
             << posi[j] % mazeWidth << ')' << endl;
        counter++;
    }
    cout << "total steps:" << counter << endl;
    cout << "Maze solved" << endl;

    // for (int j = 0; j < i; j++) {
    //     if (posi[j] < 0) continue;
    //     maze[posi[j]] = '$';
    // }
    // for (int i = 0; i < mazeHeight; i++) {
    //     for (int j = 0; j < mazeWidth; j++)
    //         cout << maze[i * mazeWidth + j];
    //     cout << endl;
    // }

    delete[] maze;
    delete[] posi;
}

void HeadingBack(int now_heading, Direction &heading) {
    switch (now_heading) {
    case 0: {
        heading = DOWN;
        break;
    }
    case 1: {
        heading = LEFT;
        break;
    }
    case 2: {
        heading = UP;
        break;
    }
    case 3: {
        heading = RIGHT;
        break;
    }
    }
}

//	This function scans the maze array for the first non-wall item
//	It assumes that the entrance is in the top row of the maze array

void FindEntrance(int &pos) {
    pos = 0;
    while (Wall(pos))
        pos++;
}

//	This function returns true if the maze position is the exit
//	identified by being in the last row of the array

bool AtExit(int pos) {
    return (pos >= (mazeHeight - 1) * mazeWidth);
}

//	This function displays the position in the maze
//	At this time it specifies row and column of the array

/*void ReportPosition(int pos)
{
    cout << "Current position: (" << pos/mazeWidth << ',' << pos%mazeWidth <<
')' << endl;
}*/

//	This function takes a maze position and a heading and determines
//	the position to the right of this position

void WheresRight(int pos, Direction heading, int &right) {
    right = pos;
    switch (heading) {
    case DOWN: {
        right--;
        break;
    }
    case LEFT: {
        right -= mazeWidth;
        break;
    }
    case UP: {
        right++;
        break;
    }
    case RIGHT: {
        right += mazeWidth;
    }
    }
}
void WheresLeft(int pos, Direction heading, int &Left) {
    Left = pos;
    switch (heading) {
    case DOWN: {
        Left++;
        break;
    }
    case LEFT: {
        Left += mazeWidth;
        break;
    }
    case UP: {
        Left--;
        break;
    }
    case RIGHT: {
        Left -= mazeWidth;
    }
    }
}
void WheresAhead(int pos, Direction heading, int &ahead) {
    ahead = pos;
    switch ((heading)) {
    case DOWN: {
        ahead += mazeWidth;
        break;
    }
    case LEFT: {
        ahead--;
        break;
    }
    case UP: {
        ahead -= mazeWidth;
        break;
    }
    case RIGHT: {
        ahead++;
        break;
    }
    }
}

bool Wall(int pos) {
    return (maze[pos] == '#');
}

//	This function changes heading by turning right
//	Take current heading and adjust so that direction is to the right

void TurnRight(Direction &heading) {
    switch ((heading)) {
    case DOWN: {
        heading = LEFT;
        break;
    }
    case LEFT: {
        heading = UP;
        break;
    }
    case UP: {
        heading = RIGHT;
        break;
    }
    case RIGHT: {
        heading = DOWN;
        break;
    }
    }
}

//	This function changes position in the maze by determining
//	the next position in the current direction

void MoveForward(int &pos, Direction heading) {
    int other;
    WheresAhead(pos, heading, other);
    pos = other;
}

//	This function determines the position in the direction
//	currently heading

void TurnLeft(Direction &heading) {
    switch ((heading)) {
    case DOWN: {
        heading = RIGHT;
        break;
    }
    case LEFT: {
        heading = DOWN;
        break;
    }
    case UP: {
        heading = LEFT;
        break;
    }
    case RIGHT: {
        heading = UP;
        break;
    }
    }
}
// this is end
