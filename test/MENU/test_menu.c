/**
 * \file test_erreur.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Tibane.
 * \date 07/03/2019
 * \version 0.1
*/

#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
<<<<<<< HEAD
    t_menu * menu = NULL;

    /* Test création menu 1 */
    assert(creer_menu(PRINCIPAL, 100, 100, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu 1 */
    printf("Test affichage Menu 1:\n");
    assert(afficher_menu_test(menu) == OK);
    printf("\t-- OK\n");

    // /* Test destruction menu 1 */
    // printf("Test destruction Menu 1:\n");
    // assert();
    // printf("\t-- OK\n");

    /* Test création menu 2 */
    printf("Test Creation Menu 2:\n");
    assert(creer_menu(SOLO, 100, 100, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu 2 */
    printf("Test affichage Menu 2:\n");
    assert(afficher_menu_test(menu) == OK);
    printf("\t-- OK\n");

    /* Test création menu 3 */
    printf("Test Creation Menu 3:\n");
    assert(creer_menu(NOUVEAU_MENU, 100, 100, &menu) == OK);
    printf("\t-- OK\n");
    printf("\tTest Ajout Bouton 1 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 50, 60, 50, 10, "Bouton 1", NULL) == OK);
    printf("\t\t-- OK\n");
    printf("\tTest Ajout Bouton 2 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 50, 60, 50, 10, "Bouton 2", NULL) == OK);
    printf("\t\t-- OK\n");
    

    /* Test affichage menu 3 */
    printf("Test affichage Menu 3:\n");
    assert(afficher_menu_test(menu) == OK);

    t_menu * menu;

    /* Test création menu 1 */
