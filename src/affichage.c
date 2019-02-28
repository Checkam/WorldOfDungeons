#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <couleurs.h>
#include <liste.h>
#include <block.h>
#include <commun.h>


int dansFenetre(SDL_Rect r){
    if(r.x < width_window && r.x >= 0 && r.y >= 0 && r.y < height_window ){
        return 1;
    }else{
        return 0;
    }
}

char * CouleurBlock(int id,block_type2_t blocks[]){
    int i;
    for(i=0;i<NB_BLOCK;i++)
        if(blocks[i].materiau==id)
            return blocks[i].texture;
    return NOIR;
}

SDL_Surface * TextureBlock(int id,block_type_t blocks[]){
    int i;
    for(i=0;i<NB_BLOCK;i++)
        if(blocks[i].materiau==id)
            return blocks[i].texture;
    return NULL;
}

void aff_map_sdl(SDL_Surface *screen,block_type_t blocks[],int min){
    int i,j=0;
    int *map; /*Tableau de recupèration de la liste*/
    SDL_Rect r = {0,0,0,0};
    if(min)
    for (j=0,en_tete(); !hors_liste(); suivant()){
        valeur_elt(&map);
        for (i = MAX_SCREEN; i > 0; i--){
            r.x=(j*(width_window/SIZE));
            r.y=(height_window-(i*(height_window/MAX_SCREEN)));
            if(dansFenetre(r))
                SDL_BlitSurface(TextureBlock(*(map + i + min),blocks),NULL,screen,&r);
           
            //printf("x:%d y:%d\n",r.x,r.y);
            //printf("%d\n",i); 
        }
        j++;       
    }
}


void aff_map(int min, int max,block_type2_t blocks[]){
    system("clear");
    int i;
    int *map;   //Tableau de recupèration de la liste
    for (i = MAX_SCREEN - 1; i >= 0; i--){
        for (en_tete(); !hors_liste(); suivant()){
            valeur_elt(&map);
            printf("%s %s",CouleurBlock(*(map + i),blocks), NOIR);
        }
        printf("\n");
    }
}