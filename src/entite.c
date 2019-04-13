/**
 * \file entite.c
 * \brief Module servant à gérer les entités.
 * \author GALBRUN Tibane
 * \date 13 Mars 2019
 * \version 0.2
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <block.h>
#include <chemin.h>
#include <entite.h>
#include <erreur.h>
#include <fps.h>
#include <json.h>
#include <map.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <touches.h>
#include <perlin.h>
#include <commun.h>

/****** SPRITE TEXTURE ACTION ******/

SDL_Texture *Textures_Joueur;
t_anim_action t_a_joueur[NB_LIGNES_SPRITE] = {{MARCHE_DROITE, 12, 9, 100},   {MARCHE_GAUCHE, 10, 9, 100}, {MARCHE_DERRIERE, 11, 9, 100},
                                              {MARCHE_DEVANT, 9, 9, 100},    {CREUSER_DEVANT, 5, 8, 100}, {CREUSER_DERRIERE, 7, 8, 100},
                                              {CREUSER_GAUCHE, 6, 8, 100},   {CREUSER_DROITE, 8, 8, 100}, {ATTAQUE_DEVANT, 13, 6, 80},
                                              {ATTAQUE_DERRIERE, 15, 6, 80}, {ATTAQUE_GAUCHE, 14, 6, 80}, {ATTAQUE_DROITE, 16, 6, 80},
                                              {IMMOBILE, 3, 1, 50}};

SDL_Texture *Textures_Zombie;
t_anim_action t_a_zombie[NB_LIGNES_SPRITE] = {{MARCHE_DROITE, 12, 9, 100},   {MARCHE_GAUCHE, 10, 9, 100}, {MARCHE_DERRIERE, 11, 9, 100},
                                              {MARCHE_DEVANT, 9, 9, 100},    {CREUSER_DEVANT, 5, 8, 100}, {CREUSER_DERRIERE, 7, 8, 100},
                                              {CREUSER_GAUCHE, 6, 8, 100},   {CREUSER_DROITE, 8, 8, 100}, {ATTAQUE_DEVANT, 13, 6, 80},
                                              {ATTAQUE_DERRIERE, 15, 6, 80}, {ATTAQUE_GAUCHE, 14, 6, 80}, {ATTAQUE_DROITE, 16, 6, 80},
                                              {IMMOBILE, 3, 1, 50}};

SDL_Texture *Textures_Boss;
t_anim_action t_a_boss[NB_LIGNES_SPRITE] = {{MARCHE_DROITE, 12, 9, 100},   {MARCHE_GAUCHE, 10, 9, 100}, {MARCHE_DERRIERE, 11, 9, 100},
                                            {MARCHE_DEVANT, 9, 9, 100},    {CREUSER_DEVANT, 5, 8, 100}, {CREUSER_DERRIERE, 7, 8, 100},
                                            {CREUSER_GAUCHE, 6, 8, 100},   {CREUSER_DROITE, 8, 8, 100}, {ATTAQUE_DEVANT, 13, 6, 80},
                                            {ATTAQUE_DERRIERE, 15, 6, 80}, {ATTAQUE_GAUCHE, 14, 6, 80}, {ATTAQUE_DROITE, 16, 6, 80},
                                            {IMMOBILE, 3, 1, 50}};

/****** FONCTIONS CREATION ET SUPPRESSION ENTITE ******/

/**
 * \fn t_entite * creer_entite_defaut (char * name, t_entite_type type, int taille)
 * \brief Créer une entité avec des paramètres par défaut.
 * \param name Le nom de l'entité.
 * \param type Le type de l'entité.
 * \param x_dep Coordonnée de départ de l'entité.
 * \param y_dep Coordonnée de départ de l'entité.
 * \param taille Taille de l'entité en Y.
 * \return Un pointeur sur l'entité créée.
*/
t_entite *creer_entite_defaut(char *name, t_entite_type type, int x_dep, int y_dep, int taille) {
  switch (type) {
  case JOUEUR:
    return creer_entite((name) ? name : "PLAYER", 20, 20, 10, 10, 15, Textures_Joueur, t_a_joueur, x_dep, y_dep, taille, type);
  case ZOMBIE:
    return creer_entite((name) ? name : "ZOMBIE", 0, 0, 10, 10, 25, Textures_Zombie, t_a_zombie, x_dep, y_dep, taille, type);
  case BOSS:
    return creer_entite((name) ? name : "BOSS", 50, 50, 30, 30, 35, Textures_Boss, t_a_boss, x_dep, y_dep, taille, type);
  }
  return NULL;
}

/**
 * \fn t_entite * creer_entite (char * name, uint32_t mana, uint32_t mana_max, uint32_t pv, uint32_t pv_max, uint32_t damage, SDL_Texture * texture, t_anim_action * t_a,int taille, t_entite_type type)
 * \brief Créer une entité.
 * \param name Le nom de l'entité.
 * \param mana Le mana de départ de l'entité.
 * \param mana_max Le mana max que peut avoir l'entité.
 * \param pv Les pv de départ de l'entité.
 * \param pv_max Les pv max de l'entité.
 * \param damage Les dégats de base de l'entité.
 * \param texture La texture de l'entité.
 * \param t_a Emplacement des textures liées à une action.
 * \param x_dep Coordonnée de départ de l'entité.
 * \param y_dep Coordonnée de départ de l'entité.
 * \param taille Taille de l'entité en Y.
 * \param Type de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite *creer_entite(char *name, uint32_t mana, uint32_t mana_max, uint32_t pv, uint32_t pv_max, uint32_t damage, SDL_Texture *texture,
                       t_anim_action *t_a, int x_dep, int y_dep, int taille, t_entite_type type) {
  if (!texture || !name || !t_a)
    return NULL;
  if (mana > mana_max || pv > pv_max) {
    mana = mana_max;
    pv = pv_max;
  };

  /* Endroit de départ dans le sprite pour animation */
  SDL_Rect sprite_part = {0 + DECAL_W_SPRITE, t_a[0].ligne * H_PART_SPRITE + DECAL_H_SPRITE, W_PART_SPRITE / 2, H_PART_SPRITE / 1.25};

  /* Initialisation de la taille de l'entité */
  SDL_Rect hit = {x_dep * width_block_sdl, y_dep * height_block_sdl, taille * sprite_part.w / sprite_part.h, taille};

  t_entite *entite = malloc(sizeof(t_entite));
  entite->id = sizeof(*name); // sizeof temporaire
  entite->name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(entite->name, name);
  entite->xp = 0;
  entite->faim = entite->faim_max = 10;
  entite->mana = mana;
  entite->mana_max = mana_max;
  entite->pv = pv;
  entite->pv_max = pv_max;
  entite->texture = texture;
  entite->texture_part = sprite_part;
  entite->texture_action = t_a;
  entite->col_act_prec = 0;
  entite->act_pred = IMMOBILE;
  entite->temp_dep = SDL_GetTicks();
  entite->hitbox = hit;
  entite->posEnt = entite->hitbox;
  entite->posEnt.x = POSX_ENT_SCREEN(entite);
  entite->posEnt.y = POSY_ENT_SCREEN(entite);
  entite->accX = VITESSE_DEPLACEMENT;
  entite->accY = 0.5;
  entite->velX = 0;
  entite->velY = 0;
  entite->type = type;
  entite->damage = damage;
  entite->nb_saut = NB_SAUT;

  return entite;
}

/**
 * \fn t_erreur detruire_entite (t_entite * entite)
 * \brief Détruit une entité.
 * \param entite L'entité à détruire.
 * \return Une erreur s'il y en a une.
*/
t_erreur detruire_entite(t_entite *entite) {
  if (!entite)
    return PTR_NULL;
  free(entite->name);
  free(entite);
  return OK;
}

/**
 * \fn t_liste * Create_Liste_Entite (int x1, int x2, int y, t_entite_type type, int nb_entite, int taille)
 * \brief Créer une liste d'entité d'un certain type entre 2 points.
 * \brief Si le y est négatif, il est créé avec le bruit de perlin.
 * \param x1 Le x de gauche dans l'intervalle.
 * \param x2 Le x de droite dans l'intervalle.
 * \param y Le y de création.
 * \param type Le type de l'entité à créer.
 * \param nb_entite Le nombre d'entité à créer dans l'intervale [x1;x2].
 * \param taille La taille des entités à créer.
 * \return La liste d'entités créées.
*/
t_liste * Create_Liste_Entite (int x1, int x2, int y, t_entite_type type, int nb_entite, int taille)
{
  t_entite * entite;
  uint8_t perlin = 0;
  int x;

  /* Vérif paramètre */
  if (x2 < x1) x2 = x1;
  if (nb_entite <= 0) return NULL;
  if (y < 0) perlin = 1;

  /* Initialisation liste */
  t_liste * liste = malloc(sizeof(t_liste));
  init_liste(liste);

  /* Création des entités */
  int i;
  for (i = 0; i < nb_entite; i++)
  {
    x = RAND_AB(x1,x2);
    if (perlin)
      y = (perlin2d(x, MAX / 2, FREQ, DEPTH) * MAX / 2) + HAUTEUR_MINIMUN;
    entite = creer_entite_defaut(NULL,type,x,y,taille);
    ajout_droit(liste,(void *)entite);
    fprintf(stderr,"Entite %d -> %d:%d\n",i+1,x,y);
  }

  return liste;
}

/**
 * \fn t_erreur Destroy_Liste_Entite (t_liste ** entite)
 * \brief Détruit une liste d'entités.
 * \param entite Un pointeur sur la liste à détruire.
 * \return Une erreur s'il y en a une.
*/
t_erreur Destroy_Liste_Entite (t_liste ** entite)
{
  if (!entite) return PTR_NULL;
  if (!*entite) return PTR_VALUE_ERROR;

  detruire_liste(*entite,free);
  *entite = NULL;

  return OK;
}

/****** FONCTIONS MODIF PARAMETRE ENTITE ******/

/**
 * \fn t_erreur Change_Name_Entite (t_entite * entite, char * name)
 * \brief Change le nom d'une entité.
 * \param entite L'entité à modifier.
 * \param name Le nouveau nom.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_Name_Entite(t_entite *entite, char *name) {
  if (!entite || !name || !entite->name)
    return PTR_NULL;

  entite->name = realloc(entite->name, sizeof(char) * strlen(name) + 1);
  strcpy(entite->name, name);

  return OK;
}

/**
 * \fn t_erreur Change_Faim_Entite (t_entite * entite, uint32_t faim, uint32_t faim_max)
 * \brief Change la faim d'une entité.
 * \brief La faim doit être inférieure à la faim maximale et supérieure à 0.
 * \param entite L'entité à modifier.
 * \param faim La nouvelle faim.
 * \param faim_max La nouvelle faim maximale.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_Faim_Entite(t_entite *entite, uint32_t faim, uint32_t faim_max) {
  if (!entite)
    return PTR_NULL;
  if (faim <= 0 || faim_max <= 0)
    return VALUE_ERROR;
  if (faim > faim_max)
    faim = faim_max;

  entite->faim = faim;
  entite->faim_max = faim_max;

  return OK;
}

/**
 * \fn t_erreur Change_Mana_Entite (t_entite * entite, uint32_t mana, uint32_t mana_max)
 * \brief Change la mana d'une entité.
 * \brief La mana doit être inférieure à la mana maximale et supérieure à 0.
 * \param entite L'entité à modifier.
 * \param mana La nouvelle mana.
 * \param mana_max La nouvelle mana maximale.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_Mana_Entite(t_entite *entite, uint32_t mana, uint32_t mana_max) {
  if (!entite)
    return PTR_NULL;
  if (mana <= 0 || mana_max <= 0)
    return VALUE_ERROR;
  if (mana > mana_max)
    mana = mana_max;

  entite->mana = mana;
  entite->mana_max = mana_max;

  return OK;
}

/**
 * \fn t_erreur Change_PV_Entite (t_entite * entite, uint32_t pv, uint32_t pv_max)
 * \brief Change les pv d'une entité.
 * \brief Les pv doivent être inférieur aux pv maximum et supérieur à 0.
 * \param entite L'entité à modifier.
 * \param pv Les nouveaux pv.
 * \param pv_max Les nouveaux pv maximum.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_PV_Entite(t_entite *entite, uint32_t pv, uint32_t pv_max) {
  if (!entite)
    return PTR_NULL;
  if (pv <= 0 || pv_max <= 0)
    return VALUE_ERROR;
  if (pv > pv_max)
    pv = pv_max;

  entite->pv = pv;
  entite->pv_max = pv_max;

  return OK;
}

/**
 * \fn t_erreur Change_XP_Entite (t_entite * entite, uint64_t xp)
 * \brief Change l'xp d'une entité.
 * \brief L'xp doit être supérieur à 0.
 * \param entite L'entité à modifier.
 * \param pv La nouvelle xp.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_XP_Entite(t_entite *entite, uint64_t xp) {
  if (!entite)
    return PTR_NULL;
  if (xp < 0)
    return VALUE_ERROR;

  entite->xp = xp;

  return OK;
}

/**
 * \fn t_erreur Change_Damage_Entite (t_entite * entite, uint32_t damage)
 * \brief Change les dégats d'une entité.
 * \brief Les dégats doivent être supérieur ou égals à 0.
 * \param entite L'entité à modifier.
 * \param damage Les nouveaux dégats de l'entité.
 * \return Une erreur s'il y en a une.
*/
t_erreur Change_Damage_Entite(t_entite *entite, uint32_t damage) {
  if (!entite)
    return PTR_NULL;
  if (damage < 0)
    return VALUE_ERROR;

  entite->damage = damage;

  return OK;
}

/**
 * \fn t_erreur Add_Faim_Entite (t_entite * entite, int32_t faim)
 * \brief Ajoute ou Retire de la faim à l'entité.
 * \param entite L'entité à modifier.
 * \param faim La faim à ajouter ou retirer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Add_Faim_Entite(t_entite *entite, int32_t faim) {
  if (!entite)
    return PTR_NULL;

  if ((int)entite->faim + faim < 0)
    entite->faim = 0;
  else if (entite->faim + faim > entite->faim_max)
    entite->faim = entite->faim_max;
  else
    entite->faim += faim;

  return OK;
}

/**
 * \fn t_erreur Add_Mana_Entite (t_entite * entite, int32_t mana)
 * \brief Ajoute ou Retire de la mana à l'entité.
 * \param entite L'entité à modifier.
 * \param mana La mana à ajouter ou retirer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Add_Mana_Entite(t_entite *entite, int32_t mana) {
  if (!entite)
    return PTR_NULL;

  if ((int)entite->mana + mana < 0)
    entite->mana = 0;
  else if (entite->mana + mana > entite->mana_max)
    entite->mana = entite->mana_max;
  else
    entite->mana += mana;

  return OK;
}

/**
 * \fn t_erreur Add_PV_Entite (t_entite * entite, int32_t pv)
 * \brief Ajoute ou Retire des pv à l'entité.
 * \param entite L'entité à modifier.
 * \param pv Les pv à ajouter ou retirer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Add_PV_Entite(t_entite *entite, int32_t pv) {
  if (!entite)
    return PTR_NULL;

  if ((int)entite->pv + pv < 0)
    entite->pv = 0;
  else if (entite->pv + pv > entite->pv_max)
    entite->pv = entite->pv_max;
  else
    entite->pv += pv;

  return OK;
}

/**
 * \fn t_erreur Add_XP_Entite (t_entite * entite, int64_t xp)
 * \brief Ajoute ou Retire de l'xp à l'entité.
 * \param entite L'entité à modifier.
 * \param xp L'xp à ajouter ou retirer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Add_XP_Entite(t_entite *entite, int64_t xp) {
  if (!entite)
    return PTR_NULL;

  if ((int)entite->xp + xp < 0)
    entite->xp = 0;
  else
    entite->xp += xp;

  return OK;
}

/**
 * \fn t_erreur Add_Damage_Entite (t_entite * entite, int32_t damage)
 * \brief Ajoute ou Retire de les dégats à l'entité.
 * \param entite L'entité à modifier.
 * \param damage Les dégats à ajouter ou retirer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Add_Damage_Entite(t_entite *entite, int32_t damage) {
  if (!entite)
    return PTR_NULL;

  if ((int)entite->damage + damage < 0)
    entite->damage = 0;
  else
    entite->damage += damage;

  return OK;
}

/****** FONCTIONS GESTION SPRITE ******/

/**
 * \fn SDL_Texture * Create_Sprite (char * lieu, SDL_Renderer * renderer)
 * \brief Crée la texture d'un sprite.
 * \param lieu L'endroit où se situe le sprite à charger.
 * \param renderer Renderer de la fenêtre.
 * \return Un pointeur sur une structure.
*/
SDL_Texture *Create_Sprite(char *lieu, SDL_Renderer *renderer) {
  if (!renderer || !lieu)
    return NULL;

  char *chemin;
  creation_chemin(lieu, &chemin);

  SDL_Texture *texture;
  Create_IMG_Texture(renderer, chemin, &texture);
  free(chemin);

  return texture;
}

/**
 * \fn t_erreur Charger_Anima (SDL_Renderer * renderer, t_entite * entite, t_action action)
 * \brief Charge dans le renderer, suivant une action et une entité, l'image suivante (pour animation) où une nouvelle image si l'action à changer.
 * \param renderer Renderer de la fenêtre.
 * \param entite L'entité à afficher.
 * \param action L'action à afficher.
 * \return Une erreur s'il y en a une.
*/
t_erreur Charger_Anima(SDL_Renderer *renderer, t_entite *entite, t_action action) {
  if (!renderer || !entite)
    return PTR_NULL;

  /* On cherche l'action associée à l'entité */
  int i = Search_Action(entite->texture_action, action);
  if (i == -1)
    return VALUE_ERROR;

  /* On redémarre l'animation à zéro si on est arrivé au bout */
  if (entite->col_act_prec == entite->texture_action[i].nb_col)
    entite->col_act_prec = 0;
  /* On redémarre l'animation à 0 si l'action a changé */
  if (entite->act_pred != action)
    entite->col_act_prec = 0;

  /* On met à jour l'animation */
  entite->texture_part.y = (entite->texture_action[i].ligne - 1) * H_PART_SPRITE + DECAL_H_SPRITE;
  entite->texture_part.x = (entite->col_act_prec) * W_PART_SPRITE + DECAL_W_SPRITE;
  SDL_RenderCopy(renderer, entite->texture, &(entite->texture_part), &(entite->posEnt));

  /* On regarde si l'animation est finie avant de passer à la suivante */
  if (entite->act_pred == action && (SDL_GetTicks() - entite->temp_dep) >= entite->texture_action[i].temps_anim) {
    (entite->col_act_prec)++;
    entite->temp_dep = SDL_GetTicks();
  }
  entite->act_pred = action;

  return OK;
}

/**
 * \fn int Search_Action (t_anim_action * t_a, t_action action)
 * \brief Cherche dans un tableau d'action/description l'indice correspondant à l'action qu'on cherche.
 * \param t_a Le tableau de recherche.
 * \param action L'action que l'on cherche.
 * \return L'indice de l'action recherchée.
*/
int Search_Action(t_anim_action *t_a, t_action action) {
  if (!t_a)
    return -1;

  int i;
  for (i = 0; t_a[i].action != action && t_a[i].action != IMMOBILE; i++)
    ;

  return i;
}

/**
 * \fn t_erreur Init_Sprite(SDL_Renderer * renderer)
 * \brief Initialise la texture associée au sprite de chaque entité par défaut.
 * \param renderer Renderer de la fenêtre.
 * \return Une erreur s'il y en a une.
*/
t_erreur Init_Sprite(SDL_Renderer *renderer) {
  if (!renderer)
    return PTR_NULL;
  /* Création de la texture pour chaque SPRITE */
  Textures_Joueur = Create_Sprite("IMG/texture/entite/joueur/sprite_apoil.png", renderer);
  Textures_Zombie = Create_Sprite("IMG/texture/entite/zombie/sprite_apoil.png", renderer);
  Textures_Boss = Create_Sprite("IMG/texture/entite/boss/sprite_boss1.png", renderer);

  return OK;
}

/**
 * \fn t_erreur Quit_Sprite(void)
 * \brief Détruit toutes les textures précédement initialisées.
 * \return Une erreur s'il y en a une.
*/
t_erreur Quit_Sprite(void) {
  /* Destruction des textures */
  SDL_DestroyTexture(Textures_Joueur);
  SDL_DestroyTexture(Textures_Zombie);
  SDL_DestroyTexture(Textures_Boss);
  return OK;
}

/**
 * \fn t_erreur Anim_Update (t_entite * entite, t_action action, int new_time)
 * \brief Modifie pour une entité le temps d'une animation correspondant à une action.
 * \param entite L'entité où il faut changer le temps d'animation.
 * \param action L'action où l'on modifie le temps d'animation.
 * \param new_time Le nouveau temps d'animation.
 * \return Une erreur s'il y en a une.
*/
t_erreur Anim_Update(t_entite *entite, t_action action, int new_time) {
  if (!entite)
    return PTR_NULL;
  if (new_time < 0)
    return VALUE_ERROR;

  int i = Search_Action(entite->texture_action, action);
  entite->texture_action[i].temps_anim = new_time;

  return OK;
}

/****** FONCTION GESTION COLLISION ENTITE + GRAVITE ******/

/**
 * \fn t_erreur update_posY_entite(t_entite * entite, double coef_fps, t_liste * p, uint8_t pos)
 * \brief Gère la position de l'entité sur Y via la gravité et les collisions.
 * \param entite L'entité à gérer.
 * \param coef_fps Permet d'adapter les déplacements en fonction du nombre de fps.
 * \param p Liste contenant les paramètres supplémentaires de la fonction collision si il y en a besoin.
 * \param pos Position pour savoir si l'entité doit être bloqué dans l'affichage lorsqu'elle tombe.
 * \return Une erreur s'il y en a une.
*/
t_erreur update_posY_entite(t_entite *entite, double coef_fps, t_liste *p, uint8_t pos) {
  //fprintf(stderr,"Vel Y -> %.2f\n", entite->velY);
  if (!entite)
    return PTR_NULL;

  int diff; // Profondeur de la collision
  diff = collision(entite, DIRECT_HAUT_COLLI, p);
  if (diff > 0) {
    entite->hitbox.y -= diff;
  }

  if (coef_fps > 5)
    coef_fps = 5;
  int i;
  for (i = 0; i < coef_fps; i++) {
    entite->velY += entite->accY;
    int grav = entite->velY;
    entite->hitbox.y -= grav;
  }
  if ((diff = collision(entite, DIRECT_BAS_COLLI, p)) > 0) {
    entite->velY = 0;
    entite->hitbox.y += diff;
  } //printf("Diff : %d\n", diff);
  // if (pos & CENTER_SCREEN && ((!entite->velY && diff > 0) || entite->posEnt.y >= POSY_ENT_SCREEN(entite))) {
  //   entite->posEnt.y = POSY_ENT_SCREEN(entite);
  // }

  return OK;
}

/**
 * \fn t_erreur update_posY_Liste_entite(t_liste * entite, double coef_fps, t_liste * p, uint8_t pos)
 * \brief Update la position en Y d'une liste d'entités.
 * \param entite La liste d'entités à update.
 * \param coef_fps Permet d'adapter les déplacements en fonction du nombre de fps.
 * \param p Liste contenant les paramètres supplémentaires de la fonction collision si il y en a besoin.
 * \param pos Position pour savoir si l'entité doit être bloqué dans l'affichage lorsqu'elle tombe.
 * \return Une erreur s'il y en a une.
*/
t_erreur update_posY_liste_entite(t_liste * entite, double coef_fps, t_liste * p, uint8_t pos)
{
  if (!entite) return PTR_NULL;
  t_entite * ent;
  for(en_tete(entite);!hors_liste(entite);suivant(entite))
  {
    valeur_elt(entite,(void **)&ent);
    update_posY_entite(ent,coef_fps,p,pos);
  }
  return OK;
}

/**
 * \fn int collision(t_entite *entite, t_collision_direction direction, t_liste *p)
 * \brief Calcul la profondeur d'une collision en fonction d'une direction et d'une entité.
 * \param entite L'entité à collisionner.
 * \param direction Direction de la direction.
 * \param p La liste de blocs permettant de calculer les collisions.
 * \return La profondeur de la collision, 0 sinon.
*/
int collision(t_entite *entite, t_collision_direction direction, t_liste *p)
{
  if (!entite || !p)
    return 0;

  int collision = 0;
  SDL_Rect res;
  t_block *block = NULL;

  /* Conversion des coordonnées SDL en coordonnées pour la MAP */
  int w = entite->hitbox.w, h = entite->hitbox.h;
  int x = (entite->hitbox.x) / width_block_sdl, y = (entite->hitbox.y) / height_block_sdl;

  /* Recréation de la MAP */
  t_map map;
  map.list = p;

  /* Traitement des collisions */
  switch (direction) {
  /* Collision en BAS */
  case DIRECT_BAS_COLLI:
    while (collision <= 0 && x < ((entite->hitbox.x + w) / width_block_sdl)) {
      block = MAP_GetBlock(&map, x, y - 1);
      // Récup Block
      // Check si collision
      if (block) {
        if (block->id != AIR) {
          SDL_Rect B = {width_block_sdl * block->x, height_block_sdl * block->y, width_block_sdl, height_block_sdl};
          SDL_IntersectRect(&(entite->hitbox), &B, &res);
          if(block->y * height_block_sdl > entite->hitbox.y - h)
            collision = block->y * height_block_sdl - (entite->hitbox.y - h) + 1;
          
          //collision = res.h;
          //fprintf(stderr, " b.x:%d b.y:%d x:%d y:%d w:%d h:%d res.h:%d\n", block->x, block->y, x, y, w, h, res.h);
        }
      }

      // Mis à jour du x
      x += 1;
      //fprintf(stderr,"------> %d\n", res.h);
    }
    if (collision)
      entite->nb_saut = NB_SAUT;
    break;

  /* Collision en HAUT */
  case DIRECT_HAUT_COLLI:
    while (collision <= 0 && x < ((entite->hitbox.x + w) / width_block_sdl)) {
      block = MAP_GetBlock(&map, x, y);
      // Récup Block
      // Check si collision
      if (block) {
        if (block->id != AIR) {
          SDL_Rect B = {width_block_sdl * block->x, height_block_sdl * block->y, width_block_sdl, height_block_sdl};
          SDL_IntersectRect(&(entite->hitbox), &B, &res);
          collision = res.h;
          //fprintf(stderr, " b.x:%d b.y:%d x:%d y:%d w:%d h:%d res.h:%d\n", block->x, block->y, x, y, w, h, res.h);
        }
      }

      // Mis à jour du x
      x += 1;
      //fprintf(stderr,"------> %d\n", res.h);
    }
    break;

  /* Collision à DROITE */
  case DIRECT_DROITE_COLLI:
    while (collision <= 0 && y > ((entite->hitbox.y - h) / height_block_sdl)) {
      block = MAP_GetBlock(&map, x + 1, y);
      // Récup Block
      // Check si collision
      if (block) {
        if (block->id != AIR) {
          SDL_Rect B = {width_block_sdl * block->x, height_block_sdl * block->y, width_block_sdl, height_block_sdl};
          SDL_IntersectRect(&(entite->hitbox), &B, &res);
          collision = res.h;
          //fprintf(stderr, " b.x:%d b.y:%d x:%d y:%d w:%d h:%d res.h:%d\n", block->x, block->y, x, y, w, h, res.h);
        }
      }

      // Mis à jour du x
      y -= 1;
      //fprintf(stderr,"------> %d\n", res.h);
    }
    break;

  /* Collision à GAUCHE */
  case DIRECT_GAUCHE_COLLI:
    while (collision <= 0 && y > ((entite->hitbox.y - h) / height_block_sdl)) {
      block = MAP_GetBlock(&map, x - 1, y);
      // Récup Block
      // Check si collision
      if (block) {
        if (block->id != AIR) {
          SDL_Rect B = {width_block_sdl * block->x, height_block_sdl * block->y, width_block_sdl, height_block_sdl};
          SDL_IntersectRect(&(entite->hitbox), &B, &res);
          collision = res.h;
          //fprintf(stderr, " b.x:%d b.y:%d x:%d y:%d w:%d h:%d res.h:%d\n", block->x, block->y, x, y, w, h, res.h);
        }
      }

      // Mis à jour du x
      y -= 1;
      //fprintf(stderr,"------> %d\n", res.h);
    }
    break;

  default:
    break;
  }
  /* ANCIENNE VERSION */
  // /* Conversion des coordonnées SDL en coordonnées pour la MAP */
  // int x = entite->hitbox.x / width_block_sdl, y = entite->hitbox.y / height_block_sdl;
  // /* Recréation de la MAP */
  // t_map map;
  // map.list = p;

  // /* Récupération des Blocks si il y en a, en fonction des coordonnées du Joueur */
  // t_block *blockH = NULL, *blockB = NULL, *blockHD = NULL, *blockHG = NULL;
  // blockH = MAP_GetBlock(&map, x, y + 1);
  // blockB = MAP_GetBlock(&map, x, y - 1);
  // blockHD = MAP_GetBlock(&map, x + 1, y);
  // blockHG = MAP_GetBlock(&map, x - 1, y);

  // /* Traitement des collisions */
  // switch (direction) {
  // /* Collision en BAS */
  // case DIRECT_BAS_COLLI:
  //   if (blockB) {
  //     if (blockB->id != AIR) {
  //       SDL_Rect B = {width_block_sdl * blockB->x, height_block_sdl * blockB->y, width_block_sdl, height_block_sdl};
  //       SDL_IntersectRect(&(entite->hitbox), &B, &res);
  //       collision = res.h;
  //     }
  //   }
  //   break;

  // /* Collision en HAUT */
  // case DIRECT_HAUT_COLLI:
  //   if (blockH) {
  //     if (blockH->id != AIR) {
  //       SDL_Rect B = {width_block_sdl * blockH->x, height_block_sdl * blockH->y, width_block_sdl, height_block_sdl};
  //       SDL_IntersectRect(&(entite->hitbox), &B, &res);
  //       collision = res.h;
  //     }
  //   }
  //   break;

  // /* Collision à DROITE */
  // case DIRECT_DROITE_COLLI:
  //   if (blockHD) {
  //     if (blockHD->id != AIR) {
  //       SDL_Rect B = {width_block_sdl * blockHD->x, height_block_sdl * blockHD->y, width_block_sdl, height_block_sdl};
  //       SDL_IntersectRect(&(entite->hitbox), &B, &res);
  //       collision = res.w;
  //     }
  //   }
  //   break;

  // /* Collision à GAUCHE */
  // case DIRECT_GAUCHE_COLLI:
  //   if (blockHG) {
  //     if (blockHG->id != AIR) {
  //       SDL_Rect B = {width_block_sdl * blockHG->x, height_block_sdl * blockHG->y, width_block_sdl, height_block_sdl};
  //       SDL_IntersectRect(&(entite->hitbox), &B, &res);
  //       collision = res.w;
  //     }
  //   }
  //   break;

  // default:
  //   break;
  // }
  /**/
  if (collision < 0)
    collision *= -1;
  return collision;
}

/************** Focntion qui gère les déplacements et les animations de l'entité **************/

/**
 * \fn t_erreur Gestion_Entite (SDL_Renderer * renderer, t_entite * entite, uint8_t * ks, double coef_fps, t_liste * p, uint8_t type_gestion, t_action action, t_entite * ref, uint8_t pos)
 * \brief Gère une entité (collision, déplacement, animation).
 * \brief Gère les animations ainsi que les modifications apportées à l'entité (gravité, collision, déplacement) correspondant aux différents appuis de touches ou non.
 * \param renderer Renderer de la fenêtre.
 * \param entite L'entité à gérer.
 * \param ks Etat du clavier pour la gestion de l'appui des touches.
 * \param coef_fps Permet d'adapter les déplacements en fonction du nombre de fps.
 * \param p Liste contenant les paramètres supplémentaires de la fonction collision si il y en a besoin.
 * \param type_gestion La gestion à appliquer à l'entité (si on veut les touches on non).
 * \param action L'action à effectuer si jamais pas de gestion des touches.
 * \param ref Entité de référence pour affichage.
 * \param pos La position de l'entité sur l'écran, permet de savoir si elle est au centre ou non.
 * \return Une erreur s'il y en a une.
*/
t_erreur Gestion_Entite(SDL_Renderer *renderer, t_entite *entite, uint8_t *ks, double coef_fps, t_liste *p, uint8_t type_gestion, t_action action,
                        t_entite *ref, uint8_t pos) {
  if (!renderer || !entite || !ks)
    return PTR_NULL;

  int diff; // Profondeur de la collision

  if (type_gestion & GESTION_TOUCHES) /* Gestion des touches et actions associées */
  {
    /* Modif pour la touche AVANCER */
    if (SDL_touche_appuyer(ks, AVANCER)) {
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DEVANT, pos);
    }
    /* Modif pour la touche RECULER */
    else if (SDL_touche_appuyer(ks, RECULER)) {
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DERRIERE, pos);
    }
    /* Modif pour la touche DROITE */
    else if (SDL_touche_appuyer(ks, DROITE)) {

      diff = collision(entite, DIRECT_DROITE_COLLI, p);
      if (diff <= 0)
        entite->hitbox.x += entite->accX * coef_fps;
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DROITE, pos);
    }
    /* Modif pour la touche GAUCHE */
    else if (SDL_touche_appuyer(ks, GAUCHE)) {

      diff = collision(entite, DIRECT_GAUCHE_COLLI, p);
      if (diff <= 0)
        entite->hitbox.x -= entite->accX * coef_fps;
      Print_Entite_Screen(renderer, ref, entite, MARCHE_GAUCHE, pos);
    }
    /* Modif quand on appui sur AUCUNE touche */
    else
      Print_Entite_Screen(renderer, ref, entite, IMMOBILE, pos);

    /* Modif pour la touche SHIFT (Accélérer) */
    if (SDL_touche_appuyer(ks, SHIFT)) {
      entite->accX = VITESSE_DEPLACEMENT * ACCELERATION;
      Anim_Update(entite, MARCHE_DROITE, 25);
      Anim_Update(entite, MARCHE_GAUCHE, 25);
      Anim_Update(entite, MARCHE_DEVANT, 25);
      Anim_Update(entite, MARCHE_DERRIERE, 25);
    } else {
      entite->accX = VITESSE_DEPLACEMENT;
      Anim_Update(entite, MARCHE_DROITE, 100);
      Anim_Update(entite, MARCHE_GAUCHE, 100);
      Anim_Update(entite, MARCHE_DEVANT, 100);
      Anim_Update(entite, MARCHE_DERRIERE, 100);
    }

    /* Modif pour la touche SAUTER */
    if (entite->nb_saut > 0 && SDL_touche_appuyer(ks, SAUTER)) {
      entite->velY -= HAUTEUR_SAUT;
      if (entite->nb_saut != 0)
        entite->nb_saut--;
    }

    /* Gravité */
    update_posY_entite(entite, coef_fps, p, pos);

  } else if (type_gestion & GESTION_ACTION) /* Gestion d'une action sans appui de touches */
  {
    if (!ref)
      return PTR_NULL;

    switch (action) {
    case IMMOBILE:
      Print_Entite_Screen(renderer, ref, entite, IMMOBILE, pos);
      break;

    case MARCHE_DEVANT:
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DEVANT, pos);
      break;

    case MARCHE_DERRIERE:
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DERRIERE, pos);
      break;

    case MARCHE_DROITE:
      diff = collision(entite, DIRECT_DROITE_COLLI, p);
      if (diff <= 0) {
        entite->hitbox.x += entite->accX * coef_fps;
      }
      Print_Entite_Screen(renderer, ref, entite, MARCHE_DROITE, pos);
      break;

    case MARCHE_GAUCHE:
      diff = collision(entite, DIRECT_GAUCHE_COLLI, p);
      if (diff <= 0) {
        entite->hitbox.x -= entite->accX * coef_fps;
      }
      Print_Entite_Screen(renderer, ref, entite, MARCHE_GAUCHE, pos);
      break;

    case SAUTER_ENT:
      if (!(entite->velY) && collision(entite, DIRECT_BAS_COLLI, p)) {
        entite->velY -= HAUTEUR_SAUT;
      }
      break;

    case ACCELERER:
      entite->accX = VITESSE_DEPLACEMENT * ACCELERATION;
      Anim_Update(entite, MARCHE_DROITE, 25);
      Anim_Update(entite, MARCHE_GAUCHE, 25);
      Anim_Update(entite, MARCHE_DEVANT, 25);
      Anim_Update(entite, MARCHE_DERRIERE, 25);
      break;

    case MARCHER:
      entite->accX = VITESSE_DEPLACEMENT;
      Anim_Update(entite, MARCHE_DROITE, 100);
      Anim_Update(entite, MARCHE_GAUCHE, 100);
      Anim_Update(entite, MARCHE_DEVANT, 100);
      Anim_Update(entite, MARCHE_DERRIERE, 100);
      break;

    case ATTAQUE_DEVANT:
      Print_Entite_Screen(renderer, ref, entite, ATTAQUE_DEVANT, pos);
      break;

    case ATTAQUE_DERRIERE:
      Print_Entite_Screen(renderer, ref, entite, ATTAQUE_DERRIERE, pos);
      break;

    case ATTAQUE_DROITE:
      Print_Entite_Screen(renderer, ref, entite, ATTAQUE_DROITE, pos);
      break;

    case ATTAQUE_GAUCHE:
      Print_Entite_Screen(renderer, ref, entite, ATTAQUE_GAUCHE, pos);
      break;

    case CREUSER_DEVANT:
      Print_Entite_Screen(renderer, ref, entite, CREUSER_DEVANT, pos);
      break;

    case CREUSER_DERRIERE:
      Print_Entite_Screen(renderer, ref, entite, CREUSER_DERRIERE, pos);
      break;

    case CREUSER_DROITE:
      Print_Entite_Screen(renderer, ref, entite, CREUSER_DROITE, pos);
      break;

    case CREUSER_GAUCHE:
      Print_Entite_Screen(renderer, ref, entite, CREUSER_GAUCHE, pos);
      break;

    default:
      break;
    }
  } else
    return VALUE_ERROR;

  return OK;
}

/**
 * \fn t_erreur Print_Info_Entite (SDL_Renderer * renderer, t_entite * entite)
 * \brief Affiche le nom de l'entité ainsi que ses pv et sa mana.
 * \param renderer Renderer de la fenêtre pour affichage des jauges.
 * \param entite L'entité pour les infos à afficher.
 * \return Une erreur s'il y en a une.
*/
t_erreur Print_Info_Entite(SDL_Renderer *renderer, t_entite *entite) {
  if (!entite)
    return PTR_NULL;

  int x = entite->posEnt.x;
  int y = entite->posEnt.y;
  int w = entite->posEnt.w;
  //int h = entite->posEnt.h;
  char *nom = entite->name;
  uint32_t pv = entite->pv;
  uint32_t pv_max = entite->pv_max;
  uint32_t mana = entite->mana;
  uint32_t mana_max = entite->mana_max;
  if (pv_max <= 0) {
    pv = 0;
    pv_max = 1;
  }
  if (mana_max <= 0) {
    mana = 0;
    mana_max = 1;
  }

  /******* PARTIE NOM ENTITE *******/

  /* Boite contenant le nom de l'entité */
  SDL_Rect posNom = {x - ((x + LARGEUR_NOM_ENT / 2) - (x + w / 2)), y - DECALAGE_NOM_ENT, LARGEUR_NOM_ENT, HAUTEUR_NOM_ENT};

  /* Couleur du nom */
  SDL_Color couleur = {255, 255, 255};

  /* Police du nom */
  int taille_police = posNom.w / (strlen(nom));
  char *police;
  creation_chemin("data/police/8-BIT_WONDER.ttf", &police);

  /* Création du texte pour le nom */
  SDL_Texture *texture;
  Create_Text_Texture(renderer, nom, police, taille_police, couleur, BLENDED, &texture);

  /* DEBUG */
  // char * chemin;
  // creation_chemin("IMG/texture/pierre.png",&chemin);
  // SDL_Texture * boite;
  // Create_IMG_Texture(renderer,chemin,&boite);

  /* Affichage */
  // SDL_RenderCopy(renderer,boite,NULL,&posNom);
  SDL_RenderCopy(renderer, texture, NULL, &posNom);

  /****** PARTIE JAUGE PV ET MANA ENTITE ******/

  /* Boite contenant la jauge de pv de l'entité */
  SDL_Rect posPV = posNom;
  posPV.y += HAUTEUR_NOM_ENT + HAUTEUR_NOM_ENT / 4;
  posPV.h = HAUTEUR_NOM_ENT / 4;

  SDL_Rect pvLong = posPV;
  pvLong.w = pvLong.w * pv / pv_max;

  /* Boite contenant la jauge de mana de l'entité */
  SDL_Rect posMana = posPV;
  posMana.y += posPV.h;

  SDL_Rect manaLong = posMana;
  manaLong.w = manaLong.w * mana / mana_max;

  /* Affichage des jauges */
  // PV
  SDL_SetRenderDrawColor(renderer, 91, 143, 91, 80);
  SDL_RenderFillRect(renderer, &posPV);
  SDL_SetRenderDrawColor(renderer, 255 - pv * 255 / pv_max, pv * 255 / pv_max, 0, 255);
  SDL_RenderFillRect(renderer, &pvLong);
  // MANA
  SDL_SetRenderDrawColor(renderer, 107, 72, 110, 80);
  SDL_RenderFillRect(renderer, &posMana);
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &manaLong);

  /* Libération de la mémoire + autres */
  SDL_DestroyTexture(texture);
  // SDL_DestroyTexture(boite);
  // free(chemin);
  free(police);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  return OK;
}

/**
 * \fn t_erreur Print_Entite_Screen (SDL_Renderer * renderer, t_entite * entite_ref, t_entite * entite_aff, t_action action, uint8_t pos)
 * \brief Affiche une entité sur l'écran avec ses informations (pv,mana,nom), soit au centre, soit en fonction d'une autre.
 * \param renderer Le renderer de la fenêtre.
 * \param entite_ref L'entité de référence si affichage en fonction d'elle.
 * \param entite_aff L'entité à afficher.
 * \param action L'action effectuer pour effectuer le bon affichage.
 * \param pos La position de l'entité sur l'écran, permet de savoir si elle est au centre ou non.
 * \return Une erreur s'il y en a une.
*/
t_erreur Print_Entite_Screen(SDL_Renderer *renderer, t_entite *entite_ref, t_entite *entite_aff, t_action action, uint8_t pos) {
  if (!entite_aff)
    return PTR_NULL;

  /* Affichage au centre de l'écran */
  if (pos & CENTER_SCREEN) {
    entite_aff->posEnt.x = POSX_ENT_SCREEN(entite_aff);
    entite_aff->posEnt.y = POSY_ENT_SCREEN(entite_aff);
    Charger_Anima(renderer, entite_aff, action);
    Print_Info_Entite(renderer, entite_aff);

  }
  /* Affichage */
  else if (pos & NOT_CENTER_SCREEN) {
    if (!entite_ref)
      return PTR_NULL;

    int x_diff = entite_ref->hitbox.x - entite_aff->hitbox.x;
    int y_diff = entite_ref->hitbox.y - entite_aff->hitbox.y;

    int newPosEntX = entite_ref->posEnt.x - x_diff;
    int newPosEntY;
    if (pos & INVERSION_AXE_Y)
      newPosEntY = entite_ref->posEnt.y - y_diff;
    else
      newPosEntY = entite_ref->posEnt.y + y_diff;

    /* Entité à afficher en dehors de l'écran */
    if (newPosEntX + entite_ref->posEnt.w < 0 || newPosEntX > width_window)
      return VALUE_ERROR;
    if (newPosEntY + entite_ref->posEnt.h < 0 || newPosEntY > height_window)
      return VALUE_ERROR;

    entite_aff->posEnt.x = newPosEntX;
    entite_aff->posEnt.y = newPosEntY;

    Charger_Anima(renderer, entite_aff, action);
    Print_Info_Entite(renderer, entite_aff);
  }

  return OK;
}

/**
 * \fn t_erreur Print_Entite_Screen (SDL_Renderer * renderer, t_entite * entite_ref, t_liste * entite_aff, t_action action, uint8_t pos)
 * \brief Affiche une liste d'entités sur l'écran avec ses informations (pv,mana,nom), soit au centre, soit en fonction d'une autre.
 * \param renderer Le renderer de la fenêtre.
 * \param entite_ref L'entité de référence si affichage en fonction d'elle.
 * \param entite_aff La liste d'entités à afficher.
 * \param action L'action effectuer pour effectuer le bon affichage.
 * \param pos La position de l'entité sur l'écran, permet de savoir si elle est au centre ou non.
 * \return Une erreur s'il y en a une.
*/
t_erreur Print_Liste_Entite_Screen (SDL_Renderer * renderer, t_entite * entite_ref, t_liste * entite_aff, t_action action, uint8_t pos)
{
  if (!entite_aff) return PTR_NULL;
  t_entite * entite;
  for (en_tete(entite_aff);!hors_liste(entite_aff);suivant(entite_aff))
  {
    valeur_elt(entite_aff,(void **)&entite);
    Print_Entite_Screen(renderer,entite_ref,entite,action,pos);
    //fprintf(stderr,"%d / ",entite->hitbox.y);
  }
  //fprintf(stderr,"\n");
  return OK;
}

/****** FONCTION SAVE ET LOAD ENTITE ******/

/**
 * \fn t_erreur Save_Entite (t_entite * entite,char * dossier, char * nom_fichier)
 * \brief Sauvegarde dans un fichier JSON une entité.
 * \brief Un fichier ne peut contenir qu'une seule entité.
 * \param entite L'entité à sauvegarder.
 * \param dossier Le dossier où enregistrer le fichier.
 * \param nom_fichier Le nom du fichier.
 * \return Une erreur s'il y en a une.
*/
t_erreur Save_Entite(t_entite *entite, char *dossier, char *nom_fichier) {
  if (!entite || !dossier || !nom_fichier)
    return PTR_NULL;

  FILE *fic = open_json(dossier, nom_fichier, "w");
  if (!fic)
    return OPEN_FILE_ERROR;

  // Save descriptif entité
  open_json_obj(fic);
  write_json(fic, "id", &(entite->id), "d");
  write_json(fic, "type", &(entite->type), "d");
  write_json(fic, "name", entite->name, "s");
  close_json_obj(fic);

  // Save stats entité
  open_json_obj(fic);
  write_json(fic, "xp", &(entite->xp), "u");
  write_json(fic, "mana", &(entite->mana), "u");
  write_json(fic, "mana_max", &(entite->mana_max), "u");
  write_json(fic, "pv", &(entite->pv), "u");
  write_json(fic, "pv_max", &(entite->pv_max), "u");
  write_json(fic, "faim", &(entite->faim), "u");
  write_json(fic, "faim_max", &(entite->faim_max), "u");
  close_json_obj(fic);

  // Save position entité
  open_json_obj(fic);
  write_json(fic, "hitboxX", &(entite->hitbox.x), "d");
  write_json(fic, "hitboxY", &(entite->hitbox.y), "d");
  write_json(fic, "hitboxW", &(entite->hitbox.w), "d");
  write_json(fic, "hitboxH", &(entite->hitbox.h), "d");
  close_json_obj(fic);

  fclose(fic);
  return OK;
}

/**
 * \fn t_entite * Load_Entite (char * dossier, char * nom_fichier)
 * \brief Charge une entité depuis un fichier.
 * \param dossier Le dossier où se trouve le fichier.
 * \param nom_fichier Le nom du fichier.
 * \return Un pointeur sur l'entité chargée.
*/
t_entite *Load_Entite(char *dossier, char *nom_fichier) {
  if (!dossier || !nom_fichier)
    return NULL;

  FILE *fic = open_json(dossier, nom_fichier, "r");
  if (!fic)
    return NULL;

  char *objet;

  // Récup descriptif entité
  int id;
  t_entite_type type;
  char name[100];
  extract_json_obj(fic, &objet);
  read_json_obj(objet, "id", &id, "d");
  read_json_obj(objet, "type", &type, "d");
  read_json_obj(objet, "name", name, "s");
  free(objet);

  // Récup stats entité
  uint64_t xp;
  uint32_t mana, pv, faim;
  uint32_t mana_max, pv_max, faim_max;
  extract_json_obj(fic, &objet);
  read_json_obj(objet, "xp", &xp, "u");
  read_json_obj(objet, "mana", &mana, "u");
  read_json_obj(objet, "mana_max", &mana_max, "u");
  read_json_obj(objet, "pv", &pv, "u");
  read_json_obj(objet, "pv_max", &pv_max, "u");
  read_json_obj(objet, "faim", &faim, "u");
  read_json_obj(objet, "faim_max", &faim_max, "u");
  free(objet);

  // Récup position entité
  SDL_Rect hitbox;
  extract_json_obj(fic, &objet);
  read_json_obj(objet, "hitboxX", &(hitbox.x), "d");
  read_json_obj(objet, "hitboxY", &(hitbox.y), "d");
  read_json_obj(objet, "hitboxW", &(hitbox.w), "d");
  read_json_obj(objet, "hitboxH", &(hitbox.h), "d");
  free(objet);

  // Création entité
  t_entite *entite = creer_entite_defaut(name, type, hitbox.x / width_block_sdl, hitbox.y / height_block_sdl, hitbox.h);
  Change_Name_Entite(entite, name);
  Change_Mana_Entite(entite, mana, mana_max);
  Change_Faim_Entite(entite, faim, faim_max);
  Change_PV_Entite(entite, pv, pv_max);
  Change_XP_Entite(entite, xp);

  return entite;
}
