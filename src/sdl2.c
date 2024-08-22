#include "sdl2.h"
#include "grid.h"

SDLContext context;

void sdl_init()
{
  int const width = 1280;
  int const height = 720;
  context = (SDLContext){NULL, NULL, .width = 0, .height = 0};
  if (SDL_Init(SDL_INIT_VIDEO)){
    return;
  }

  SDL_Window *window =
      SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  if (!window)
  {
    return;
  }
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  context = (SDLContext){
      .window = window, .renderer = renderer, .width = width, .height = height};
}
void sdl_quit()
{
  SDL_DestroyWindow(context.window);
  SDL_DestroyRenderer(context.renderer);
  context.window = NULL;
  context.renderer = NULL;
  SDL_Quit();
}

void display_sdl2(struct Grid* grille)
{
  float x = 0;
  float y = 0;
  float w = context.width / grille->column_number;
  float h = context.height / grille->row_number;
  SDL_Rect rec;
  SDL_SetRenderDrawColor(context.renderer, 214, 193, 133, 255); 
  SDL_RenderClear(context.renderer);                            
  int index_row, index_column;
  for (index_row = 0; index_row < grille->row_number; index_row++)
  {
    for (index_column = 0; index_column < grille->column_number; index_column++)
    {
      char positionActuelle = grille->game_grille[index_row][index_column];
      switch (positionActuelle)
      {
      case WALL:
      {
        SDL_SetRenderDrawColor(context.renderer, 128, 128, 128, 255);; 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec); 
        break;
      }
      case PLAYER:
      {
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 255, 255); 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec);
        break;
      }
      case GOAL:
      {
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255); 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec);
        break;
      }
      case BOX:
      {
        SDL_SetRenderDrawColor(context.renderer, 139, 69, 19, 255); 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec);
        break;
      }
      case BOX_OK:
      {
        SDL_SetRenderDrawColor(context.renderer, 0, 128, 0, 255); 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec);
        break;
      }
      case PLAYER_GOAL:
      {
        SDL_SetRenderDrawColor(context.renderer, 163, 0, 0, 255); 
        rec.x = x, rec.y = y, rec.w = w, rec.h = h;
        SDL_RenderFillRect(context.renderer, &rec);
        break;
      }
      default:
        break;
      }
      x = x + w; 
    }
    y = y + h; 
    x = 0;     
  }
  SDL_RenderPresent(context.renderer); 
}

Event event_sdl2(){
  SDL_Event ev; //variable ev
  Event e=none;//variable e 

  SDL_WaitEvent(&ev);//attends clique au clavier

  if(ev.type==SDL_QUIT)
  
    e=quit;
  else if(ev.type==SDL_KEYDOWN){
    switch(ev.key.keysym.sym)
    {
      case SDLK_UP:
        e=up;
          break;
      case SDLK_LEFT:
        e=left;
          break;
      case SDLK_DOWN:
        e=down;
          break;
      case SDLK_RIGHT:
        e=right;
         break;
      default:
        e=none;
        break;
    }
  }
  return e;
}


Event event()
{
  Event action;
  char event = fgetc(stdin);// Attend le prochain événement disponible.
  switch (event)
  {
  case 'a':
  {
    action = QUIT;
    return action;
    break;
  }
  case 'z':
  {
    action = UP;
    return action;
    break;
  }
  case 's':
  {
    action = DOWN;
    return action;
    break;
  }
  case 'd':
  {
    action = RIGHT;
    return action;
    break;
  }
  case 'q':
  {
    action = LEFT;
    return action;
    break;
  }
  default:
  {
    action = NON;
    return action;
    break;
  }
  }
}

void console_init()
{
  return ;
}
