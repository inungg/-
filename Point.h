#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
    int x;
    int y;
    char type;
    int color;
public:
    Point(int x = 0, int y = 0, char type = ' ');

    int getX() const;
    int getY() const;
    char getType() const;
    void setType(char newType);


    Point shiftCopy(int shiftX, int shiftY) const;
    void move(int moveX, int moveY);
    void setCoordinate(int newX, int newY);

    bool operator==(const Point& rhs) const;
    int getColor()const;
    void setColor(int c);
};

#endif
