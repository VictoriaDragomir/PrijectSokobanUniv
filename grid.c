#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include "sdl2.h"
#include <stdbool.h>


void init_level(const char* file_path, struct Grid *grille){ // ajout du paramètre struct Grid *grille
	// ouverture du fichier en mode lecture
	FILE* file = fopen(file_path, "r");
	if(!file){
		fprintf(stderr, "Error %s not found", file_path);
		exit(-1);
	}
    char line[100] = {0};
    int number_column = 0; // nombre de colonne
        int number_goals = 0; //nombre objectif

    // on lit la première ligne du fichier
    fgets(line, 100, file);
    sscanf(line, "%d %d %d", &number_column, &number_row, &number_goals);
    
    // on inscrit le nb de colonnes et lignes dans Grid
    grille->column_number = number_column;
    grille->row_number = number_row;
    grille->nb_point_cibles = number_goals;
	grille->point_cibles_recouverts =0;


    int current_row = 0; //ligne actuelle
    int current_goal = 0;//objectif

    // on alloue de la memoire pour le tableau game_grid pour un tableau en 2D
    grille->game_grid = malloc(sizeof(enum CaseType*)*(grille->row_number));
    
    
    for (int i = 0; i < grille->row_number; i++){
        grille->game_grid[i] = malloc(sizeof(enum CaseType*)*(grille->column_number));
    }

    // On lit le fichier ligne par ligne jusqu'à la fin du fichier
    while(fgets(line, 100, file) != NULL){
        char* buffer = line;
        int current_column = 0;
        while(*buffer && *buffer != '\n'){
                // on rempli le tableau game_grid avec les symboles de fichier level1.txt
                grille->game_grid[current_row][current_column] = *buffer;
            
                // si on tombe sur le symbole du joueur, alors sa position (x,y) = [current_row][current_column] 
                if(*buffer == '@'){
                    grille->positionPlayer.x = current_row;     // x = ligne
                    grille->positionPlayer.y = current_column;      // y = colonne
                }
                // on incrémente pour accéder au prochain élément
                current_column += 1;
                buffer += 1;
        }       
        current_row += 1;
    }
    // fermeture du fichier
    fclose(file);
    
}

void freeArray(struct Grid *grille){
    // on parcourt le tableau et on le free 
    for(int i = 0; i < grille->row_number; i++){
        free(grille->game_grid[i]);
    }
    free(grille->game_grid);
}


void display(struct Grid *grille){
    // on parcourt le tableau et on affiche la grille 
    for(int i = 0; i < grille->row_number; i++){
        for(int j = 0; j < grille->column_number; j++){
            printf("%c", grille->game_grid[i][j]);
        }
        printf("\n");
    }
}

int pointEgal(Grid * grille){
	return grille->nb_point_cibles==grille->point_cibles_recouverts;
}
