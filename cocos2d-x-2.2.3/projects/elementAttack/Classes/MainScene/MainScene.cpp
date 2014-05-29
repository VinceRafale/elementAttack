//
//  MainScene.cpp
//  elementAttack
//
//  Created by 成焱 on 5/28/14.
//
//

#include "MainScene.h"
#include "../EAResource.h"
#include "GameLevelScene.h"
USING_NS_CC;
CCScene *MainScene::scene()
{
    CCScene *scene = CCScene::create();
    MainScene *mainScene = MainScene::create();
    scene->addChild(mainScene);
    return scene;
}

bool MainScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //init code bollow
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *sprite = CCSprite::create(mainSceneBg);
    sprite->setPosition(ccp(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(sprite,0);
    
    
    CCSprite *iceSprite = CCSprite::create(test_ice_icon);
    CCSprite *iceSelectSprite = CCSprite::create(test_ice_icon);
    iceSelectSprite->setScale(0.95f);
    CCMenuItemSprite *menuIceSprite = CCMenuItemSprite::create(iceSprite, iceSelectSprite, this, menu_selector(MainScene::menuFirstCallBack));
    menuIceSprite->setPosition(ccp(origin.x+67, visibleSize.height/2));
    
    CCSprite *fireSprite = CCSprite::create(test_fire_icon);
    CCSprite *fireSelectSprite = CCSprite::create(test_fire_icon);
    fireSelectSprite->setScale(0.95f);
    CCMenuItemSprite *menuFireSprite = CCMenuItemSprite::create(fireSprite, fireSelectSprite, this, menu_selector(MainScene::menuSecondCallBack));
    menuFireSprite->setPosition(ccp(visibleSize.width-67, visibleSize.height/2));
    

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(MainScene::menuCloseCallBack));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    
    CCMenu *menu = CCMenu::create(menuIceSprite,menuFireSprite,pCloseItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu,1);
    return true;
    
    
}

void MainScene::menuCloseCallBack(CCObject *pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void MainScene::menuFirstCallBack(CCObject *pSender)
{
    //do your custom code here ,DongGe
}

void MainScene::menuSecondCallBack(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameLevelScene::scene());
}
