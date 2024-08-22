#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

void move_player(struct Grid *grille, enum Direction dir){
    int next_x = grille->positionPlayer.x;
    int next_y = grille->positionPlayer.y;
    
    int next_next_x = grille->positionPlayer.x;
    int next_next_y = grille->positionPlayer.y;

    if(dir == TOP){
        next_x -= 1;
        next_next_x -= 2;
    }
    else if(dir == LEFT){
        next_y -= 1;
        next_next_y -= 2;
    }
    else if(dir == RIGHT){
        next_y += 1;
        next_next_y += 2;
    }
    else if(dir == BOTTOM){
        next_x +=1;
        next_next_x += 2;
    }

   //  s'il n'y a rien devant la position actuelle du joueur et que le joueur n'est pas sur GOAL
    if(grille->game_grid[next_x][next_y] == NONE && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER){

        grille->game_grid[next_x][next_y] = PLAYER;
        grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
        grille->positionPlayer.x = next_x;
        grille->positionPlayer.y = next_y;
    }
    // si la position devant est un GOAL et que le joueur n'est pas déjà sur un GOAL
    else if(grille->game_grid[next_x][next_y] == GOAL && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER){
        grille->game_grid[next_x][next_y] = PLAYER_GOAL;
        grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
        grille->positionPlayer.x = next_x;
        grille->positionPlayer.y = next_y;
    }
    // s'il y a une case devant la position actuelle du joueur mais que le joueur est sur un GOAL
    else if(grille->game_grid[next_x][next_y] == BOX && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER_GOAL && grille->game_grid[next_next_x][next_next_y] == NONE){
        grille->game_grid[next_x][next_y] = PLAYER;
        grille->game_grid[next_next_x][next_next_y] = BOX;
        grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = GOAL;
        grille->positionPlayer.x = next_x;
        grille->positionPlayer.y = next_y;
    }
    //  s'il n'y a rien devant la position actuelle du joueur mais que le joueur est sur un GOAL
    else if(grille->game_grid[next_x][next_y] == NONE && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER_GOAL){
        grille->game_grid[next_x][next_y] = PLAYER;
        grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = GOAL;
        grille->positionPlayer.x = next_x;
        grille->positionPlayer.y = next_y;
    }
    // s'il y a une case devant la position actuelle du joueur et que le joueur n'est pas sur un GOAL
    else if(grille->game_grid[next_x][next_y] == BOX && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER){
        // si devant la boîte il y a rien alors on pousse la boîte
        if(grille->game_grid[next_next_x][next_next_y] == NONE){
            grille->game_grid[next_x][next_y] = PLAYER;
            grille->game_grid[next_next_x][next_next_y] = BOX;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer.y = next_y;
        }
        // si devant la case il y a un but alors on incrémente le compteur cible
        else if(grille->game_grid[next_next_x][next_next_y] == GOAL){
            grille->game_grid[next_x][next_y] = PLAYER;
            grille->game_grid[next_next_x][next_next_y] = BOX_OK;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer .y = next_y;
            
        }
    }
    // si nous voulons déplacer une boîte qui est sur un GOAL
    else if(grille->game_grid[next_x][next_y] == BOX_OK){
        if(grille->game_grid[next_next_x][next_next_y] == NONE && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER){
            grille->game_grid[next_x][next_y] = PLAYER_GOAL;
            grille->game_grid[next_next_x][next_next_y] = BOX;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer.y = next_y;
            
        }
         // si devant la boite il n'y a rien mais le joueur est sur un GOAL
        else if(grille->game_grid[next_next_x][next_next_y] == NONE && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER_GOAL){
            grille->game_grid[next_x][next_y] = PLAYER_GOAL;
            grille->game_grid[next_next_x][next_next_y] = BOX;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = GOAL;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer.y = next_y;
            
        }
        // si devant la boîte il y a encore un GOAL et que le joueur n'est pas sur un GOAL
        else if(grille->game_grid[next_next_x][next_next_y] == GOAL && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER){
            grille->game_grid[next_x][next_y] = PLAYER_GOAL;
            grille->game_grid[next_next_x][next_next_y] = BOX_OK;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = NONE;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer.y = next_y;
        }
        // si devant la boîte il y a encore un GOAL mais que le joueur est sur un GOAL
        else if(grille->game_grid[next_next_x][next_next_y] == GOAL && grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] == PLAYER_GOAL){
            grille->game_grid[next_x][next_y] = PLAYER_GOAL;
            grille->game_grid[next_next_x][next_next_y] = BOX_OK;
            grille->game_grid[grille->positionPlayer.x][grille->positionPlayer.y] = GOAL;
            grille->positionPlayer.x = next_x;
            grille->positionPlayer.y = next_y;
        }
    }
}