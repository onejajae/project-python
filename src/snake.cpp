#include <random>
#include "snake.h"


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


//게이트에 있는 뱀를 다른 게이트에서 나가야하는 방향에 있는 좌표로 이동시켜준다.
void snakeClass::tpsnake(int n){ //인자로 gatestate를 받는다 만약 1이 인자로 들어왔을 경우 1번게이트에 뱀이 있는 경우로 판단
  switch (n) {
    case 0: //0번 게이트에 뱀이 들어있는경우
      for(int i=0; i<snake.size();i++){
        if(gate[0].y==snake[i].y && gate[0].x==snake[i].x){
          switch (direction) { //뱀의 원래 방향에 따라 어느 방향을 우선으로 나갈지 정함
            case 'u': // 만약 뱀이 게이트 진입시 방향이 u이였다면 위, 오른쪽, 왼쪽 ,아래를 순서대로 탐색해 먼저 가능한 곳으로 나가고 뱀의 방향을 다시 설정해준다.
              if(snakemap[gate[1].y -1][gate[1].x]!=1 && snakemap[gate[1].y -1][gate[1].x]!=9){ //만약 나가야하는 게이트의 위 방향이 벽이 아니라면 게이트 안에 있는 snake의 좌표를 바꿔준다.
                snake[i].y = gate[1].y -1;
                snake[i].x = gate[1].x;
                direction = 'u';
              }else if(snakemap[gate[1].y][gate[1].x +1]!=1 && snakemap[gate[1].y][gate[1].x +1]!=9){ //만약 나가야하는 게이트의 오른쪽 방향이 벽이 아니라면 게이트 안에 있는 snake의 좌표를 바꿔준다.
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x +1;
                direction = 'r';
              }else if(snakemap[gate[0].y][gate[1].x -1]!=1 && snakemap[gate[1].y][gate[0].x -1]!=9){ //만약 나가야하는 게이트의 왼쪽 방향이 벽이 아니라면 게이트 안에 있는 snake의 좌표를 바꿔준다.
                snake[i].y = gate[1].y;
                snake[i].x = gate[1].x -1;
                direction = 'l';
              }else{ //만약 나가야하는 게이트의 아래 방향이 벽이 아니라면 게이트 안에 있는 snake의 좌표를 바꿔준다.
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
    if(tempa==tempb) continue; //만약 생선된 두 변 수가 같다면 루프를 다시 수행

    gate[0] = wallvt[tempa]; //벽 벡터에 들어있는 원소 하나를 게이트로 선언
    gate[1] = wallvt[tempb]; //벽 벡터에 들어있는 원소 하나를 게이트로 선언

    wallvt[tempa] = snakePart(-1,-1);//게이트로 지정된 벽 벡터의 원소를 뱀이 도달할 수 없는 곳인 -1,-1로 변경(후에 충돌 함수에서 벽에 부딪히지 않게 판정되게 위해서)
    wallvt[tempb] = snakePart(-1,-1);
    snakemap[gate[0].y][gate[0].x] = 7; // snakemap에서 gate부분의 배열을 7로 비꿔준다.
    snakemap[gate[1].y][gate[1].x] = 7;
    break;
  }
}

bool snakeClass::collision() {

    for(int i =0 ; i < snake.size(); i++){
      if(gate[0].y == snake[i].y && gate[0].x == snake[i].x) gatestate = 0; //snake벡터 내부를 돌면서 0번 게이트와 snake가 만났다면 게이트의 상태 변수를 0으로 바꿔준다.
      if(gate[1].y == snake[i].y && gate[1].x == snake[i].x) gatestate = 1; //snake벡터 내부를 돌면서 1번 게이트와 snake가 만났다면 게이트의 상태 변수를 1으로 바꿔준다.
    }

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
    for(int i=0; i<2; i++) {
        if(snake[0].x==growthItem[i].x && snake[0].y==growthItem[i].y) {
            getgrowth = true;
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
            break;
        }
        else {
            getpoison = false;
        }
    }

    //gate 사용할 때
    for (int i=0; i<2; i++) {
      if (snake[0].x == gate[i].x && snake[0].y == gate[i].y) {
        ingate = true;
        break;
      }
      else {
        ingate = false;
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

  if (ingate) {
    sumgates++;
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
  sumpoisons = 0;
  sumgrowth = 0;
  sumgates = 0;
  getgrowth = false;
  getpoison = false;
  gatestate = 2;
  direction ='l'; //default is left

  points += (stageNum-1)*2000;

  //putitem
  putGrowthItem(0);
  putGrowthItem(1);
  putPoisonItem(0);
  putPoisonItem(1);

  makegate();
}