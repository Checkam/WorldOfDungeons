/**
 * \file menu.c
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 3
 * \date 15/03/2019
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chemin.h>
#include <menu.h>
#include <outils_SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <touches.h>

#define POLICE_MENU "data/police/8-BIT_WONDER.ttf"
#define FOND_MENU "IMG/texture/menu/fond_menu.png"
#define BOUTON_MENU "IMG/texture/menu/bouton_menu.png"
#define WIDTH_TITRE 80 //100 maximum

SDL_Texture *menu_texture[2];

/**
 * \struct t_type_titre
 * \brief Contient le titre correspondant au type de menu
*/
typedef struct s_type_titre {
  t_type_menu type_menu;
  char *titre;
} t_type_titre;

#define NB_TITRE 2
t_type_titre tab_menu_titre[NB_TITRE] = {{MENU_PRINCIPAL, "World Of Dungeons"}, {MENU_SOLO, "Solo"}};

/**
 * \fn t_erreur menu_init(SDL_Renderer * renderer)
 * \brief Initialise Menu
 * \param renderer Renderer de la fenetre
 * \return t_erreur Code erreur
*/
t_erreur menu_init(SDL_Renderer *renderer) {
  char *fond, *bouton;
  creation_chemin(FOND_MENU, &fond);
  creation_chemin(BOUTON_MENU, &bouton);
  SDL_Texture *fond_tex, *bouton_tex;

  /* Création Texture */
  Create_IMG_Texture(renderer, fond, &fond_tex);
  Create_IMG_Texture(renderer, bouton, &bouton_tex);

  menu_texture[0] = fond_tex;
  menu_texture[1] = bouton_tex;

  free(fond);
  free(bouton);

  return OK;
}

/**
 * \fn t_erreur menu_quit(void)
 * \brief Quitte Menu
 * \return Code erreur
*/
t_erreur menu_quit(void) {
  SDL_DestroyTexture(menu_texture[0]);
  SDL_DestroyTexture(menu_texture[1]);

  return OK;
}

/**
 * \fn t_erreur menu_ajout_bouton(t_menu * menu, SDL_Rect rect, char * titre, t_type_menu type)
 * \brief Ajoute un bouton au menu
 * \param rect Informations de position et de taille du bouton
 * \param titre Titre du bouton
 * \param type Type du menu suivant
 * \return Retourne un code erreur
*/
t_erreur menu_ajout_bouton(t_menu *menu, SDL_Rect rect, char *titre, t_type_menu type) {
  /* Vérification */
  if (menu == NULL) {
    erreur_save(PTR_NULL, "menu_ajout_bouton() : Pointeur sur le menu NULL");
    return PTR_NULL;
  }
  if (rect.x < 0 || rect.y < 0 || rect.w < 0 || rect.h < 0) {
    erreur_save(VALUE_ERROR, "menu_ajout_bouton() : Position ou taille des boutons incorrects");
    return VALUE_ERROR;
  }

  /* Allocation de la mémoire pour un bouton au menu */
  if (menu->tab_bouton == NULL) {
    menu->tab_bouton = malloc(sizeof(t_bouton_menu));
  } else {
    menu->tab_bouton = realloc(menu->tab_bouton, (menu->nb_bouton + 1) * sizeof(t_bouton_menu));
  }

  /* Création d'un bouton */
  t_bouton_menu *btn = malloc(sizeof(t_bouton_menu));

  if (titre != NULL) {
    btn->titre = malloc(sizeof(char) * (strlen(titre) + 1));
    strcpy(btn->titre, titre);
  }
  btn->x = rect.x;
  btn->y = rect.y;
  btn->width = rect.w;
  btn->height = rect.h;
  btn->state = RELEASED;
  btn->focus = 0;
  btn->suivant = type;

  /* Ajout du bouton au menu */
  menu->tab_bouton[menu->nb_bouton] = btn;
  menu->nb_bouton++;

  return OK;
}

/**
 * \fn t_erreur menu_creer(t_type_menu type, int width, int height, t_menu ** menu)
 * \brief Créer un Menu
 * \param type Type de menu que l'on veut avoir (Solo,...)
 * \param width Largeur de la fenêtre d'affichage
 * \param height Hauteur de la fenêtre d'affichage
 * \param menu Double pointeur sur le menu que l'on veut créer
 * \return Code erreur
*/
t_erreur menu_creer(t_type_menu type, int width, int height, t_menu **menu) {
  /* Vérification */
  if (width < 0 || height < 0) {
    erreur_save(VALUE_ERROR, "menu_creer() : Taille du menu incorrect");
    return VALUE_ERROR;
  }
  if (menu == NULL) {
    erreur_save(PTR_NULL, "menu_creer() : Pointeur sur le menu NULL");
    return PTR_NULL;
  }

  /* Création d'un menu */
  *menu = malloc(sizeof(t_menu));
  (*menu)->nb_bouton = 0;
  (*menu)->width = width;
  (*menu)->height = height;
  (*menu)->type = type;

  /* Initialisation taille bouton */
  int w, h; //Taille d'une colonne et d'une ligne
  int hauteur_btn, largeur_btn;
  w = width / 100;
  h = height / 100;
  largeur_btn = 50 * w;
  hauteur_btn = 12 * h;
  SDL_Rect btn = {(width - largeur_btn) / 2, 15 * w, largeur_btn, hauteur_btn};

  if (type == MENU_PRINCIPAL) {
    (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));

    menu_ajout_bouton(*menu, btn, "Solo", MENU_SOLO);
    btn.y += btn.h + 20;
    menu_ajout_bouton(*menu, btn, "Multijoueur", MENU_PRINCIPAL);
    btn.y += btn.h + 20;
    menu_ajout_bouton(*menu, btn, "Option", MENU_PRINCIPAL);
    btn.y += btn.h + 20;
    menu_ajout_bouton(*menu, btn, "Quitter", MENU_QUITTER);
  } else if (type == MENU_SOLO) {
    (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));

    menu_ajout_bouton(*menu, btn, "Nouvelle partie", MENU_NOUVELLE_PARTIE);
    btn.y += btn.h + 20;
    menu_ajout_bouton(*menu, btn, "charger une partie", MENU_CHARGER_PARTIE);
    btn.y += btn.h + 20;
    menu_ajout_bouton(*menu, btn, "Retour", MENU_PRINCIPAL);
  } else if (type == NOUVEAU_MENU) {
    (*menu)->tab_bouton = NULL;
  } else {
    (*menu)->tab_bouton = NULL;
    menu_detruire(menu);
  }

  return OK;
}

/**
 * \fn t_erreur menu_afficher_titre_SDL(SDL_Renderer * renderer, t_menu * menu)
 * \brief Affiche le titre du Menu
 * \param renderer Renderer de la fenetre
 * \param menu Pointeur sur le menu
 * \return Code erreur
*/
t_erreur menu_afficher_titre_SDL(SDL_Renderer *renderer, t_menu *menu) {
  /* On récupère le titre correspondant au type de menu */
  char *titre = NULL;
  int taille_titre_max = 0;
  int i;
  for (i = 0; i < NB_TITRE; i++) {
    if (menu->type == tab_menu_titre[i].type_menu) {
      titre = malloc(sizeof(char) * (strlen(tab_menu_titre[i].titre) + 1));
      strcpy(titre, tab_menu_titre[i].titre);
    }
    if (strlen(tab_menu_titre[i].titre) > taille_titre_max) {
      taille_titre_max = strlen(tab_menu_titre[i].titre);
    }
  }

  if (titre == NULL)
    return OK;

  /* On affiche le titre */
  int row = menu->height / 4.5;
  int col = menu->width / 100;
  int taille_titre = strlen(titre);
  int taille_police = col * WIDTH_TITRE / taille_titre_max;
  int x = (col * WIDTH_TITRE - taille_police * taille_titre) / 2 + ((menu->width - WIDTH_TITRE * col) / 2);
  int y = (row - taille_police) / 2;

  SDL_Rect r = {x, y, taille_police * taille_titre, taille_police};
  SDL_Color couleur = {255, 255, 255};

  char *chemin_police = NULL;
  creation_chemin(POLICE_MENU, &chemin_police);
  SDL_Texture *texture_texte;

  Create_Text_Texture(renderer, titre, chemin_police, taille_police, couleur, BLENDED, &texture_texte);
  SDL_RenderCopy(renderer, texture_texte, NULL, &r);

  /* On libère la mémoire */
  SDL_DestroyTexture(texture_texte);
  free(chemin_police);
  free(titre);

  return OK;
}

/**
 * \fn t_erreur menu_afficher_SDL(t_menu * menu, SDL_Renderer * renderer)
 * \brief Affiche le menu
 * \param menu Pointeur sur le menu que l'on veut afficher
 * \param renderer Renderer sur le lequel on veut afficher le menu
 * \return Code erreur
*/
t_erreur menu_afficher_SDL(t_menu *menu, SDL_Renderer *renderer) {
  /* Vérification */
  if (menu == NULL) {
    return UNDEFINED_MENU;
  }
  if (renderer == NULL) {
    return PTR_NULL;
  }
  if (menu->tab_bouton == NULL) {
    return PTR_NULL;
  }

  /* Initialisation */
  SDL_Color couleur_texte = {255, 255, 255};
  char *police;
  creation_chemin(POLICE_MENU, &police);
  SDL_Texture *texte_tex;

  /* Définition taille de la police */
  int taille_max_titre = 0;
  int taille_min_width = menu->tab_bouton[0]->width;
  int i;
  for (i = 0; i < menu->nb_bouton; i++) {
    if (strlen(menu->tab_bouton[i]->titre) > taille_max_titre)
      taille_max_titre = strlen(menu->tab_bouton[i]->titre);
    if (menu->tab_bouton[i]->width > taille_min_width) {
      taille_min_width = menu->tab_bouton[i]->width;
    }
  }
  int taille_police = taille_min_width / taille_max_titre;

  /* Affichage */
  SDL_Rect fenetre = {0, 0, menu->width, menu->height};
  SDL_RenderCopy(renderer, menu_texture[0], NULL, &fenetre);

  /* Titre Menu */
  menu_afficher_titre_SDL(renderer, menu);

  for (i = 0; i < menu->nb_bouton; i++) {
    SDL_Rect r_img = {menu->tab_bouton[i]->x, menu->tab_bouton[i]->y, menu->tab_bouton[i]->width, menu->tab_bouton[i]->height};

    /* Centrer le texte */
    int x_txt = (menu->tab_bouton[i]->width - taille_police * strlen(menu->tab_bouton[i]->titre)) / 2 + menu->tab_bouton[i]->x;
    int y_txt = (menu->tab_bouton[i]->height - taille_police) / 2 + menu->tab_bouton[i]->y;
    SDL_Rect r_txt = {x_txt, y_txt, taille_police * strlen(menu->tab_bouton[i]->titre), taille_police};

    /* Etat bouton */
    if (menu->tab_bouton[i]->focus == 1) {
      couleur_texte.a = 100;
    } else {
      couleur_texte.a = 255;
    }

    /* Création Texture texte */
    Create_Text_Texture(renderer, menu->tab_bouton[i]->titre, police, taille_police, couleur_texte, BLENDED, &texte_tex);

    SDL_RenderCopy(renderer, menu_texture[1], NULL, &r_img);
    SDL_RenderCopy(renderer, texte_tex, NULL, &r_txt);
    SDL_DestroyTexture(texte_tex);
  }
  free(police);
  return OK;
}

/**
 * \fn t_erreur menu_afficher_Term(t_menu * menu)
 * \param menu
*/
t_erreur menu_afficher_Term(t_menu *menu) {
  /* Vérification */
  return OK;
}

/**
 * \fn t_erreur menu_detruire_bouton(t_bouton_menu ** btn)
 * \brief Detruire un bouton
 * \param btn Bouton que l'on veut détruire
 * \return Code erreur
*/
t_erreur menu_detruire_bouton(t_bouton_menu **btn) {
  if (*btn != NULL) {
    if ((*btn)->titre != NULL) {
      free((*btn)->titre);
      (*btn)->titre = NULL;
    }
    free(*btn);
    *btn = NULL;
  }
  return OK;
}

/**
 * \fn t_erreur menu_detruire(t_menu ** menu)
 * \brief Detruire un Menu
 * \param menu Menu que l'on veut détruire
 * \return Code erreur
*/
t_erreur menu_detruire(t_menu **menu) {
  if (*menu != NULL) {
    if ((*menu)->tab_bouton != NULL) {
      int i;
      for (i = 0; i < (*menu)->nb_bouton; i++) {
        menu_detruire_bouton(&((*menu)->tab_bouton[i]));
      }
      free((*menu)->tab_bouton);
      (*menu)->tab_bouton = NULL;
    }
    free(*menu);
    *menu = NULL;
  }
  return OK;
}

/**
 * \fn t_erreur menu_gestion_SDL(t_menu * menu, int mouseState, t_type_menu * type_menu_suivant)
 * \brief Met à jour le menu
 * \param menu Menu que l'on veut gérer
 * \param mouse Info de la souris
 * \param type_menu_suivant Pointeur sur le menu suivant, MENU_NULL sinon
 * \return Code erreur
*/
t_erreur menu_gestion_SDL(t_menu *menu, int mouseState, t_type_menu *type_menu_suivant) {
  /* Vérification */
  if (menu == NULL) {
    erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le menu NULL");
    return PTR_NULL;
  }
  if (menu->tab_bouton == NULL) {
    erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le tab_bouton NULL");
    return PTR_NULL;
  }
  if (type_menu_suivant == NULL) {
    erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le pos_btn_pressed NULL");
    return PTR_NULL;
  }

  /* Récupération coordonnée menu */
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  /* Gestion souris menu */
  *type_menu_suivant = MENU_NULL;
  int i;
  for (i = 0; i < menu->nb_bouton; i++) {
    SDL_Rect r = {menu->tab_bouton[i]->x, menu->tab_bouton[i]->y, menu->tab_bouton[i]->width, menu->tab_bouton[i]->height};
    SDL_Point p = {mouseX, mouseY};
    if (SDL_PointInRect(&p, &r)) {
      menu->tab_bouton[i]->focus = 1;
      if (menu->tab_bouton[i]->state == PRESSED && mouseState == RELEASED) {
        *type_menu_suivant = menu->tab_bouton[i]->suivant;
        menu->tab_bouton[i]->state = RELEASED;
      } else if (mouseState == PRESSED) {
        menu->tab_bouton[i]->state = PRESSED;
      }
    } else {
      menu->tab_bouton[i]->focus = 0;
    }
  }

  return OK;
}

/**
 * \fn t_erreur menu_suivant(t_menu ** menu, t_type_menu type_menu_suivant)
 * \brief Passe au Menu suivant
 * \param menu Double pointeur sur le menu
 * \param type_menu_suivant Type du menu suivant
 * \return Code erreur
*/
t_erreur menu_suivant(t_menu **menu, t_type_menu type_menu_suivant) {
  /* Vérification */
  if (menu == NULL) {
    erreur_save(PTR_NULL, "menu_suivant() : Double pointeur sur le menu NULL");
    return PTR_NULL;
  }
  if (*menu == NULL) {
    erreur_save(PTR_NULL, "menu_suivant() : Pointeur sur le menu NULL");
    return PTR_NULL;
  }

  /* Création + destruction du menu */
  t_menu *tamp;
  menu_creer(type_menu_suivant, (*menu)->width, (*menu)->height, &tamp);
  menu_detruire(menu);
  *menu = tamp;

  return OK;
}
