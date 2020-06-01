#ifndef SNAKE_H
#define SNAKE_H
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>

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
    growthItemchar, poisonItemchar;
    bool getgrowth, getpoison;
    int ticks;
    snakePart growthItem[2];
    snakePart poisonItem[2];

    std::vector<snakePart> snake;

    void putGrowthItem(int n); //몸 길이 증가 아이템
    void putPoisonItem(int n); //독 아이템
    bool collision(); //충돌
    void movesnake(); //뱀 움직이기
    void draw_map();

    public:
        snakeClass();
        ~snakeClass();
        void start(); // start game
};

#endif