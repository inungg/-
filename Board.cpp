#ifndef BOARD_H
#define BOARD_H

#include "Block.h"
#include <vector>
#include <algorithm>

class Board {
private:
    int width;
    int height;
    std::vector<Point> allPoints;
    std::vector<Point> builtPoints;
public:
    Board(int width=30, int height=30);

    int getWidth();
    int getHeight();
    std::vector<Point> getAllPoints();
    std::vector<Point> getBuiltPoints();
    void setBuiltPoints(std::vector<Point> builtPoints);
    void setBorder();

    void insertToBuiltPoints(std::vector<Point> insertPoints);
    int removeRow();
    void refresh();

};

#endif
