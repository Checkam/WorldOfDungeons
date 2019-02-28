#include <SDL2/SDL.h>
#define NB_BLOCK 10


typedef enum {
	AIR,
	HERBE,
	TERRE,
	EAU,
	SABLE,
	FEUILLE,
	BOIS,
	ROCHE,
	NEIGE,
	GLACE,
	DIAMAND
} materiaux_t;

typedef struct block_type_s{
    materiaux_t materiau;
    char * nom;
	//int resistance;
	SDL_Surface * texture;
}block_type_t;

typedef struct block_type2_s{
    materiaux_t materiau;
    char * nom;
	//int resistance;
	char * texture;
}block_type2_t;

typedef struct block_s{
    int id,x,y;
}block_t;
