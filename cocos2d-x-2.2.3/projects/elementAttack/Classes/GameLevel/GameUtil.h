//
//  GameUtil.h
//  elementAttack
//
//  Created by 成焱 on 5/29/14.
//
//

#ifndef elementAttack_GameUtil_h
#define elementAttack_GameUtil_h

enum{
    HEIGHT_CNT = 9,
    WIDTH_CNT = 5,
};
enum {
 BLOCK_WIND = 0,
 BLOCK_FIRE = 1,
 BLOCK_FOG = 2,
 BLOCK_ICE = 3,

};



const int blockCount = 4;
const short int dir[4][2] = {{1,0},{0,1},{0,-1},(-1.0)};

typedef struct {
    short int blocktype;
    short int moveToY;
}block;
#endif
