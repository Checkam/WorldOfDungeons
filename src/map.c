/**
 *   \file map.c
 *   \brief Module permettant de géré une map (Création,Suppression)
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 07 mars 2019
 **/

#ifndef __MAP_H__
#define __MAP_H__
#include <erreur.h>
#endif

#include <map.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

/**
    \fn t_erreur MAP_creer(t_map ** map, char * nom_map, int SEED)
    \brief Créer une map (le dossier de saugarde et le pointeur pour manipuler
cette map) \param map le pointeur de la map qui va être créer \param nom_map Le
nom de la map \param SEED Le SEED de génération de la map \return Renvoie un
code erreur en cas de problème sinon OK
**/
t_erreur MAP_creer(t_map **map, char *nom_map, int SEED) {

  (*map) = malloc(sizeof(t_map));
  (*map)->nom = malloc(sizeof(char) * strlen(nom_map) + 1);

  strcpy((*map)->nom, nom_map);
  (*map)->SEED = SEED;

  MAP_creer_dir(*map);

  MAP_sauvegarder(*map);

  return OK;
}

/**
    \fn t_erreur MAP_charger(t_map ** map, char * nom_map)
    \brief Charge la map a partir des fichier
    \param map Pointeur sur la map qui doit etre sauvegarder
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_charger(t_map **map, char *nom_map) {
  char *path_dir = MAP_creer_path(nom_map);
  int size = 500;
  char *dir_curr = malloc(sizeof(char) * size + 1);
  getcwd(dir_curr, size);
  if (chdir(path_dir))
    return FILE_ERROR; // DIR_NO_FOUND
  chdir(dir_curr);
  free(dir_curr);
  MAP_detruire_path(&path_dir); // Gestion des erreurs a faire

  (*map) = malloc(sizeof(t_map));
  (*map)->nom = malloc(sizeof(char) * strlen(nom_map) + 1);
  strcpy((*map)->nom, nom_map);
  // Charger le seed avec fct json

  return OK;
}

/**
    \fn t_erreur MAP_sauvegarder(t_map * map)
    \brief Sauvegarde la map dans l'état actuel
    \param map Pointeur sur la map qui doit etre sauvegarder
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_lister() { return OK; }

/**
    \fn t_erreur MAP_sauvegarder(t_map * map)
    \brief Sauvegarde la map dans l'état actuel
    \param map Pointeur sur la map qui doit etre sauvegarder
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_sauvegarder(t_map *map) {
  if (map == NULL)
    return PTR_NULL;

  char *path_dir = MAP_creer_path(map->nom);

  // A finir avec le systeme de JSON est de path pas encore disponible
  // Sauvegarde de ou est le joueurs pour preload la map a afficher

  MAP_detruire_path(&path_dir); // Gestion des erreurs a faire

  return OK;
}

/**
    \fn t_erreur MAP_creer_dir(t_map * map)
    \brief Créer le repertoire d'une map
    \param map Pointeur sur la map dont le repertoire doit être créer
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_creer_dir(t_map *map) {
  if (map == NULL)
    return PTR_NULL;
  t_erreur erreur;
  char *path_dir = MAP_creer_path(map->nom);

  if (mkdir(path_dir, 755))
    return FILE_ERROR; // MKDIR_ERROR

  erreur = MAP_detruire_path(&path_dir);
  if (erreur != OK)
    return erreur;

  return OK;
}

/**
    \fn t_erreur MAP_supprimer_dir(t_map * map)
    \brief Supprimer le repertoire d'une map
    \param map Pointeur sur la map dont le repertoire doit être supprimer
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_supprimer(t_map *map) {
  if (map == NULL)
    return PTR_NULL;

  char *path_dir = MAP_creer_path(map->nom);

  rmdir(path_dir);

  MAP_detruire_path(&path_dir);

  return OK;
}

/**
    \fn t_erreur MAP_supprimer(t_map ** map)
    \brief Supprime un pointeur t_map
    \param map Pointeur de pointeur de t_map à supprimer et mettre a NULL
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_detruction(t_map **map) {
  if (map == NULL)
    return PTR_NULL;

  if ((*map)->nom != NULL) {
    free((*map)->nom);
    (*map)->nom = NULL;
  }
  free(*map);
  map = NULL;
  return OK;
}

/**
    \fn char * MAP_path(t_map * map)
    \brief Créer le path d'une map
    \param map Pointeur de t_map
    \return Renvoie le path de la map
**/
char *MAP_creer_path(char *nom_map) {
  char *path_dir = malloc(sizeof(char) * strlen(nom_map) +
                          sizeof(char) * strlen(PATH_MAP_DIR));
  strcpy(path_dir, PATH_MAP_DIR);
  strcat(path_dir, nom_map);
  return path_dir;
}

/**
    \fn t_erreur MAP_detruire_path(char ** path_dir)
    \brief Libère la mémoire dynamique alloué pour le path
    \param map Pointeur de pointeur sur le path
    \return Renvoie un code erreur en cas de problème sinon OK
**/
t_erreur MAP_detruire_path(char **path_dir) {
  if (*path_dir == NULL)
    return PTR_NULL;

  free(*path_dir);
  path_dir = NULL;
  return OK;
}
