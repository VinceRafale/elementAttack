//
//  GameLogic.cpp
//  elementAttack
//
//  Created by 成焱 on 5/29/14.
//
//

#include "GameLogic.h"
#include "memory.h"
#include <stdlib.h>
#include "ctime"
#include "cocos2d.h"
//构造函数，可以带一个默认参数
GameLogic::GameLogic(void):totalScore(0)
{
    //做一个伪随机数的种子
    srand((unsigned)time(0));
    
    for (int i = 0; i<WIDTH_CNT; i++) {
        lack[i] = 0;
        for (int j = 0; j<HEIGHT_CNT; j++) {
            blocks[i][j].moveToY = j;//默认是不移动
            blocks[i][j].blocktype = rand()%blockCount;//生成随机的元素
        }
    }
    memset(visit, false, sizeof(visit));//将visit的内存空间置为false
}

void GameLogic::init()
{
    //做一个伪随机数的种子
    srand((unsigned)time(0));
    
    for (int i = 0; i<WIDTH_CNT; i++) {
        lack[i] = 0;
        for (int j = 0; j<HEIGHT_CNT; j++) {
            blocks[i][j].moveToY = j;//默认是不移动
            blocks[i][j].blocktype = rand()%blockCount;//生成随机的元素
        }
    }
    memset(visit, false, sizeof(visit));//将visit的内存空间置为false
    totalScore = 0;//分初始化为0
}
//析构函数
GameLogic::~GameLogic()
{

}

void GameLogic::makeUpBlocks()
{
    srand((unsigned)time(0));
    
    for (int i = 0; i<WIDTH_CNT; i++) {
        for (int j  = HEIGHT_CNT-lack[i]; j<HEIGHT_CNT; j++) {
            blocks[i][j].blocktype = rand()%blockCount;//补齐
        }
    }
}

bool GameLogic::touchPoint(int i, int j)
{
    stateRecover();//重置所有状态
    //根据点击的位置去判断点击的位置能够消除的个数和消除结构数组
    int ret = deepFirstSearch(i, j);
//    if (ret<3) {
//        return false;
//    }
    
    //进行分值计算
    blockCancel();
    makeUpBlocks();
    return true;
}

int GameLogic::deepFirstSearch(int i, int j)
{
    int ret = 1;
    visit[i][j] = true;
    
    for (int p = 0; p<4;p++) {
        int x = i + dir[p][0];//取的某一方向的横坐标
        int y = j + dir[p][1];//取的某一项的纵坐标
        
        if (x>WIDTH_CNT||x<0) {
            continue;
        }
        if (y>HEIGHT_CNT||y<0) {
            continue;
        }
    #warning 该算法有问题，不会判断行与列,只要相邻的相同就认为能消除是不合适的
        if (!visit[i][j]&&blocks[i][j].blocktype==blocks[x][y].blocktype) {
            ret += deepFirstSearch(x, y);
            using namespace cocos2d;
            CCLOG("%d",ret);
        }
    }
    return ret;
    
}

void GameLogic::blockCancel()
{
    for (int i = 0; i<WIDTH_CNT; i++) {
        for (int j = 0; j<HEIGHT_CNT; j++) {
            if (visit[i][j]) {
                lack[i]++;
            }else{
                blocks[i][j].moveToY = j-lack[i];//利用这个结构去操作精灵位置的移动
                blocks[i][j-lack[i]].blocktype = blocks[i][j].blocktype;//这条是为了将数据与遍历数据进行统一，不会用它进行UI变化
            }
        }
    }
}

void GameLogic::stateRecover()
{
    memset( visit, false, sizeof(visit) );
    
	for (int i=0; i<WIDTH_CNT; i++)
	{
		lack[i] = 0;
		for (int j=0; j<HEIGHT_CNT; j++)
		{
			blocks[i][j].moveToY = j;
		}
	}
}











