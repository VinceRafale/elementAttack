//
//  GameLevelScene.cpp
//  elementAttack
//
//  Created by 成焱 on 5/29/14.
//
//

#include "GameLevelScene.h"
#include "EAResource.h"
using namespace cocos2d;

CCScene *GameLevelScene::scene()
{
    CCScene *scene = cocos2d::CCScene::create();
    GameLevelScene *gameLevelLayer = GameLevelScene::create();
    scene->addChild(gameLevelLayer);
    return scene;
}

void GameLevelScene::addMenus()
{

}

bool GameLevelScene:: init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //init code bollow
    CCSprite *temp = CCSprite::create(ice);
    this->spriteSize = temp->getContentSize();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *sprite = CCSprite::create(mainSceneBg);
    sprite->setPosition(ccp(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(sprite,0);
    gameLogic.init();
    this->initBlocks()  ;
    this->setTouchEnabled( true );
    std::cout<<&gameLogic;
    return true;
}

void GameLevelScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameLevelScene::initBlocks()
{
    for (int i=0; i<WIDTH_CNT; i++)
	{
		for (int j=0; j<HEIGHT_CNT; j++)
		{
			spriteBlocks[i][j] = getSprite(i, j);
			spriteBlocks[i][j]->setPosition( ccp(getRealX(i),getRealY(j)));
            CCLOG("%d",getRealY(j));
			this->addChild(spriteBlocks[i][j]);
		}
	}
}

CCSprite *GameLevelScene::getSprite(int i, int j){
    switch (gameLogic.blocks[i][j].blocktype) {
        case BLOCK_FIRE:
            return CCSprite::create(fire);
            break;
        case BLOCK_FOG:
            return CCSprite::create(fog);
            break;
        case BLOCK_ICE:
            return CCSprite::create(ice);
            break;
        case BLOCK_WIND:
            return CCSprite::create(wind);
            break;
        default:
            break;
    }
    return NULL;
}


bool GameLevelScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent){
	CCPoint point = touch->getLocation();
	for (int i=0; i<WIDTH_CNT; i++)
	{
		for (int j=0; j<HEIGHT_CNT; j++)
		{
			CCRect rect = spriteBlocks[i][j]->boundingBox();
			if ( rect.containsPoint(point) )
			{
				bool ok = gameLogic.touchPoint(i, j);
				if ( !ok ) return false;
				
            
                
				char s[15];
				sprintf( s, "score : %d", gameLogic.totalScore);
//				scoreLabel->setCString( s );
                
				spriteDropDown();
				makeUpBlocks();
				return false;
			}
		}
	}
	return false;
}

void GameLevelScene::spriteMoveFromTo(int fromX, int fromY, int toY)
{
	if ( fromY == toY ) return;
    
	CCMoveTo *mv = CCMoveTo::create( 0.3f, ccp(getRealX(fromX), getRealY(toY)) );
	spriteBlocks[fromX][fromY]->runAction(mv);
	spriteBlocks[fromX][toY] = spriteBlocks[fromX][fromY];
}

void GameLevelScene::spriteDropDown()
{
	bool dropNum[WIDTH_CNT];
	memset ( dropNum, false, sizeof(dropNum) );
	for (int i=0; i<WIDTH_CNT; i++)
	{
		for (int j=0; j<HEIGHT_CNT; j++)
		{
			if ( gameLogic.visit[i][j] )
			{
				dropNum[i] = true;
				spriteBlocks[i][j]->removeFromParentAndCleanup( true );
			}
		}
	}
    
	for (int i=0; i<WIDTH_CNT; i++)
	{
		if ( ! dropNum[i] ) continue;
		for (int j=0; j<HEIGHT_CNT; j++)
		{
			if ( ! gameLogic.visit[i][j] )
				spriteMoveFromTo( i, j, gameLogic.blocks[i][j].moveToY);
		}
	}
}

void GameLevelScene::makeUpBlocks()
{
	for (int i=0; i<WIDTH_CNT; i++)
	{
		for (int j=HEIGHT_CNT-gameLogic.lack[i]; j<HEIGHT_CNT; j++)
		{
			spriteBlocks[i][j] = getSprite(i, j);
			spriteBlocks[i][j]->setPosition( ccp(getRealX(i), getRealY(j)) );
//			spriteBlocks[i][j]->setScale( 0.5 );
			
			this->addChild(spriteBlocks[i][j]);
            
		}
	}
}






