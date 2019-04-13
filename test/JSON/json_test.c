#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <erreur.h>
#include <json.h>
#include <assert.h>
#include <inttypes.h>
#include <liste.h>

int main(int argc, char **argv, char ** env) {
    printf("-------- Programme de Test du Module JSON --------\n");

    pwd_init(argv[0],getenv("PWD"));

    char * objet;
    char nom[10];
    float val = 75.4;

    /* Création fichier JSON */
    printf("Création de fichier JSON :\n");
    assert(JSON_Open("test/JSON/", "test", "w+") == OK);
    printf("\t-- OK\n");

    /* Création d'objets JSON */
    /* Objet 1 */
    printf("Création et Ouverture objet JSON 1 :\n");
    assert(JSON_Open_Object() == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 1 :\n");
    assert(JSON_Write("nom","jean","s") == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 2 :\n");
    assert(JSON_Write("poids",(void *)&val,"f") == OK);
    printf("\t-- OK\n");

    printf("Fermerture objet JSON 1 :\n");
    assert(JSON_Close_Object() == OK);
    printf("\t-- OK\n");

    /* Objet 2 */
    printf("Création et Ouverture objet JSON 2 :\n");
    assert(JSON_Open_Object() == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 1 :\n");
    assert(JSON_Write("nom","jean","s") == OK);
    printf("\t-- OK\n");

    printf("Insertion valeur 2 :\n");
    assert(JSON_Write("poids",(void *)&val,"f") == OK);
    printf("\t-- OK\n");

    printf("Fermerture objet JSON 2 :\n");
    assert(JSON_Close_Object() == OK);
    printf("\t-- OK\n");

    /* Lecture d'un objet */
    printf("\n\nRécupération des objets JSON :\n");
    for (en_tete(&json_objects);!hors_liste(&json_objects);suivant(&json_objects))
    {
        printf("Récupération Objet :\n");
        assert(valeur_elt(&json_objects,(void **)&objet) == OK);
        printf("\t-- OK\n");
        printf("Récupération du contenu :\n");
        assert(JSON_Read_Object(objet,"nom",nom,"s") == OK);
        printf("\t-- OK\n");
        assert(JSON_Read_Object(objet,"poids",&val,"f") == OK);
        printf("\t-- OK\n");

        printf("Contenu : nom = %s, poids = %.2f\n", nom, val);
    }

    /* Fermeture d'un fichier JSON */
    printf("Fermeture d'un fichier JSON :\n");
    JSON_Close();
    printf("\t-- OK\n");


    /****************************************************/
    printf("-------------- Test --------------\n");
    char * unint64 = "18446744073709551615";
    printf("U_INT64_T :\t%"PRIu64"\n",(uint64_t)strtoull(unint64,NULL,0));
    char * sint64 = "9223372036854775807";
    printf("INT64_T :\t%"PRId64"\n",(int64_t)atoll(sint64));
    /****************************************************/

    pwd_quit();
    return OK;
}
