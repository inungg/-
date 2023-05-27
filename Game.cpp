#include "Game.h"

Game::Game(){
    score = 0; 
    speed = 200;
    run = true;

    do {
        system("cls");
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
    else if (GetAsyncKeyState('P')) {
        //run = gameOver();
    }
}

void Game::running() {
    while (!gameOver()) {
        currBlock = Block(Point((board.getWidth() - 1) / 2, board.getHeight(), 'O'));
        while (!hitBuiltPointsDown()) {
            speed = 500;
            ClearScreen();
            currBlock.fallDown();
            score += board.removeRow();
            board.refresh();
            refreshFinalPoints();
            draw();
            controls();
            Sleep(speed);

        }
    }
}

bool Game::hitBuiltPointsDown() {

    for (const auto& nextBlockPnt : currBlock.nextFallDownBody()) {
        //hit the ground
        if (nextBlockPnt.getY() == 0) {
            board.insertToBuiltPoints(currBlock.getBody());
            return true;
        }
        //hit built points
        for (const auto& builtPnt : board.getBuiltPoints())
            if (nextBlockPnt == builtPnt) {
                board.insertToBuiltPoints(currBlock.getBody());
                return true;
            }
    }

    return false;
}

bool Game::gameOver() {
    for (const auto& pnt : board.getBuiltPoints())
        if (pnt.getY() >= board.getHeight() - 2) {
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
        if (c == 'y')
            return true;
        else if (c == 'n')
            return false;
        else {
            std::cout << "invalid entry\n";
            isvalid = true;
        }
    } while (isvalid);
}

bool Game::checkedMove(enum move_direction dir) {
    for (const auto& nextBlockPnt : currBlock.nextMoveBody(dir)) {
        if (nextBlockPnt.getX() == 0 || nextBlockPnt.getX() == (board.getWidth() - 1))
            return false;

        for (const auto& builtPnt : board.getBuiltPoints())
            if (builtPnt == nextBlockPnt)
                return false;
    }

    currBlock.move(dir);
    return true;
}

bool Game::checkedRotate() {
    for (const auto& nextBlockPnt : currBlock.nextRotateBody()) {
        if (nextBlockPnt.getX() == 0 || nextBlockPnt.getX() == (board.getWidth() - 1))
            return false;

        for (const auto& builtPnt : board.getBuiltPoints())
            if (builtPnt == nextBlockPnt)
                return false;
    }

    currBlock.rotate();
    return true;
}

void Game::draw() {
    for (int i = board.getHeight() - 1; i >= 0; i--) {
        for (int j = 0; j < board.getWidth(); j++) {
            auto it = std::find_if(finalPoints.begin(), finalPoints.end(), [j, i](const Point& c) {
                return c.getX() == j && c.getY() == i;
                });

            if (it != finalPoints.end()) {
                if (it->getType() == '#')
                    std::cout << "*";
                else if (it->getType() == 'O')
                    std::cout << "0";
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

    finalPoints = board.getAllPoints();
    for (auto& finalPnt : finalPoints)
        for (auto blockPnt : currBlock.getBody())
            if (finalPnt == blockPnt)
                finalPnt = blockPnt;
}

void Game::ClearScreen() {
    // Function which cleans the screen without flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
