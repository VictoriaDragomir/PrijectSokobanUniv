#ifndef GRID_HEADER
#define GRID_HEADER
#include "player.h"
#include "sdl2.h"
#include <stdbool.h>

enum CaseType{
    WALL = '#',
    BOX = '$',
    PLAYER = '@',
    GOAL = '.',
    NONE = ' ',
};
typedef enum CaseType CaseType;

enum Direction{
    TOP    = 'k',
    LEFT   = 'h',
    RIGHT  = 'l',
    BOTTOM = 'j'
};
typedef enum Event{
    Quit = SDL_QUIT,
    Left = SDLK_LEFT,
    Right = SDLK_RIGHT,
    Up = SDLK_UP,
    Down = SDLK_DOWN,
    None = SDLK_CLEAR
} Event;

struct Player{
    int x;    /// row->ligne
    int y;    /// column->colonne
};

/**
 * @struct Grid grid.h
 * @brief Cette structure contient les informations 
 * concernant la grille du jeu et son contenu
 */
struct Grid{
    enum CaseType** game_grid; ///< Tableau contenant les entités présents dans le jeu
    int column_number; ///< Nombre de colonne de game_grid
    int row_number; ///< Nomber de ligne de game_grid
    struct Player positionPlayer; ///< Structure qui contient la position du joueur
    int nb_point_cibles;///< Nombre de points cibles a recouvrir
	int point_cibles_recouverts;///< Nombre de points ciles recouverts

};
typedef struct Grid Grille;


void init_level(const char* file_path ,struct Grid *grille);
void freeArray(struct Grid *grille);
void display(struct Grid *grille);
void move_player(struct Grid *grille, enum Direction dir);
int pointEgal(Grid * grid);
void display_sdl2(Grid * myGrid);
Event event();
#endif

