#include <random>
#include "snake.h"

/*
TODO LIST
-make a menu
-top list ??
-colors 구현
-Immune Wall 구현
*/

//constructor
snakePart::snakePart(int row, int col) {
    y = row;
    x = col;
}
//constructor
snakePart::snakePart() {
    x = 0;
    y = 0;
}

int snakeClass::sizeofsnake(){
  return snake.size();
}

void snakeClass::putGrowthItem() {
  while(1) {
      int y=(rand()%(maxHeight-1)) +1;
      int x=(rand()%(maxWidth-1)) +1;

      if(snakemap[y][x]!=0) continue;
      growthItem.push_back(snakePart(y,x));
      snakemap[y][x]=5;
      itemsum++;
      break;
  }
}

void snakeClass::putPoisonItem() {
  while(1) {
      int y=(rand()%(maxHeight-1)) +1;
      int x=(rand()%(maxWidth-1)) +1;

      if(snakemap[y][x]!=0) continue;
      poisonItem.push_back(snakePart(y,x));
      snakemap[y][x]=6;
      itemsum++;
      break;
  }
}

void snakeClass::makegate() {
  while(1){
    int tempa = rand()&wallvt.size();
    int tempb = rand()%wallvt.size();
    if(tempa==tempb) continue;

    gate[0] = wallvt[tempa];
    gate[1] = wallvt[tempb];
    snakemap[gate[0].y][gate[0].x] = 7;
    snakemap[gate[1].y][gate[1].x] = 7;
    break;
  }
}

bool snakeClass::collision() {
    //벽에 머리가 부딪히는 경우
    for(int i=0;i<wallvt.size();i++){
      if(snake[0].x==wallvt[i].x && snake[0].y==wallvt[i].y) return true;
    }

    //자기 몸에 부딪히는 경우
    for(int i=2; i<snake.size(); i++) {
        if(snake[0].x==snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    //growthItem 먹었을 때
    for(int i=0; i<growthItem.size(); i++) {
        if(snake[0].x==growthItem[i].x && snake[0].y==growthItem[i].y) {
            getgrowth = true;
            points+=10;
            itemsum--;
            break;
        }
        else {
            getgrowth = false;
        }
    }

    //poisonItem 먹었을 때
    for(int i=0; i<poisonItem.size(); i++) {
        if(snake[0].x==poisonItem[i].x && snake[0].y==poisonItem[i].y) {
            getpoison = true;
            points-=10;
            itemsum--;
            break;
        }
        else {
            getpoison = false;
        }
    }

    //뱀의 몸의 길이가 3보다 작아질 경우
    if(sizeofsnake()<3) return true;

    return false;
}

void snakeClass::movesnake(int n) {

    switch (n)
    {
    case TURN_LEFT: //왼쪽
        if(direction != 'r') {
            direction='l';
        }
        break;
    case TURN_UP://위
        if(direction != 'd') {
            direction = 'u';
        }
        break;
    case TURN_DOWN://아래
        if(direction != 'u') {
            direction = 'd';
        }
        break;
    case TURN_RIGHT://오른쪽
        if(direction != 'l') {
            direction = 'r';
        }
        break;
    }

    if(direction == 'l') {
      snake.insert(snake.begin(), snakePart(snake[0].y,snake[0].x-1));
    }
    else if(direction =='r') {
      snake.insert(snake.begin(), snakePart(snake[0].y,snake[0].x+1));
    }
    else if(direction == 'u') {
      snake.insert(snake.begin(), snakePart(snake[0].y-1,snake[0].x));
    }
    else if(direction == 'd') {
      snake.insert(snake.begin(), snakePart(snake[0].y+1,snake[0].x));
    }


    for(int i=0; i<snake.size(); i++){
      if(i==0) snakemap[snake[i].y][snake[i].x]=3;
      else snakemap[snake[i].y][snake[i].x]=4;
    }

    //grow아이템
    if(!getgrowth){//안 먹었을 때
      snakemap[snake.back().y][snake.back().x] = 0;
      snake.pop_back();
    }else{//먹엇을 때
      for(int i =0; i<growthItem.size();i++){
        if(growthItem[i].y==snake[0].y && growthItem[i].x==snake[0].x) growthItem.erase(growthItem.begin()+i);
      }
    }

    //poison아이템
    if(getpoison){//먹었을 때
      snakemap[snake.back().y][snake.back().x] = 0;
      snake.pop_back();
      for(int i =0; i<poisonItem.size();i++){
        if(poisonItem[i].y==snake[0].y && poisonItem[i].x==snake[0].x) poisonItem.erase(growthItem.begin()+i);
      }
    }

    while(1){
      if(itemsum<3){
        int k=rand()%2;
        switch (k) {
          case 0:
          putGrowthItem();
          break;

          case 1:
          putPoisonItem();
          break;
        }
      }else break;
    }
}

snakeClass::snakeClass() {
    maxWidth = MAX_WIDTH;
    maxHeight = MAX_HEIGHT;

    //배열 초기화
    for(int i=0; i<maxHeight; i++){
      for(int j=0; j<maxWidth; j++){
        snakemap[i][j] = 0;
      }
    }

    //아이템개수 초기화

    // //맵, 뱀 모양 초기화
    // airchar = ' ';
    // headPartchar = 'o';
    // bodyPartchar = '*';
    // wallchar = '§';
    // immuneWallchar = '#';
    // growthItemchar = 'O';
    // poisonItemchar = 'X';
    // gatechar = '0';

    //snake 생성
    for(int i=0; i<3; i++) {
        snake.push_back(snakePart(maxHeight/2, maxWidth/2+i));
    }


    snakesize = snake.size();
    itemsum =0;
    points = 0;
    ticks = 200000;
    getgrowth = false;
    getpoison = false;
    direction ='u'; //default is left
    srand(time(NULL));

    //make Wall and immuneWall
    for(int j=0; j<maxWidth; j++) { //위
      if(j==0||j==maxWidth-1) snakemap[0][j] = 2;
      else {
        snakemap[0][j] = 1;
        wallvt.push_back(snakePart(0,j));
      }
    }
    for(int j=0; j<maxWidth; j++) { //아래
      if(j==0||j==maxWidth-1) snakemap[maxHeight-1][j]=2;
      else {
        snakemap[maxHeight-1][j]=1;
        wallvt.push_back(snakePart(maxHeight-1,j));
      }
    }
    for(int i=0; i<maxHeight; i++) { //왼쪽
      if(i==0||i==maxHeight-1) snakemap[i][0]=2;
      else {
        snakemap[i][0]=1;
        wallvt.push_back(snakePart(i,0));
      }
    }
    for(int i=0; i<maxHeight; i++) { //오른쪽
      if(i==0||i==maxHeight-1) {
        snakemap[i][maxWidth-1] = 2;
      }else {
        snakemap[i][maxWidth-1] = 1;
        wallvt.push_back(snakePart(i,maxWidth-1));
      }
    }


    //make snake
    for(int i=0; i<snake.size(); i++) {
        if(i == 0) snakemap[snake[i].y][snake[i].x] = 3;
        else snakemap[snake[i].y][snake[i].x] = 4;
    }

    //putitem
    putGrowthItem();
    for(int i=0; i<2; i++) {
      int k=rand()%2;
      switch (k) {
        case 0:
        putGrowthItem();
        break;

        case 1:
        putPoisonItem();
        break;
      }
    }

    makegate();

}

snakeClass::~snakeClass() {
}
