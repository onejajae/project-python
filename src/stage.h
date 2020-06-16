#ifndef SNAKE_STAGE
#define SNAKE_STAGE

#include <string>
#include <vector>

#define MAX_HEIGHT 30
#define MAX_WIDTH 30

class Stage
{
  private:
    int stageNum;
    int mission_maxLength;
    int mission_maxGrowth;
    int mission_maxPoison;
    int mission_maxGates;

  protected:
    void loadStageFile(const std::string& stageFileName);

  public:
    Stage(int stageNum=1);
    int mapArr[30][30];

    int getStageNum();
    std::vector<int> getMission();

    void newStage(int newStageNum);
    

};

#endif