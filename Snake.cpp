
#include <NonBlockingGame.h>
#include <time.h>
#include <iostream>

#include "Snake.h"

//
//  The purpose of this assignment is to learn to
// 1. The classic game of Snake.
//    Move a "snake" (line of sprites) along a 2D grid attempting to run over a
//    randomly placed object to help it grow.
//    If it runs into itself the game is over and the player has lost.
//    The object of the game is to make the snake as big as possible.
// 2. Practice using a complex data structure -- a Queue of Pairs of integers.
// 3. Work with a game engine.
//
using namespace bridges::game;
using namespace std;

void SnakeGame::initialize() {
    srand(time(NULL));

    // as the snake moves, its tail won't be deleted for 2 steps, so
    // initially the snake will be 3 segments long.
    skipDeletingTailNodesCount = 2;

    // start the snake in the middle, going east.
    snake.add(Pair<int>(BOARD_SIZE / 2, BOARD_SIZE / 2));
    dir = Direction::East;
    lastDir = dir;

    plantTarget();
    paint();
}

// read the keyboard and store the direction we are moving next in the
// instance variable "dir"
void SnakeGame::handleInput() {
    if (keyLeft() && dir != Direction::East && lastDir != Direction::East) {
        dir = Direction::West;
    } else if (keyUp() && dir != Direction::South &&
               lastDir != Direction::South) {
        dir = Direction::North;
    } else if (keyDown() && dir != Direction::North &&
               lastDir != Direction::South) {
        dir = Direction::South;
    } else if (keyRight() && dir != Direction::West &&
               lastDir != Direction::West) {
        dir = Direction::East;
    }
}

// update snake position -- delete node from head of queue (tail of snake)
// and add new node to tail of queue (head of snake);
void SnakeGame::updateSnake() {
    // TODO:
    // if skipDeletingTailNodesCount is 0, remove the tail of the snake.
    // otherwise, decrement skipDeletingTailNodesCount.

    // based on the direction, compute the new head of the snake
    // by getting the current head, altering it, and adding it.
    Pair<int> head = // TODO: finish the code here.

    int x, y;
    switch (dir) {
        case Direction::North:
            x = head.getFirst();
            if (--x < 0) {
                x = BOARD_SIZE - 1;
            }
            head.setFirst(x);
            break;
        case Direction::South:
            x = head.getFirst();
            x = (x + 1) % BOARD_SIZE;  // wrap around right to left.
            head.setFirst(x);
            break;
        case Direction::East:
            y = head.getSecond();
            y = (y + 1) % BOARD_SIZE;  // wrap around bottom to top.
            head.setSecond(y);
            break;
        case Direction::West: {
            y = head.getSecond();
            if (--y < 0) {
                y = BOARD_SIZE - 1;
            }
            head.setSecond(y);
            break;
        }
    }

    // TODO: add the new head to the snake
}

void SnakeGame::plantTarget() {
    int x;
    int y;

    // TODO:
    // repeatedly:
    //   get a random x and random y, within the BOARD_SIZE
    //      o use rand() and the modulo operator
    //   if this x,y location is not part of the snake already,
    //      break out of the loop and store x, y in "target"
}

// check if snake has found the target
void SnakeGame::detectTarget() {

    // TODO:
    // get the head of the snake from the queue.
    // if the head is the same as the target:
    //    use the following code to erase the target.
    //    drawSymbol(target.getFirst(), target.getSecond(), NamedSymbol::none,
    //           NamedColor::red);
    //    call plantTarget() to put the target down again in a new random location.
}

// check if snake ate itself! Yuk!
void SnakeGame::detectDeath() {
    // TODO:
    // We have already put the new block on the head of the snake,
    // so we need to check if that block  is somewhere else already in the body of the snake.
    // Implementation:
    // if the head of the snake is already in the body of the snake, call exit(0) to end the game.
}

void SnakeGame::paintBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i % 2 == j % 2) {
                setBGColor(i, j, NamedColor::green);
            } else {
                setBGColor(i, j, NamedColor::forestgreen);
            }
        }
    }
}

// redraw
void SnakeGame::paint() {
    paintBoard();
    drawSnake();
    drawTarget();
}

void SnakeGame::drawTarget() {
    // show the number "1" as the target. Option: make it random from 1 to 9 and
    // make the snake longer by that amount when it is eaten.
    drawSymbol(target.getFirst(), target.getSecond(), NamedSymbol::one,
               NamedColor::red);
}

void SnakeGame::drawSnake() {
    // TODO:
    // iterate through the snake queue, using the queue iterator.
    //   for each item (a Pair object), call setBGColor to set the square to NamedColor::silver.
    // After the loop, call setBGColor again to set the head of the snake to white.
}

// handle input, check if target was detected, update position, redraw,
// detect if snake ate itself
void SnakeGame::gameLoop() {
    frame += 1;
    handleInput();
    if (frame >= 5) {           // this could be changed to make the game run faster...
        lastDir = dir;
        updateSnake();
        detectTarget();
        detectDeath();
        paint();
        frame = 0;
    }
}

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: snake <bridges_username> <bridges_user_id>" << endl;
        exit(-1);
    }

    SnakeGame game(1111, argv[1], argv[2]);

    game.start();
}
