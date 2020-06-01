#include "snake.h"
#include "ncurses.h"
#include <random>
#include "unistd.h"

/*
TODO LIST
-make a menu
-top list ??
-colors 구현
-Immune Wall 구현
*/

//constructor
snakePart::snakePart(int col, int row) {
    x = col;
    y = row;
}
//constructor
snakePart::snakePart() {
    x = 0;
    y = 0;
}

void snakeClass::putGrowthItem(int n) {
    while(1) {
        int tmpx=(rand()%(maxWidth-1)) +1;
        int tmpy=(rand()%(maxHeight-1)) +1;
        for(int i=0; i<snake.size(); i++) {
            if(snake[i].x==tmpx && snake[i].y==tmpy) continue;
        }

        for(int i=0; i<3;i++){
          if(tmpx==poisonItem[i].x&&tmpy==poisonItem[i].y) continue;
        }

        growthItem[n].x = tmpx;
        growthItem[n].y = tmpy;
        break;
    }
    move(growthItem[n].y,growthItem[n].x);
    addch(growthItemchar);
    refresh();
}

void snakeClass::putPoisonItem(int n) {
    while(1) {
        int tmpx=(rand()%(maxWidth-1)) +1;
        int tmpy=(rand()%(maxHeight-1)) +1;
        for(int i=0; i<snake.size(); i++) {
            if(snake[i].x==tmpx && snake[i].y==tmpy) continue;
        }

        for(int i=0; i<3;i++){
          if(tmpx==growthItem[i].x&&tmpy==growthItem[i].y) continue;
        }

        poisonItem[n].x = tmpx;
        poisonItem[n].y = tmpy;
        break;
    }
    move(poisonItem[n].y,poisonItem[n].x);
    addch(poisonItemchar);
    refresh();
}

//아직 구현 못함
bool snakeClass::collision() {
    //벽에 머리가 부딪히는 경우
    if(snake[0].x==0 || snake[0].x==maxWidth ||
     snake[0].y==0 || snake[0].y==maxHeight) return true;

    for(int i=2; i<snake.size(); i++) {
        if(snake[0].x==snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }


    //growthItem 먹었을 때
    for(int j=0; j<2; j++) {
        if(snake[0].x==growthItem[j].x && snake[0].y==growthItem[j].y) {
            getgrowth = true;
            putGrowthItem(j);
            points+=10;
            break;
        }
        else {
            getgrowth = false;
        }
    }

    //poisonItem 먹었을 때
    for(int j=0; j<2; j++) {
        if(snake[0].x==poisonItem[j].x && snake[0].y==poisonItem[j].y) {
            getpoison = true;
            putPoisonItem(j);
            points-=10;
            break;
        }
        else {
            getpoison = false;
        }
    }

    //뱀의 몸의 길이가 3보다 작아질 경우
    if(snake.size()<3) return true;

    return false;
}

void snakeClass::movesnake() {

    int tmp=getch();
    switch (tmp)
    {
    case KEY_LEFT:
        if(direction != 'r') {
            direction='l';
        }
        break;
    case KEY_UP:
        if(direction != 'd') {
            direction = 'u';
        }
        break;
    case KEY_DOWN:
        if(direction != 'u') {
            direction = 'd';
        }
        break;
    case KEY_RIGHT:
        if(direction != 'l') {
            direction = 'r';
        }
        break;
    case KEY_BACKSPACE:
        direction = 'q';
        break;
    }

    if(!getgrowth ) {
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(getpoison) {
      move(snake[snake.size()-1].y, snake[snake.size()-1].x);
      addch(' ');
      refresh();
      snake.pop_back();
    }
    if(direction == 'l') {
        snake.insert(snake.begin(), snakePart(snake[0].x-1,snake[0].y));
    }
    else if(direction =='r') {
        snake.insert(snake.begin(), snakePart(snake[0].x+1,snake[0].y));
    }
    else if(direction == 'u') {
        snake.insert(snake.begin(), snakePart(snake[0].x,snake[0].y-1));
    }
    else if(direction == 'd') {
        snake.insert(snake.begin(), snakePart(snake[0].x,snake[0].y+1));
    }

    for(int i=0; i<snake.size();i++) {
        move(snake[i].y, snake[i].x);
        if(i==0) addch(headPartchar);
        else addch(bodyPartchar);
    }
    refresh();
}

snakeClass::snakeClass() {
    initscr();
    resize_term(100,100);
    nodelay(stdscr,true); //the getch() not wait until the user press a key
    keypad(stdscr,true);
    noecho();
    curs_set(0);

    maxWidth = 60;
    maxHeight = 30;

    //아이템 위치 초기화
    for(int k=0; k<=1; k++) {
        growthItem[k].x = 0;
        growthItem[k].y = 0;
        poisonItem[k].x = 0;
        poisonItem[k].y = 0;
    }

    //맵, 뱀 모양 초기화
    headPartchar = 'o';
    bodyPartchar = '*';
    wallchar = '§';
    immuneWallchar = '#';
    growthItemchar = 'O';
    poisonItemchar = 'X';

    for(int i=0; i<3; i++) {
        snake.push_back(snakePart(maxWidth/2+i, maxHeight/2));
    }

    points = 0;
    ticks = 200000;
    getgrowth = false;
    getpoison = false;
    direction ='l'; //default is left
    srand(time(NULL));

    //make Wall and immuneWall
    for(int i=0; i<maxWidth+1; i++) {//아래
      move(maxHeight,i);
      if(i==0||i==maxWidth) addch(immuneWallchar);
      else {addch(wallchar);}
    }
    for(int j=0; j<maxHeight+1; j++) {//왼쪽
      move(j,0);
      if(j==0||j==maxHeight) addch(immuneWallchar);
      else {addch(wallchar);}
    }
    for(int i=0; i<maxWidth+1; i++) {//위
      move(0,i);
      if(i==0||i==maxWidth) addch(immuneWallchar);
      else {addch(wallchar);}
    }
    for(int j=0; j<maxHeight+1; j++) {//오른쪽
      move(j,maxWidth);
      if(j==0||j==maxHeight) addch(immuneWallchar);
      else {addch(wallchar);}
    }


    //draw snake
    for(int k=0; k<snake.size(); k++) {
        move(snake[k].y, snake[k].x);
        if(k == 0) addch(headPartchar);
        else addch(bodyPartchar);
    }
    // printw("%d",points);
    putGrowthItem(0);
    putGrowthItem(1);
    putPoisonItem(0);
    putPoisonItem(1);
    refresh();
}

snakeClass::~snakeClass() {
    nodelay(stdscr, false);
    getch();
    endwin();
}

void snakeClass::start() {
    while(true) {
        if(collision()) {
            // move(maxWidth/2-4, maxHeight/2);
            move(12,36);
            printw("Game Over");
            break;
        }

        movesnake();
        if(direction=='q') {
            break;
        }
        usleep(ticks); //ticks 마이크로초 동안 대기
    }

}