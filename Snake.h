#include <NonBlockingGame.h>

#include <iostream>

#include "Pair.h"
#include "Queue.h"

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

const int BOARD_SIZE = 20;

class SnakeGame : public NonBlockingGame {
public:
    SnakeGame(int assID, string username, string apikey)
        : NonBlockingGame(assID, username, apikey, BOARD_SIZE, BOARD_SIZE) {
        skipDeletingTailNodesCount = 0;
    }

    // Called by game.start() in main.
    virtual void gameLoop() override;

private:
    // Called by game.start() in main.
    virtual void initialize() override;

    void handleInput();
    void updateSnake();
    void plantTarget();
    void detectTarget();
    void detectDeath();
    void paintBoard();
    void paint();   // repaint everything

    void drawTarget();
    void drawSnake();

    // instance variables
    long frameTime;
    long nextFrameTime;
    int skipDeletingTailNodesCount;

    Pair<int> target;   // what the snake should eat.

    // tail of the queue is the head of the snake.
    // So, as the snake moves, add squares to the tail, and remove from the
    // head.
    Queue<Pair<int>> snake;

    enum Direction { East, West, South, North };
    Direction lastDir = Direction::East;
    Direction dir = Direction::East;
    int frame = 0;
};
