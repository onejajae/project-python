#include <fstream>
#include "stage.h"

Stage::Stage(int stageNum) : stageNum(stageNum)
{
  newStage(stageNum);
}

void Stage::newStage(int newStageNum)
{
  stageNum = newStageNum;
  std::string stageFileName = "stages/stage" + std::to_string(stageNum) + ".txt";
  loadStageFile(stageFileName);
}

void Stage::loadStageFile(const std::string& stageFileName)
{
  char tmp;
  std::ifstream stageFile;
  stageFile.open(stageFileName);

  if (stageFile.is_open()) {
    // 스테이지 맵 배열 생성
    for (int i=0; i<MAX_HEIGHT; i++) {
      for (int j=0; j<MAX_WIDTH; j++) {
        stageFile >> tmp;
        mapArr[i][j] = (int)(tmp-'0');
      }
    }

    // 스테이지 미션
    stageFile >> mission_maxLength;
    stageFile >> mission_maxGrowth;
    stageFile >> mission_maxPoison;
    stageFile >> mission_maxGates;
    stageFile >> stage_tick;
  }

  stageFile.close();
}
