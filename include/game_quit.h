
Quit_Sprite();
menu_quit();
TTF_Quit();
BIOME_Quit();
SDL_exit_touches(&ks, &ct);
BLOCK_DestroyTexture_sdl(renderer);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(screen);
SDL_Quit();
pwd_quit();
