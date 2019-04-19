#ifndef __FPS_H__
#define __FPS_H__

#define FPS 50 /* fps affichée a l'ecran */

#define FPS_BASE 50 /* a ne pas changer, point de repere pour le module*/

/* initialise le module fps */
void fps_init ();

/* permet de limiter le defilement de l'image. Renvoie un double corespondant a un multiplicateur ( de base 1, mais si l'ordinateur est trop lent et n'afficha pas toutes les images, cette valeur augmentera ). Sans cette fonction, les ordinateurs les plus puissants auront le jeu plus rapide, a l'inverse les ordinateurs les moins puissant auront un jeu ralentit */
double fps ();

#endif