/**
*
*   \file procedural.c
*   \brief Fonction du Programme de Test de la génération procédural grace a Perlin Noise
*   \author {Maxence.D Jasmin.G Tibane.G, Mathieu.V}
*   \version 0.1 
*   \date 30 Janvier 2019 
*
*   \fn void init_map(int *map)
*   \brief Initialise un tableau d'entier a 0 
*
*   \fn int noise2(int x, int y)
*   \brief Renvoie une valeur d'un tableau dont l'indice est calculer a partir d'un SEED
*
*   \fn float lin_inter(float x, float y, float s)
*   \brief A définir
* 
*   \fn float smooth_inter(float x, float y, float s)
*   \brief A définir
* 
*   \fn float noise2d(float x, float y)
*   \brief A définir
*  
*   \fn float perlin2d(float x, float y, float freq, int depth)
*   \brief A définir
*
*   \fn void gen_col(int **tab, int i)
*   \brief A définir
*
*   \fn int arbre(int i)
*   \brief A définir
*
*   \fn void draw_arbre(int **tab, int dep, int arr, int tronc)
*   \brief A définir
*
*   \enum biome_t 
*   \brief Enumération des types de biomes (Toudra,Taiga ect) 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <commun.h>
#include <procedural.h>
#include <couleurs.h>
#include <block.h>

biome_t biome;

static int hash[] = {208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24, 140, 71, 48, 140, 254, 245, 255, 247, 247, 40,
                     185, 248, 251, 245, 28, 124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202, 224, 245, 128, 167, 204,
                     9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 100, 108, 167, 44, 43, 77, 180, 204, 8, 81,
                     70, 223, 11, 38, 24, 254, 210, 210, 177, 32, 81, 195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13,
                     203, 9, 47, 104, 125, 117, 114, 124, 165, 203, 181, 235, 193, 206, 70, 180, 174, 0, 167, 181, 41,
                     164, 30, 116, 127, 198, 245, 146, 87, 224, 149, 206, 57, 4, 192, 210, 65, 210, 129, 240, 178, 105,
                     228, 108, 245, 148, 140, 40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62, 3, 237, 55, 89,
                     232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17, 212, 203, 149, 152, 140, 187, 234, 177, 73, 174,
                     193, 100, 192, 143, 97, 53, 145, 135, 19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 39, 145,
                     101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42, 30, 154, 120, 67, 87, 167,
                     135, 176, 183, 191, 253, 115, 184, 21, 233, 58, 129, 233, 142, 39, 128, 211, 118, 137, 139, 255,
                     114, 20, 218, 113, 154, 27, 127, 246, 250, 1, 8, 198, 250, 209, 92, 222, 173, 21, 88, 102, 219};


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

int noise2(int x, int y){
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int + 1, y_int);
    int u = noise2(x_int, y_int + 1);
    int v = noise2(x_int + 1, y_int + 1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for (i = 0; i < depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin / div;
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
    int rnd, j, dep, arr, tronc;
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
