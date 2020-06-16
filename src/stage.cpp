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
    for (int i=0; i<MAX_HEIGHT; i++) {
      for (int j=0; j<MAX_WIDTH; j++) {
        stageFile >> tmp;
        mapArr[i][j] = (int)(tmp-'0');
      }
    }
  }

  stageFile.close();
}
