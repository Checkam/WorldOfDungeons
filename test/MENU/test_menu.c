/**
 * \file test_erreur.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Tibane.
 * \date 07/03/2019
 * \version 0.1
*/

#include <menu.h>
#include <erreur.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    t_menu * menu;

    /* Test création menu 1 */
    printf("Test Creation Menu 1:\n");
    assert(creer_menu(PRINCIPAL, 100, 100, menu) == OK);
    printf("\t-- OK\n");

    return EXIT_SUCCESS;
}