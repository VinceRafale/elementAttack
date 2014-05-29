//
//  GameLevelScene.h
//  elementAttack
//
//  Created by 成焱 on 5/29/14.
//
//

#ifndef elementAttack_GameLevelScene_h
#define elementAttack_GameLevelScene_h
#include "cocos2d.h"
#include "GameLogic.h"
using namespace cocos2d;

/*!
 * @brief 每个scene都是包裹着 cclayer的一个scene，实际的操作是在操作cclayer
 * @function bool init(); 初始化方法，界面的精灵设置在该方法中进行处理
 * @function static cocos2d::ccScene *scene();提供给外界的一个接口，用来创建scene
 * @function CREATE_FUNC(GameLevelScene); 默认的分配内存空间的方法
 */
class GameLevelScene:public cocos2d::CCLayer
{
    enum{START_X = 174, START_Y = 174};
    CCSize spriteSize;
	int getRealX(int gs)
	{
		return START_X + gs * spriteSize.width;
	}
	int getRealY(int gs)
	{
		return START_Y + gs * spriteSize.height;
	}
private:
    GameLogic gameLogic;
    cocos2d::CCSprite *spriteBlocks[WIDTH_CNT][HEIGHT_CNT];
    cocos2d::CCLabelBMFont *scoreLabel;
    cocos2d::CCLabelBMFont *leftTime;
    cocos2d::CCLabelBMFont *gameOver;
    short int second;
private:
    cocos2d::CCSprite *getSprite(int x, int y);//获取layer层上的精灵
    
public:
    CREATE_FUNC(GameLevelScene);
    virtual bool init();
    static cocos2d::CCScene * scene();
    
    void registerWithTouchDispatcher();//注册触摸事件
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
    void initBlocks();
    void addMenus();
    void menuBeganCallBack(CCObject *pSender);
    void menuCloseCallBack(CCObject *pSender);
    void scheduleCallBack(float dt);
    void spriteMoveFromTo(int fromX, int fromY, int toY);
    void makeUpBlocks();
    void spriteDropDown();
    
    friend GameLogic;
};
#endif
