#ifndef POINT_H
#define POINT_H

class Point{
private:
    int x;
    int y;
    char type;

public:
    Point(int newX,int newY,char newType);
    Point();
    int getX()const;
    int getY()const;
    char getType()const;
    void setType(char newType);
    Point shiftCopy(int shiftX,int shiftY);
    void move(int moveX,int moveY);
    void setCoordinate(int newX,int newY);
    bool operator==(const Point &rhs)const;


};

#endif
