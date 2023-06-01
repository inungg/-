#ifndef BLOCK_H
#define BLOCK_H

#include "Point.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

enum block_type {
    Block_t,
    Block_i,
    Block_o,
    Block_l,
    Block_j,
    Block_s,
    Block_z
};

enum move_direction {
    right = 1,
    left = -1
};

class Block {
private:
    enum block_type type;
    std::vector<Point> body;
    Point pos;


public:
    Block() = default;
    Block(Point pos);
    void fallDown();
    std::vector<Point> nextFallDownBody();
    void move(enum move_direction dir);
    std::vector<Point> nextMoveBody(enum move_direction dir);
    void rotate();
    std::vector<Point> nextRotateBody();

    std::vector<Point> getBody() { return body; }
    void setBody(std::vector<Point> body) { this->body = body; }

};

#endif
