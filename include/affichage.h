

/* Fenetre */
int dansFenetre(SDL_Rect r);
SDL_Surface * TextureBlock(int id,block_type_t blocks[]);
void aff_map_sdl(SDL_Surface *screen,block_type_t blocks[],int min);

/* Terminale */
char * CouleurBlock(int id,block_type2_t blocks[]);
void aff_map(int min, int max,block_type2_t blocks[]);

