#ifndef BLOCK_H
#define BLOCK_H
#include"Point.h"
#include<vector>
#include <stdlib.h>
#include<time.h>

enum BlockType{
    Block_t,
    Block_i,
    Block_o,
    Block_l,
    Block_j,
    Block_s,
    Block_z
};

enum moveDirection{
    right=1,left=-1
};

class Block{
private:
    enum BlockType type;
    vector<Point> body;
    Point pos;

public:
    Block()=default;
    Block(Point pos);
    void fallDown();
    vector<Point> nextFallDownBody();
    void move(enum moveDirection dir);
    vector<Point> nextMoveBody(enum moveDirection dir);
    void rotate();
    vector<Point> nextRotateBody();
    vector<Point>getBody(){return body;}
    void setBody(vector<Point> body){this->body=body;}
};

#endif
