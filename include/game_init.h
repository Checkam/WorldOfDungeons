SDL_Init(SDL_INIT_EVERYTHING);
TTF_Init();
IMG_Init(IMG_INIT_PNG);

SDL_Window *screen =
    SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window, SDL_WINDOW_SHOWN);

//SDL_GetWindowSize(screen, &width_window, &height_window);
SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);


BIOME_init();
Init_Sprite(renderer);
BLOCK_CreateTexture_sdl(renderer);
menu_init(renderer);
fps_init();
SDL_init_touches(&ks, &ct);
init_item(renderer);
