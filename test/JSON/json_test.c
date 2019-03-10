#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <erreur.h>
#include <json.h>
#include <assert.h>

int main(int argc, char **argv, char ** env) {
    printf("-------- Programme de Test du Module JSON --------\n");

    getpwd(argv[0],getenv("PWD"));

    char * objet;
    char nom[10];
    float val = 75.4;

    /* Création fichier JSON */
    printf("Création de fichier JSON :\n");
    FILE * file = new_json("test/JSON/", "test");
    assert(file);
    printf("\t-- OK\n");

    /* Création d'objets JSON */
    /* Objet 1 */
    printf("Création et Ouverture objet JSON 1 :\n");
    assert(open_json_obj(file) == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 1 :\n");
    assert(write_json(file,"nom","jean",'s') == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 2 :\n");
    assert(write_json(file,"poids",(void *)&val,'f') == OK);
    printf("\t-- OK\n");

    printf("Fermerture objet JSON 1 :\n");
    assert(close_json_obj(file) == OK);
    printf("\t-- OK\n");

    /* Objet 2 */
    printf("Création et Ouverture objet JSON 2 :\n");
    assert(open_json_obj(file) == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 1 :\n");
    assert(write_json(file,"nom","jean",'s') == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 2 :\n");
    assert(write_json(file,"poids",(void *)&val,'f') == OK);
    printf("\t-- OK\n");

    printf("Fermerture objet JSON 2 :\n");
    assert(close_json_obj(file) == OK);
    printf("\t-- OK\n");

    /* Fermeture d'un fichier JSON */
    printf("Fermeture d'un fichier JSON :\n");
    fclose(file);
    printf("\t-- OK\n");

    /* Lecture d'un objet */
    file = open_json("test/JSON/", "test");
    printf("Récupération objet JSON 1 :\n");
    assert(extract_json_obj(file,&objet) == OK);
    printf("\t-- OK\n");

    printf("Récupération du contenu :\n");
    assert(read_json_obj(objet,"nom",nom,'s') == OK);
    printf("\t-- OK\n");
    assert(read_json_obj(objet,"poids",&val,'f') == OK);
    printf("\t-- OK\n");

    printf("Contenu : nom = %s, poids = %.2f\n", nom, val);

    fclose(file);
    free(objet);
    free(WOD_PWD);
    return OK;
}
