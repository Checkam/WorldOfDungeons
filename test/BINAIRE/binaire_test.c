#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <erreur.h>
#include <binaire.h>
#include <assert.h>

int main(int argc, char **argv, char ** env) {
    printf("-------- Programme de Test du Module BINAIRE --------\n");

    pwd_init(argv[0],getenv("PWD"));

    /* Ouverture Fichier Binaire */
    FILE * fic = Open_BIN("test/BINAIRE/","data.dat","wb+");
    
    /* On écrit 2 tableaux */
    int t[4] = {1,2,3,4};
    int t2[4] = {5,6,7,8};
    
    Write_BIN(t,sizeof(int),4,fic);
    Write_BIN(t2,sizeof(int),4,fic);
    
    /* On récupère les 2 tableaux */
    FStart_BIN(fic);
    int res[4];

    /* Récup Tableau 1 */
    Read_BIN(res,sizeof(int),4,fic);
    for (int i = 0; i < 4; i++)
        printf("%d ", res[i]);
    printf("\n");
    
    /* Récup Tableau 2 */
    Read_BIN(res,sizeof(int),4,fic);
    for (int i = 0; i < 4; i++)
        printf("%d ", res[i]);
    printf("\n");
    
    /* Fermeture du Fichier Binaire */
    Close_BIN(fic);
    
    pwd_quit();
    return OK;
}
