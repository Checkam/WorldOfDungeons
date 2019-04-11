MAP_sauvegarder(map);
Quit_Sprite();
menu_quit();
TTF_Quit();
BIOME_Quit();
MAP_detruction(&map);
SDL_exit_touches(&ks, &ct);
BLOCK_DestroyTexture_sdl(renderer);
SDL_DestroyTexture(fond);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(screen);
SDL_Quit();
pwd_quit();

free_inventaire(inventaire);
detruire_liste(liste, free);
free(liste);
