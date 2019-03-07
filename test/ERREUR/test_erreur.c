/**
 * \file test_erreur.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Tibane.
 * \date 07/03/2019
 * \version 0.1
*/

#include <erreur.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int num_test = 1;

    /* Test erreur de fichier */
    printf("Test Erreur %d :\tFILE_ERROR\n",num_test++);
    assert(aff_erreur(FILE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur d'ouverture de fichier */
    printf("Test Erreur %d :\tOPEN_FILE_ERROR\n",num_test++);
    assert(aff_erreur(OPEN_FILE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur de fermeture de fichier */
    printf("Test Erreur %d :\tCLOSE_FILE_ERROR\n",num_test++);
    assert(aff_erreur(CLOSE_FILE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur de valeur */
    printf("Test Erreur %d :\tVALUE_ERROR\n",num_test++);
    assert(aff_erreur(VALUE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur de suppression de fichier */
    printf("Test Erreur %d :\tREMOVE_FILE_ERROR\n",num_test++);
    assert(aff_erreur(REMOVE_FILE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test valeur de ptr incorrect */
    printf("Test Erreur %d :\tPTR_VALUE_ERROR\n",num_test++);
    assert(aff_erreur(PTR_VALUE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur de type */
    printf("Test Erreur %d :\tTYPE_ERROR\n",num_test++);
    assert(aff_erreur(TYPE_ERROR) == OK);
    printf("\t-- OK\n");

    /* Test erreur de clé */
    printf("Test Erreur %d :\tKEY_NOT_FOUND\n",num_test++);
    assert(aff_erreur(KEY_NOT_FOUND) == OK);
    printf("\t-- OK\n");

    /* Test erreur non existante */
    printf("Test Erreur %d :\tERROR\n",num_test++);
    assert(aff_erreur(100) == ERROR_NOT_EXIST);
    printf("\t-- OK\n");

    return EXIT_SUCCESS;
}