#ifndef WAVE_H
#define WAVE_H

#include "alien.h"

#define N_ALIEN 11
#define ALIEN_SPACING 10

struct wave {

	struct alien* squids[N_ALIEN];
	struct alien* jellyfishes[2][N_ALIEN];
	struct alien* crabs[2][N_ALIEN];
	int x, y;
};
wave* create_wave(void);

void move_wave_left(struct wave* obj);

void move_wave_right(struct wave* obj);

void anima_wave(struct wave* obj);

void draw_wave(struct wave* obj);

#endif
