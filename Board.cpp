#include "Board.h"

Board::Board(int width, int height)
    :width{ width }, height{ height } {
    for (int i{ 0 }; i < width; i++)
        for (int j{ 0 }; j < height; j++)
            allPoints.push_back(Point(i, j));

    setBorder();
}

int Board::getWidth() { 
    return width; 
}

int Board::getHeight() { 
    return height; 
}

std::vector<Point> Board::getAllPoints() { 
    return allPoints; 
}

std::vector<Point> Board::getBuiltPoints() { 
    return builtPoints; 
}

void Board::setBuiltPoints(std::vector<Point> builtPoints) { 
    this->builtPoints = builtPoints; 
}
void Board::refresh() {
    setBorder();
    for (auto& allPnt : allPoints)
        for (auto builtPnt : builtPoints)
            if (allPnt == builtPnt)
                allPnt = builtPnt;    //seting the char of all_pnt to built pnt
}

void Board::setBorder() {
    for (auto& point : allPoints) {
        if (point.getX() == 0 || point.getY() == 0 || point.getX() == width - 1 || point.getY() == height - 1)
            point.setType('*');
        else
            point.setType(' ');
    }
}

void Board::insertToBuiltPoints(std::vector<Point> insertPoints) {
    builtPoints.insert(builtPoints.end(), insertPoints.begin(), insertPoints.end());
}

int Board::removeRow() {
    int removedRows{ 0 };
    int i{ 1 };
    while (i < height) {

        int builtPointsCount = std::count_if(builtPoints.begin(), builtPoints.end(), [i](const Point& point) {
            return (point.getY() == i);
            });

        if (builtPointsCount == (width - 2)) {
            removedRows++;

            // earse-remove idiom
            auto it = std::remove_if(builtPoints.begin(), builtPoints.end(), [i](Point point) {
                return (point.getY() == i);
                });
            builtPoints.erase(it, builtPoints.end());

            std::for_each(builtPoints.begin(), builtPoints.end(), [i](Point& point) {
                if (point.getY() > i)
                    point.move(0, -1);
                });

        }
        else
            i++;
    }

    return removedRows;
}
