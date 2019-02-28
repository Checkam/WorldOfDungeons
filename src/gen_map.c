/**
*
*   \file gen_map.c
*   \brief Programme de Test de la génération procédural grace a Perlin Noise
*   \author {Maxence.D, Jasmin.G, Tibane.G, Mathieu.V}
*   \version 0.1 
*   \date 30 Janvier 2019 
*
*   \fn CouleurBlockc har * CouleurBlock(int id)
*   \brief donne la couleur de l'id d'un block 
*
*   \fn aff_map void aff_map()
*   \brief Afffiche une map stocker dans un liste, chaque element de la liste est un tableau de taille N
*
*   \fn save_tab void save_tab(FILE *fichier, int *tab)
*   \brief Sauvegarde une ligne (Tableau de int) de la map dans un fichier
*   
*   \struct block_s 
*   \brief Struture d'un block
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <SDL2/SDL.h>
#include <liste.h>
#include <seed.h>
#include <gen_map.h>
#include <commun.h>
#include <generation.h>
#include <couleurs.h>
#include <block.h>
#include <affichage.h>


static int Program=1;

void save_tab(FILE *fichier, int *tab){
    int i;
    for (i = 0; i < MAX; i++){
        switch (*(tab + i)){
        case 0: /* Air */
            fprintf(fichier, " ");
            break;
        case 1: /* Herbe */
            fprintf(fichier, "V");
            break;
        case 2: /* Eau */
            fprintf(fichier, "~");
            break;
        case 3: /* Sable */
            fprintf(fichier, "S");
            break;
        case 4: /* Feuille */
            fprintf(fichier, "A");
            break;
        case 5: /* Tronc */
            fprintf(fichier, "T");
            break;
        default: /* Roche */
            fprintf(fichier, "#");
            break;
        }
    }
    fprintf(fichier, "\n");
}

int taille_mid_aff(){
    int *tab;
    int i=0;
    int taille = MAX-1;
    if (taille_liste() > SIZE){ /* INCOMPREHENSIBLE */
        for(en_tete();!hors_liste();suivant(), i++){
            valeur_elt(&tab);
            if(i==(SIZE/2)){
                while(tab[taille] != HERBE && tab[taille] != NEIGE && tab[taille] != EAU){
                    taille--;
                }
                return taille;
            }
        }
    } 
    return -1;
}


void intHandler(int dummy) {
    Program = 0;
    printf("\33[30;48;5;0m\033[38;5;253m \n");
}

int main(int argc, char const *argv[]){

    // ----------------------------------------------------------------- SDL 

    SDL_Init(SDL_INIT_EVERYTHING);    SDL_Window* screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window, SDL_WINDOW_SHOWN);
    SDL_Event event;
    SDL_Rect fondRect = {0,0,0,0};
    //SDL_Rect Rect = {200,height_window-100,0,0};

    SDL_Surface *fond = SDL_LoadBMP("./IMG/texture/fond.bmp");; 
    SDL_Surface *herbe_world = SDL_LoadBMP("./IMG/texture/herbe.bmp");
    SDL_Surface *terre_world = SDL_LoadBMP("./IMG/texture/terre.bmp");
    SDL_Surface *eau_world   = SDL_LoadBMP("./IMG/texture/eau.bmp");
    SDL_Surface *neige_world = SDL_LoadBMP("./IMG/texture/neige.bmp");
    SDL_Surface *tronc_world = SDL_LoadBMP("./IMG/texture/tronc.bmp");
    SDL_Surface *feuille_world = SDL_LoadBMP("./IMG/texture/feuille.bmp");
    SDL_Surface *roche_world = SDL_LoadBMP("./IMG/texture/pierre.bmp");


    block_type_t blocks[NB_BLOCK] = 
    {
        {AIR,"air",NULL},
        {HERBE,"herbe",herbe_world},
        {TERRE,"terre",terre_world},
        {EAU,"eau",eau_world},
        {SABLE,"sable",terre_world},
        {FEUILLE,"feuille",feuille_world},
        {BOIS,"bois",tronc_world},
        {ROCHE,"roche",roche_world},
        {NEIGE,"neige", neige_world},
        {GLACE,"glace", feuille_world}
    };

    block_type2_t blocks2[NB_BLOCK] = 
    {
        {AIR,"air",NOIR},
        {HERBE,"herbe",VERT},
        {TERRE,"terre",MARRON},
        {EAU,"eau",BLEU},
        {SABLE,"sable",JAUNE},
        {FEUILLE,"feuille",VERT},
        {BOIS,"bois",MARRON},
        {ROCHE,"roche",GRIS},
        {NEIGE,"neige", BLANC},
        {GLACE,"glace", CYAN}
    };

    // ------------------------------------------------------------------------
    if (argc != 3){
        printf("Option:\n");
        printf("\t./gen_map SEED DEPART\n");
        return EXIT_FAILURE;
    }

    signal(SIGINT, intHandler);

    SEED = seed_part(argv[1]);
    int DEPART = seed_part(argv[2]);
    init_liste();
    int *tab;
    char chaine[50];
    sprintf(chaine, "map/map%d.txt", SEED);
    FILE *fichier = fopen(chaine, "w");
    int taille_max=0;
    int i = DEPART;
    int repeat = 0;
    int taille = 0;
    while(1 && Program && !repeat){
        taille_max=gen_col(&tab, i); /*Génère la nouvelle colonne*/

        if (taille_liste() > SIZE){ /* INCOMPREHENSIBLE */
            en_tete();
            oter_elt();
        } 
        en_queue();                 /* PAREIL */
        ajout_droit(tab);

        //save_tab(fichier, tab);
        aff_map(taille_max-5,taille_max+50,blocks2);
        //if(taille_max < HAUTEUR_EAU) taille_max = HAUTEUR_EAU;

        taille = taille_mid_aff();
        if(taille == -1) taille = taille_max;

        SDL_BlitSurface(fond,NULL,SDL_GetWindowSurface(screen),&fondRect);
        aff_map_sdl(SDL_GetWindowSurface(screen),blocks,taille-4);
        SDL_UpdateWindowSurface(screen);

        while(SDL_PollEvent(&event))
            switch(event.type){
                case SDL_QUIT:
                    repeat = 1;
                    break;
            }
        SDL_Delay(50);


        //system("sleep 0.05");
        i++;
    }

    detruire_liste();

    fclose(fichier);

    return 0;
}
