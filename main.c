#include "player.h"
#include <stdio.h>
#include<stdlib.h>
#include "grid.h"
#include <stdbool.h>
#include "src/sdl2.h"
#include <string.h>

/**
 * @brief
 * pas de préconditions
 * main fait le lien entre les fonctions et les structures du jeu et lance l'interface sur le terminal
 * 
 * @param aucun
 * @return int
 */

int main(int argc, char *argv[]){

	Event (*handle_event)();

	bool run = true;
	// Grid type structure
	struct Grid grille;
	// player type structure
	struct Player position;
	// on appele level function to allocate the array of the structure and fill it
	init_level("level1.txt", &grille);
	//on display le level
	display(&grille);
	if((argc) > 1 && strcmp (argv[1], "--sdl2") == 0)
	{
		handle_event = &event_sdl2;
		handle_display = &display_sdl2;
		sdl_init();
		SDL_PumpEvents();	
		printf("utilisez les flèches clavier pour vous déplacer\n");
	}

	else
	{
		handle_event = &event;
		handle_display = &display;
	}

	
(*handle_display)(grille);

	while(run)
	{	
		printf("h: LEFT		j:BOTTOM	k:TOP	l:RIGHT\nq:EXIT\n");
		Event entry = (*handle_event)();
		switch(entry)
		{
			case Quit :
			{
				run = false;
				break;
			}
			case Left:
			case Right:
			case Up:
			case Down:
				move_player(grille, entry); 
			case None:
			default :
				break;
		}
		system("clear");
		(*handle_display)(grille);
		if (check_win(grille) == 1){
			run = false;
			printf("t'as gagné!\n");
		}
	}

	for (int i = 0; i < grille->row_number; i++) // libérer chaque ligne de game_grid
		free(grille->game_grid[i]);

	free(grille->game_grid); // libérer le game_grid
	free(grille->goals); // liberer le goals
	free(grille);	

	void sdl_quit();
	return 0;
}
