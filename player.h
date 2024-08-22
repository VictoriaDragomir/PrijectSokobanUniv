#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "grid.h"

enum Direction{
    Top = 'k' ,
    Left = 'h',
    Right = 'l',
    Bottom = 'j',
};

/**
 * @brief a structure to have the position x y of player
 * 
 */
struct Player{
    int x;
    int y;
};


#endif