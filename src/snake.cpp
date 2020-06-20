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



void snakeClass::meetgate(){
  for(int i=0; i<2;i++){
    for(int j=0; j<snake.size(); j++){
      if(snake[j].y==gate[i].y && snake[j].x==gate[i].x){
        if(j==0) gatestate =i;
      }else{
        gatestate =2;
      }
    }
  }
}

void snakeClass::tpsnake(int n){
  switch (n) {
    case 0:
      for(int i=0; i<snake.size();i++){
        if(gate[0].y==snake[i].y && gate[0].x==snake[i].x){
          switch (direction) {
            case 'u':
              if(snakemap[gate[1].y -1][gate[1].x]!=1 && snakemap[gate[1].y -1][gate[1].x]!=9){
                snake[i].y = gate[1].y -1;
                snake[i].x = gate[1].x;
                direction = 'u';
              }else if(snakemap[gate[1].y][gate[1].x +1]!=1 && snakemap[gate[1].y][gate[1].x +1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x +1;
                direction = 'r';
              }else if(snakemap[gate[0].y][gate[1].x -1]!=1 && snakemap[gate[1].y][gate[0].x -1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x -1;
                direction = 'l';
              }else{
                snake[i].y = gate[1].y +1;
                snake[i].x = gate[1].x;
                direction = 'd';
              }
              break;
            case 'd':
              if(snakemap[gate[1].y +1][gate[1].x]!=1 && snakemap[gate[1].y +1][gate[1].x]!=9){
                snake[i].y = gate[1].y +1;
                snake[i].x = gate[1].x;
                direction = 'd';
              }else if(snakemap[gate[1].y][gate[1].x -1]!=1 && snakemap[gate[1].y][gate[1].x -1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x -1;
                direction = 'l';
              }else if(snakemap[gate[1].y][gate[1].x +1]!=1 && snakemap[gate[1].y][gate[1].x +1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x +1;
                direction = 'r';
              }else{
                snake[i].y = gate[1].y -1;
                snake[i].x = gate[1].x;
                direction = 'u';
              }
              break;
            case 'l':
              if(snakemap[gate[1].y][gate[1].x-1]!=1 && snakemap[gate[1].y][gate[1].x -1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x -1;
                direction = 'l';
              }else if(snakemap[gate[1].y-1][gate[1].x]!=1 && snakemap[gate[1].y -1][gate[1].x]!=9){
                snake[i].y = gate[1].y -1;
                snake[i].x = gate[1].x ;
                direction = 'u';
              }else if(snakemap[gate[1].y +1][gate[1].x]!=1 && snakemap[gate[1].y +1][gate[1].x]!=9){
                snake[i].y = gate[1].y +1;
                snake[i].x = gate[1].x;
                direction = 'd';
              }else{
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x +1;
                direction = 'r';
              }
              break;
            case 'r':
              if(snakemap[gate[1].y][gate[1].x +1]!=1 && snakemap[gate[1].y][gate[1].x +1]!=9){
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x +1;
                direction = 'r';
              }else if(snakemap[gate[1].y +1][gate[1].x]!=1 && snakemap[gate[1].y +1][gate[1].x]!=9){
                snake[i].y = gate[1].y +1;
                snake[i].x = gate[1].x ;
                direction = 'd';
              }else if(snakemap[gate[1].y -1][gate[1].x]!=1 && snakemap[gate[1].y -1][gate[1].x]!=9){
                snake[i].y = gate[1].y -1;
                snake[i].x = gate[1].x;
                direction = 'u';
              }else{
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x -1;
                direction = 'l';
              }
              break;
          }
        }
      }
      break;
    case 1:
      for(int i=0; i<snake.size();i++){
        if(gate[1].y==snake[i].y && gate[1].x==snake[i].x){
          switch (direction) {
            case 'u':
              if(snakemap[gate[0].y -1][gate[0].x]!=1 && snakemap[gate[0].y -1][gate[0].x]!=9){
                snake[i].y = gate[0].y -1;
                snake[i].x = gate[0].x;
                direction = 'u';
              }else if(snakemap[gate[0].y][gate[0].x +1]!=1 && snakemap[gate[0].y][gate[0].x +1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x +1;
                direction = 'r';
              }else if(snakemap[gate[0].y][gate[0].x -1]!=1 && snakemap[gate[0].y][gate[0].x -1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x -1;
                direction = 'l';
              }else{
                snake[i].y = gate[0].y +1;
                snake[i].x = gate[0].x;
                direction = 'd';
              }
              break;
            case 'd':
              if(snakemap[gate[0].y +1][gate[0].x]!=1 && snakemap[gate[0].y +1][gate[0].x]!=9){
                snake[i].y = gate[0].y +1;
                snake[i].x = gate[0].x;
                direction = 'd';
              }else if(snakemap[gate[0].y][gate[0].x -1]!=1 && snakemap[gate[0].y][gate[0].x -1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x -1;
                direction = 'l';
              }else if(snakemap[gate[0].y][gate[0].x +1]!=1 && snakemap[gate[0].y][gate[0].x +1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x +1;
                direction = 'r';
              }else{
                snake[i].y = gate[0].y -1;
                snake[i].x = gate[0].x;
                direction = 'u';
              }
              break;
            case 'l':
              if(snakemap[gate[0].y][gate[0].x-1]!=1 && snakemap[gate[0].y][gate[0].x -1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x -1;
                direction = 'l';
              }else if(snakemap[gate[0].y-1][gate[0].x]!=1 && snakemap[gate[0].y -1][gate[0].x]!=9){
                snake[i].y = gate[0].y -1;
                snake[i].x = gate[0].x ;
                direction = 'u';
              }else if(snakemap[gate[0].y +1][gate[0].x]!=1 && snakemap[gate[0].y +1][gate[0].x]!=9){
                snake[i].y = gate[0].y +1;
                snake[i].x = gate[0].x;
                direction = 'd';
              }else{
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x +1;
                direction = 'r';
              }
              break;
            case 'r':
              if(snakemap[gate[0].y][gate[0].x +1]!=1 && snakemap[gate[0].y][gate[0].x +1]!=9){
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x +1;
                direction = 'r';
              }else if(snakemap[gate[0].y +1][gate[0].x]!=1 && snakemap[gate[0].y +1][gate[0].x]!=9){
                snake[i].y = gate[0].y +1;
                snake[i].x = gate[0].x ;
                direction = 'd';
              }else if(snakemap[gate[0].y -1][gate[0].x]!=1 && snakemap[gate[0].y -1][gate[0].x]!=9){
                snake[i].y = gate[0].y -1;
                snake[i].x = gate[0].x;
                direction = 'u';
              }else{
                snake[i].y = gate[0].y;
                snake[i].x = gate[0].x -1;
                direction = 'l';
              }
              break;
          }
        }
      }
      break;
    case 2:
      break;
  }
}


void snakeClass::putGrowthItem(int n) {
  while(1) {
      int y=(rand()%(maxHeight-1)) +1;
      int x=(rand()%(maxWidth-1)) +1;

      if(snakemap[y][x]!=0) continue;

      growthItem[n].y = y;
      growthItem[n].x = x;
      snakemap[y][x]=5;
      break;
  }
}

void snakeClass::putPoisonItem(int n) {
  while(1) {
      int y=(rand()%(maxHeight-1)) +1;
      int x=(rand()%(maxWidth-1)) +1;

      if(snakemap[y][x]!=0) continue;

      poisonItem[n].y = y;
      poisonItem[n].x = x;
      snakemap[y][x]=6;
      break;
  }
}

void snakeClass::makegate() {
  while(1){
    int tempa = 1+rand()&wallvt.size()-2;
    int tempb = 1+rand()%wallvt.size()-2;
    if(tempa==tempb) continue;

    gate[0] = wallvt[tempa];
    gate[1] = wallvt[tempb];

    if (snakemap[gate[0].y][gate[0].x] == IMMNUNE_WALL) continue;
    if (snakemap[gate[1].y][gate[1].x] == IMMNUNE_WALL) continue;

    snakemap[gate[0].y][gate[0].x] = 7;
    snakemap[gate[1].y][gate[1].x] = 7;
    break;
  }
  // for (int i=0; i<wallvt.size(); i++) if (gate[0].x == wallvt[i].x && gate[0].y == wallvt[i].y) wallvt.erase(wallvt.begin()+i);
  // for (int i=0; i<wallvt.size(); i++) if (gate[1].x == wallvt[i].x && gate[1].y == wallvt[i].y) wallvt.erase(wallvt.begin()+i);
  
}

bool snakeClass::collision() {

    meetgate();

    //벽에 머리가 부딪히는 경우
    if(gatestate==2){
      for(int i=0;i<wallvt.size();i++){
        if(snake[0].x==wallvt[i].x && snake[0].y==wallvt[i].y) return true;
      }
    }


    //자기 몸에 부딪히는 경우
    for(int i=2; i<snake.size(); i++) {
        if(snake[0].x==snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    //growthItem 먹었을 때
    for(int i=0; i<2; i++) {
        if(snake[0].x==growthItem[i].x && snake[0].y==growthItem[i].y) {
            getgrowth = true;
            //points+=10;
            break;
        }
        else {
            getgrowth = false;
        }
    }

    //poisonItem 먹었을 때
    for(int i=0; i<2; i++) {
        if(snake[0].x==poisonItem[i].x && snake[0].y==poisonItem[i].y) {
            getpoison = true;
            //points-=10;
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

    if(gatestate==0) tpsnake(0);
    else if(gatestate==1) tpsnake(1);

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

    for(int i=0; i<2; i++){
      if(growthItem[i].y == snake[0].y && growthItem[i].x == snake[0].x) putGrowthItem(i);
      if(poisonItem[i].y == snake[0].y && poisonItem[i].x == snake[0].x) putPoisonItem(i);
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
    }

    //poison아이템
    if(getpoison){//먹었을 때
      snakemap[snake.back().y][snake.back().x] = 0;
      snake.pop_back();
    }

    updateScore();

}

snakeClass::snakeClass() {
    maxWidth = MAX_WIDTH;
    maxHeight = MAX_HEIGHT;

    points = 0;

    srand(time(NULL));
}


snakeClass::~snakeClass() {
}

void snakeClass::updateScore()
{
  snakesize = sizeofsnake();
  if (getgrowth) {
    points += 10;
    sumgrowth++;
  }
  if (getpoison) {
    sumpoisons++;
  }
}

std::vector<int> snakeClass::getScore()
{
  std::vector<int> scores = {points, snakesize, sumgrowth, sumpoisons, sumgates};
  return scores;
}

bool snakeClass::isMissionComplete()
{
  if (snakesize < stage.mission_maxLength) return false;
  if (sumgrowth < stage.mission_maxGrowth) return false;
  if (sumpoisons < stage.mission_maxPoison) return false;
  if (sumgates < stage.mission_maxGates) return false;

  return true;
}

void snakeClass::newStage(int stageNum)
{
  sumgrowth = 0;
  sumpoisons = 0;
  sumgates = 0;

  snake.clear();
  wallvt.clear();

  stage.newStage(stageNum);

  // 맵 데이터 깊은 복사
  for (int y=0; y<MAX_HEIGHT; y++) {
    for (int x=0; x<MAX_WIDTH; x++) {
      snakemap[y][x] = stage.mapArr[y][x];
    }
  }
  //snake 생성
  for(int i=0; i<3; i++) {
      snake.push_back(snakePart(maxHeight/2, maxWidth/2+i));
  }

  // 벽 목록 생성
  for(int y=0; y<MAX_HEIGHT; y++){
    for(int x=0; x<MAX_WIDTH; x++){
      if(snakemap[y][x]==1) wallvt.push_back(snakePart(y,x));
    }
  }

  //make snake
  for(int i=0; i<snake.size(); i++) {
    if(i == 0) snakemap[snake[i].y][snake[i].x] = 3;
    else snakemap[snake[i].y][snake[i].x] = 4;
  }


  snakesize = snake.size();
  points = 0;
  sumpoisons = 0;
  sumgrowth = 0;
  sumgates = 0;
  ticks = 200000;
  getgrowth = false;
  getpoison = false;
  gatestate = 2;
  direction ='l'; //default is left

  //putitem
  putGrowthItem(0);
  putGrowthItem(1);
  putPoisonItem(0);
  putPoisonItem(1);

  makegate();
}