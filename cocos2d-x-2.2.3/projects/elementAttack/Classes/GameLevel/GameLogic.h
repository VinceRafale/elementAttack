//
//  GameLogic.h
//  elementAttack
//
//  Created by 成焱 on 5/29/14.
//
//

#ifndef elementAttack_GameLogic_h
#define elementAttack_GameLogic_h

#include "GameUtil.h"

class GameLogic
{
    public:
    int totalScore;
    block blocks[WIDTH_CNT][HEIGHT_CNT];//消除的块数据，里面包含 消除的颜色、消除的位置
    bool visit[WIDTH_CNT][HEIGHT_CNT];//将要消除的块，如果为false，则不消除；如果为true，则消除
    int lack[WIDTH_CNT];//这个数组用来实时记录消除的距离值，eg，当遍历第一列时，会记录第一列每行的元素需要消除的距离
private:
    int deepFirstSearch(int i,int j);//深度优先遍历算法
    void blockCancel();//消除逻辑，会将消除的块进行记录并存储在block结构中。
public:
    GameLogic(void);
    ~GameLogic(void);
   
    void init();
    bool touchPoint(int i, int j);
    void stateRecover();//状态覆盖
    void makeUpBlocks();//生成新的块
};
#endif
