t_biome *b = BIOME_CreateBiome(FORET);
BIOME_AddLayer(b, HERBE, 1);
BIOME_AddLayer(b, TERRE, 4);
BIOME_AddLayer(b, ROCHE, MAX);

b = BIOME_CreateBiome(PRAIRIES);
BIOME_AddLayer(b, HERBE, 1);
BIOME_AddLayer(b, TERRE, 4);
BIOME_AddLayer(b, ROCHE, MAX);

b = BIOME_CreateBiome(TAIGA);
BIOME_AddLayer(b, NEIGE, 1);
BIOME_AddLayer(b, TERRE, 4);
BIOME_AddLayer(b, ROCHE, MAX);

b = BIOME_CreateBiome(TOUNDRA);
BIOME_AddLayer(b, NEIGE, 1);
BIOME_AddLayer(b, TERRE, 4);
BIOME_AddLayer(b, ROCHE, MAX);

b = BIOME_CreateBiome(DESERTS);
BIOME_AddLayer(b, SABLE, 1);
BIOME_AddLayer(b, TERRE, 4);
BIOME_AddLayer(b, ROCHE, MAX);
