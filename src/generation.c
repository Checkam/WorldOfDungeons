/**
*   \file procedural.c
*   \brief Fonction de génération procédural grace a Perlin Noise
*   \author {Maxence.D Jasmin.G Tibane.G, Mathieu.V}
*   \version 0.1 
*   \date 28 fevrier 2019 
*
*   \fn void init_map(int *map)
*   \brief Initialise un tableau d'entier a 0 
*
*   \fn void gen_col(int **tab, int i)
*   \brief A définir
*
*   \enum biome_t 
*   \brief Enumération des types de biomes (Toudra,Taiga ect) 
**/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <commun.h>
#include <perlin.h>
#include <generation.h>
#include <couleurs.h>
#include <block.h>


biome_t biome;

void changeBiome(int x,int y){
    if(x % W_BIOME == SEED%W_BIOME){
        biome= (int)((double)x*perlin2d(x - 1, y, FREQ, DEPTH)*(double)HAUTEUR_SURFACE+1)%NB_BIOME;  
    }
}

void init_map(int *map){
    int i;
    for (i = 0; i < MAX; i++){
        *(map + i) = AIR;
    }
}



// Initialise un tableau de n valeur a 0
void initTab(int tab[],int n){
    for(int i=0;i<n;i++)
        tab[i]=0;
}

//FONCTION QUI CALCUL LES PROCHAINES HAUTEUR (A REFAIRE)
int PreviewHeight(int x,int P_Height[],int nb){
    int taille_max = 0;
    for(int i=0;i<nb;i++){
        taille_max = perlin2d(x+i, MAX, FREQ, DEPTH) * MAX;
        P_Height[i]=taille_max;
    }
    return 1;
}



//LOI QUI PERMET DE CREE DES ARBRES
//Marche plus car fonction de prediction plus bonne 
void createTree(int x,int map[MAX],int y){
    static int tree=0;
    static int new_tree = 0;

    int preview = 10;
    int P_Height[preview];
    initTab(P_Height,preview);

    PreviewHeight(x,P_Height,preview);
    //P_Height[1]==P_Height[2] && P_Height[2]==P_Height[3] && P_Height[3]==P_Height[4] && P_Height[4]==P_Height[5] && P_Height[5]==P_Height[6] && P_Height[6]==P_Height[7] && 
    if(P_Height[1]==P_Height[2] && P_Height[2]==P_Height[3] && P_Height[3]==P_Height[4] && !tree && !new_tree && y>H_MIN_GEN_ARBRE && y<H_MAX_GEN_ARBRE && (biome==FORET || biome==TAIGA) && y>HAUTEUR_EAU){
        tree=7;
        new_tree=(int)((double)x*perlin2d(x, MAX, FREQ, DEPTH)*(double)W_BIOME+1) % DIST_MAX_TREE; 
    }else if(tree){
        char line[50];
        FILE * arbre = NULL;

        if(biome==TAIGA) arbre=fopen("structure/arbre/arbre_taiga","r");
        else if(biome==FORET) arbre=fopen("structure/arbre/arbre_foret","r");

        if(arbre!=NULL){
            for(int j=0;j<tree;j++){
                for(int l=0;l<50;l++)
                    line[l]=0;
                fgets(line,50,arbre);
            }
            for(int j=0;j<strlen(line) && (j+y < MAX -1);j++)
                map[y+j]=line[j]-'0';
            
            fclose(arbre);
        }
        tree--;
    }else if(new_tree>0){
        new_tree--;
    }
}




int gen_col(int **tab, int i)/* Pourquoi i ici est x dans le reste ?*/
{
    int rnd, j;
    int taille_max = perlin2d(i, MAX, FREQ, DEPTH) * MAX;
    *tab = malloc(sizeof(int) * MAX);
    init_map(*tab);
    changeBiome(i,taille_max);

    /* génération arbre */
    createTree(i,*tab,taille_max);

    /* génération eau */
    for (j = 0; taille_max + j < HAUTEUR_EAU; j++)
    {
        *(*tab + taille_max + j) = EAU;
    }
    

    /* génération herbe + sable*/
    for (j = 1; j <= HAUTEUR_SURFACE; j++){
        if (*(*tab + taille_max) == EAU){
            *(*tab + taille_max - j) = SABLE;
        }
        else if(biome==PRAIRIES || biome==FORET || biome==DESERTS){
            if(j==1) *(*tab + taille_max - j) = HERBE;
            else *(*tab + taille_max - j) = TERRE;
        }else if(biome==TOUNDRA || biome==TAIGA){
            *(*tab + taille_max - j) = NEIGE;
        }
    }

    /* Génération profondeur */
    for (j = 0; j < taille_max - HAUTEUR_SURFACE; j++){
        rnd = perlin2d(i, j, FREQ, DEPTH) * MAX;

        if (taille_max - j > PROFONDEUR_GROTTE && j >= BEDROCK && rnd >= (MAX / 2 - SIZE_GROTTE) && rnd <= (MAX / 2 + SIZE_GROTTE)){ /* grotte */
            *(*tab + j) = AIR;
        }
        else{
            *(*tab + j) = ROCHE;
        }
    }
    return taille_max;
}