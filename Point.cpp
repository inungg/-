   #include"Point.h"

    Point:: Point(){
        x=0;
        y=0;
        type=' ';
    } 
    Point::Point(int newX,int newY,char newType){
        x=newX;
        y=newY;
        type=newType;
    }
    int Point::getX()const{
        return x;
    }
    int Point::getY()const{
        return y;
    }
    char Point::getType()const{
        return type;
    }
    void Point::setType(char newType){
        type=newType;
    }
    Point Point::shiftCopy(int shiftX,int shiftY){
        return Point(x+shiftX,y+shiftY,type);
    }
    void Point::move(int moveX,int moveY){
        x+=moveX;
        y+=moveY;
    }
    void Point::setCoordinate(int newX,int newY){
        x=newX;
        y=newY;
    }
    bool Point::operator==(const Point &rhs)const{
        return (x==rhs.getX()&&y==rhs.getY());
    }
