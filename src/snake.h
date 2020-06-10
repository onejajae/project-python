#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <cstdlib>

#define TURN_LEFT 1
#define TURN_UP 2
#define TURN_DOWN 3
#define TURN_RIGHT 4

#define BLANK 0
#define WALL 1
#define IMMNUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6
#define GATE 7

struct snakePart
{
    int x,y;
    snakePart(int col, int row);
    snakePart();
};

class snakeClass {
    public:
    int points, delay, maxWidth, maxHeight;
    char direction, headPartchar, bodyPartchar, wallchar, immuneWallchar,
    growthItemchar, poisonItemchar, gatechar, airchar;
    bool getgrowth, getpoison;
    int ticks;
    int snakesize;
    int snakemap[30][30];
    int itemsum;
    snakePart gate[2];

    std::vector<snakePart> wallvt;
    std::vector<snakePart> snake;
    std::vector<snakePart> growthItem;
    std::vector<snakePart> poisonItem;

    int sizeofsnake();
    void putGrowthItem(); //몸 길이 증가 아이템
    void putPoisonItem(); //독 아이템
    void makegate(); // 게이트 생성
    bool collision(); //충돌
    void movesnake(int n=0); //뱀 움직이기
    void printmap();

    public:
        snakeClass();
        ~snakeClass();
        void start(); // start game
};

#endif
