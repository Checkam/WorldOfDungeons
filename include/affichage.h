

/* Fenetre */
int dansFenetre(SDL_Rect r);
SDL_Surface * TextureBlock(int id,void *);
void aff_map_sdl(SDL_Surface *screen,void *,int min);
int taille_mid_aff();

/* Terminale */
char * CouleurBlock(int id, void *);
void aff_map(int min, int max, void *);
