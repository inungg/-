#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "windows.h"

#include "Point.h"
#include "Block.h"
#include "Board.h"

class Game {
private:
    Board board;
    Block currBlock;
    std::vector<Point> finalPoints;
    int score;
    int speed;
    bool run;
public:

    Game();
    void controls();
    void running();
    bool hitBuiltPointsDown();

    bool checkedMove(enum move_direction dir);
    bool checkedRotate();

    void draw();
    void refreshFinalPoints();

    void ClearScreen();
    bool gameOver();
    bool regame();


};


#endif
