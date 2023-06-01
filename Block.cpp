#include "Block.h"
using namespace std;
Block::Block(Point pos)//创建Block类的构造函数。根据给定的位置创建方块对象，并随机分配类型和颜色。
    :pos{ pos } {
    srand(time(0));
    type = static_cast<block_type>(rand() % 7);

    if (type == Block_t) {
        body = { pos, pos.shiftCopy(1, 0), pos.shiftCopy(-1, 0), pos.shiftCopy(0, 1) };
        for (auto& point : body)
            point.setColor(3);
    }
    else if (type == Block_i){
        body = { pos, pos.shiftCopy(0, -1), pos.shiftCopy(0, 1), pos.shiftCopy(0, 2) };
        for (auto& point : body)
            point.setColor(10);
    }

    else if (type == Block_o){
        body = { pos, pos.shiftCopy(0, 1), pos.shiftCopy(1, 0), pos.shiftCopy(1, 1) };
        for (auto& point : body)
            point.setColor(11);
}
    else if (type == Block_l) {
        body = { pos, pos.shiftCopy(0, 1), pos.shiftCopy(0, -1), pos.shiftCopy(1, -1) };
        for (auto& point : body)
            point.setColor(12);
    }
    else if (type == Block_j) {
        body = { pos, pos.shiftCopy(-1, 0), pos.shiftCopy(0, 1), pos.shiftCopy(0, 2) };
        for (auto& point : body)
            point.setColor(13);
    }
    else if (type == Block_s) {
        body = { pos, pos.shiftCopy(-1, 0), pos.shiftCopy(0, 1), pos.shiftCopy(1, 1) };
        for (auto& point : body)
            point.setColor(14);
    }
    else if (type == Block_z){
        body = { pos, pos.shiftCopy(1, 0), pos.shiftCopy(0, 1), pos.shiftCopy(-1, 1) };
        for (auto& point : body)
            point.setColor(15);
    }
}

void Block::fallDown() {//使方块向下移动一个单位。
    pos.move(0, -1);
    for (auto& point : body)
        point.move(0, -1);
}

vector<Point> Block::nextFallDownBody() {//返回方块向下移动一个单位后的新坐标集合。
    vector<Point> nextBody;
    for (const auto& point : body)
        nextBody.push_back(point.shiftCopy(0, -1));
    return nextBody;
}

void Block::move(enum move_direction dir) {//使方块在给定的移动方向上移动一个单位。
    pos.move(dir, 0);
    for (auto& point : body)
        point.move(dir, 0);
}

vector<Point> Block::nextMoveBody(enum move_direction dir) {//返回方块在给定的移动方向上移动一个单位后的新坐标集合。
    vector<Point> nextBody;
    for (const auto& point : body)
        nextBody.push_back(point.shiftCopy(dir, 0));
    return nextBody;
}

void Block::rotate() {
    for (auto& point : body) {
        int pointX = point.getX() - pos.getX();
        int pointY = point.getY() - pos.getY();
        point.setCoordinate((-1 * pointY) + pos.getX(), pointX + pos.getY());
    }
}

vector<Point> Block::nextRotateBody() {
    vector<Point> nextBody;
    for (const auto& point : body) {
        int pointX = point.getX() - pos.getX();
        int pointY = point.getY() - pos.getY();
        nextBody.push_back(Point((-1 * pointY) + pos.getX(), pointX + pos.getY()));
    }
    return nextBody;
}
