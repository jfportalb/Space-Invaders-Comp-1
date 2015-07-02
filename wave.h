#ifndef WAVE_H
#define WAVE_H
 
#include "alien.h"
#include "wave.h"
#include "missil.h"

#define ALIEN_SPACING 10
 
struct wave {
	int n_aliens;
	int wave_width;

    struct alien** squids;
    struct alien** jellyfishes[2];
    struct alien** crabs[2];
    int x, y, anima_contador, ritmo, velocidade;
    int linhas;
};
wave* create_wave(int y_inicial, int n_aliens);
 
void draw_wave(struct wave* obj);
 
void processa_wave(struct wave* obj);
 
#endif