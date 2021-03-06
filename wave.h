#ifndef WAVE_H
#define WAVE_H
 
#include "alien.h"
#include "wave.h"
#include "sound.h"

#define MAX_MISSEIS 10

#define ALIEN_SPACING 10
 
struct wave {
	int n_aliens;
	int wave_width;

    struct alien** squids;
    struct alien** jellyfishes[2];
    struct alien** crabs[2];
    int aliens_mortos[5];
    int x, y, anima_contador, ritmo, velocidade;
    int linhas;

    SOUND_MANAGER *sound_mng;
    int sound_count;

    Missil* missil[MAX_MISSEIS];
    int missil_atual;
};
wave* create_wave(int y_inicial, int n_aliens, SOUND_MANAGER* sound_mng);
 
void draw_wave(struct wave* obj);
 
void processa_wave(struct wave* obj);

int colide_wave(struct wave* invasores, Missil* missil);

int get_bottom_wave(wave* obj);

Missil* get_missil_wave(wave* obj, int n_missil);

void destroi_missil_wave(wave* obj, int n_missil);

int get_linhas_wave(wave* obj);
 
wave* destroi_wave(wave* obj);

#endif