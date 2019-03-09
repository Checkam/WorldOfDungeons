/**
 *   \file test_outils_sdl.c
 *   \brief test du module outils
 *   \author Jasmin Galbrun
 *   \version 1
 *   \date 09/03/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <erreur.h>
#include <outils_SDL.h>



int main(int argc, char const *argv[]) {

  /* Inialisation */
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    printf("%s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if(TTF_Init() == -1){
    printf("%s\n", TTF_GetError());
    return EXIT_FAILURE;
  }

  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == -1){
    printf("%s\n", IMG_GetError());
    return EXIT_FAILURE;
  }
  
  int width = 1000;
  int height = 600;
  SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width, height, SDL_WINDOW_SHOWN);
  if(screen == NULL){
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL){
    return EXIT_FAILURE;
  }

  /* Test création texture image */
  printf("Test Création Texture Image\n");
  SDL_Texture * texture = NULL;
  assert(Create_IMG_Texture(renderer, "../../IMG/texture/herbe.bmp", &texture) == OK);
  printf("\t -- OK\n");
  

  /* Test affichage image */
  printf("Test Affichage Image\n");
  SDL_Rect r = {0, 0, width, height};
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, &r);
  SDL_RenderPresent(renderer);
  SDL_Delay(2000);
  printf("\t -- OK\n");

  /* destruction texture */
  SDL_DestroyTexture(texture);
  texture = NULL;

  /* Test création texture texte */
  printf("Test Création Texture Texte\n");
  SDL_Color couleur = {255,0,0};
  assert(Create_Text_Texture(renderer, "Test texte", "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 40, couleur, BLENDED, &texture) == OK);
  printf("\t -- OK\n");
  

  /* Test affichage Texte */
  printf("Test Affichage Texte\n");
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, &r);
  SDL_RenderPresent(renderer);
  SDL_Delay(2000);
  printf("\t -- OK\n");

  /* destruction texture */
  SDL_DestroyTexture(texture);
  texture = NULL;
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
