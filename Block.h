#ifndef BLOCK_H
#define BLOCK_H

#include "Cell.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

enum block_type {
    t_block,
    i_block,
    o_block,
    l_block,
    j_block,
    s_block,
    z_block
};

enum move_direction {
    right = 1,
    left = -1
};

class Block {
private:
    enum block_type type;
    std::vector<Cell> body;
    Cell pos;


public:
    Block() = default;
    Block(Cell pos);
    void fall_down();
    std::vector<Cell> next_fall_down_body();
    void move(enum move_direction dir);
    std::vector<Cell> next_move_body(enum move_direction dir);
    void rotate();
    std::vector<Cell> next_rotate_body();

    std::vector<Cell> get_body() { return body; }
    void set_body(std::vector<Cell> body) { this->body = body; }

};

#endif
