#include "Block.h"
using namespace std;
Block::Block(Point pos)
    :pos{pos} {
        srand(time(0));
        type=static_cast<BlockType>(rand()%7);
        if(type==Block_t)
            body={pos,pos.shiftCopy(1,0),pos.shiftCopy(-1,0),pos.shiftCopy(0,1)};
        else if(type==Block_i)
            body={pos,pos.shiftCopy(0,-1),pos.shiftCopy(0,1),pos.shiftCopy(0,2)};
        else if(type==Block_o)
            body={pos,pos.shiftCopy(0,1),pos.shiftCopy(1,0),pos.shiftCopy(1,1)};
        else if(type==Block_l)
            body={pos,pos.shiftCopy(0,1),pos.shiftCopy(0,-1),pos.shiftCopy(1,-1)};
        else if(type==Block_j)
            body={pos,pos.shiftCopy(-1,0),pos.shiftCopy(0,1),pos.shiftCopy(0,2)};
        else if(type==Block_s)
            body={pos,pos.shiftCopy(-1,0),pos.shiftCopy(0,1),pos.shiftCopy(1,1)};
        else if(type==Block_z)
            body={pos,pos.shiftCopy(1.0),pos.shiftCopy(0,1),pos.shiftCopy(-1,1)};

}
    void Block::fallDown(){
        pos.move(0,-1);
        for(auto &point:body)
            point.move(0,-1);
    }
    vector<Point> Block::nextFallDownBody(){
        vector<Point> nextBody;
        for(const auto &point:body)
            nextBody.push_back(point.shiftCopy(0,-1));

        return nextBody;
    }
    void Block::move(enum moveDirection dir){
        pos.move(dir,0);
        for(auto &point:body)
            point.move(dir,0);
    }
    vector<Point> Block::nextMoveBody(enum moveDirection dir){
        vector<Point> nextBody;
        for(const auto &point:body)
            nextBody.push_back(point.shiftCopy(dir,0));

        return nextBody;
    }
    void Block::rotate(){
        for(auto &point:body)
            nextBody.push_back(point.shiftCopy(dir,0));

        return nextBody;
    }
    vector<Point> Block::nextRotateBody(){
        vector<Point> nextBody;
        for(const auto &point:body){
            int pointX=point.getX()-pos.getX();
            int pointY=point.getY()-pos.getY();
            nextBody.push_back(Point((-1*pointY)+pos.getX(),pointX+pos.getY()));
        }
        return nextBody;
    }
    vector<Point>getBody(){return body;}
    void setBody(vector<Point> body){this->body=body;}
