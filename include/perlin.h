/**
 *   \file perlin.h
 *   \brief Module perlin noise
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 13 mars 2019
 **/

#define FREQ 0.01   /* third parameter of perlin2d function */
#define DEPTH 5     /* fourth parameter of perlin2d function */


int noise2(int x, int y);
float lin_inter(float x, float y, float s);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);
float perlin2d(float x, float y, float freq, int depth);
