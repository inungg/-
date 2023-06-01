#include "Game.h"

Game::Game(){
    score = 0; 
    speed = 200;
    run = true;

    do {
        system("cls");//清空控制台屏幕，用于刷新游戏界面
        board = Board(20, 20);
        running();
    } while (regame());

}

void Game::controls() {
    if (GetAsyncKeyState(VK_UP))
        checkedRotate();
    else if (GetAsyncKeyState(VK_DOWN))
        speed = 10;
    else if (GetAsyncKeyState(VK_RIGHT))
        checkedMove(right);
    else if (GetAsyncKeyState(VK_LEFT))
        checkedMove(left);
    else if (GetAsyncKeyState(VK_ESCAPE)) {
        run = false;
    }
}

void Game::running() {
    while (!gameOver() && run) {
        currBlock = Block(Point((board.getWidth() - 1) / 2, board.getHeight(), 'O'));//设置在游戏板中间的顶部位置
        while (!hitBuiltPointsDown()) {//当当前方块未触底时
            speed = 500;
            ClearScreen();
            currBlock.fallDown();
            score += board.removeRow();
            board.refresh();
            refreshFinalPoints();
            draw();
            controls();

            if (!run) {
                break;  // 退出游戏循环
            }

            Sleep(speed);//根据设定的速度暂停一段时间，控制方块下落的速度。
        }
    }
}
bool Game::hitBuiltPointsDown() {

    for (const auto& nextBlockPnt : currBlock.nextFallDownBody()) {//对于当前方块下一次下落的每个点，进行迭代循环。
        //hit the ground
        if (nextBlockPnt.getY() == 0) {//到达底部边界。
            board.insertToBuiltPoints(currBlock.getBody());//插入到已建立的方块集合中。
            return true;
        }
        //hit built points
        for (const auto& builtPnt : board.getBuiltPoints())//进行迭代循环。
            if (nextBlockPnt == builtPnt) {//如果重合。
                board.insertToBuiltPoints(currBlock.getBody());//将当前方块的所有点插入到已建立的方块集合中。
                return true;
            }
    }

    return false;
}

bool Game::gameOver() {
    for (const auto& pnt : board.getBuiltPoints())//对于已建立的方块集合中的每个点，进行迭代循环。
        if (pnt.getY() >= board.getHeight() - 2) {//判断当前点的Y坐标是否大于等于游戏板的高度减去边框2.
            return true;
        }
    return false;
}

bool Game::regame() {
    std::cout << "======Game over======" << std::endl;
    std::cout << "replay ?? (y/n) " << std::endl;
    char c{};
    bool isvalid{ false };
    do {
        std::cin >> c;
        if (c == 'y') {
            // 重新初始化游戏状态
            score = 0;
            speed = 500;
            run = true;
            return true;
        }
        else if (c == 'n') {
            // 设置退出游戏标志或其他逻辑
            return false;
        }
        else {
            std::cout << "invalid entry\n";
            isvalid = true;
        }
    } while (isvalid);
}

bool Game::checkedMove(enum move_direction dir) {
    for (const auto& nextBlockPnt : currBlock.nextMoveBody(dir)) {
        if (nextBlockPnt.getX() == 0 || nextBlockPnt.getX() == (board.getWidth() - 1))//判断左边界或右边界。
            return false;

        for (const auto& builtPnt : board.getBuiltPoints())//检查当前点是否与已建立的方块集合中的任何一个点重合。
            if (builtPnt == nextBlockPnt)
                return false;
    }

    currBlock.move(dir);
    return true;
}

bool Game::checkedRotate() {
    for (const auto& nextBlockPnt : currBlock.nextRotateBody()) {
        if (nextBlockPnt.getX() == 0 || nextBlockPnt.getX() == (board.getWidth() - 1))
            return false;  // 如果旋转后的方块超出了游戏板的左边界或右边界，则返回false表示无法旋转

        for (const auto& builtPnt : board.getBuiltPoints())
            if (builtPnt == nextBlockPnt)
                return false;  // 如果旋转后的方块与已建立的方块集合中的任何一个点重叠，则返回false表示无法旋转
    }

    currBlock.rotate();  // 若旋转没有冲突，则进行方块的旋转操作
    return true;  // 返回true表示旋转成功
}


void Game::draw() {
    for (int i = board.getHeight() - 1; i >= 0; i--) {
        for (int j = 0; j < board.getWidth(); j++) {
            auto it = std::find_if(finalPoints.begin(), finalPoints.end(), [j, i](const Point& c) {
                return c.getX() == j && c.getY() == i;
                });

            
            if (it != finalPoints.end()) {
                if (it->getType() == '*') {
                    std::cout << "*";
                }
                else if (it->getType() == 'O') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), it->getColor());
                std::cout << "0";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            }
                else
                    std::cout << " ";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }


    std::cout << "\nScore = " << score << std::endl;
    
}

void Game::refreshFinalPoints() {

    finalPoints = board.getAllPoints(); // 获取游戏板上的所有点，包括已建立的方块和当前方块
    for (auto& finalPnt : finalPoints)// 对于每一个游戏板上的点
        for (auto blockPnt : currBlock.getBody()) // 对于当前方块的每一个点
            if (finalPnt == blockPnt)// 如果游戏板上的点与当前方块的某个点重合
                finalPnt = blockPnt;// 更新游戏板上的点为当前方块的点
}

void Game::ClearScreen() {
    // Function which cleans the screen without flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
