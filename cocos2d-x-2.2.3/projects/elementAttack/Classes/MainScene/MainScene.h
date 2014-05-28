//
//  MainScene.h
//  elementAttack
//
//  Created by 成焱 on 5/28/14.
//
//

#ifndef elementAttack_MainScene_h
#define elementAttack_MainScene_h
#include "cocos2d.h"
using namespace cocos2d;

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene * scene();
    
    void menuFirstCallBack(CCObject *pSender);
    void menuSecondCallBack(CCObject *pSender);
    void menuCloseCallBack(CCObject *pSender);
    CREATE_FUNC(MainScene);
};

#endif
