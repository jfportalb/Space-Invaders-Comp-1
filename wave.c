#include <stdio.h>
#include "wave.h"

wave* create_wave(void) {

	struct wave* obj = (struct wave*) malloc(sizeof(struct wave));
	obj->x = 10; 
	obj->y = 10;

	//create squids row
	int i;
	int j;
	for(i = 0; i < N_ALIEN; i++) {
		obj->squids[i] = create_alien(obj->x + i*(ALIEN_WIDTH + ALIEN_SPACING), obj->y, SQUID);
	}
	//Create 2 jellyfish rows
	for(i = 0; i < 2; i++) {

		for(j = 0; j < N_ALIEN; j++) {
			obj->jellyfishes[i][j] = create_alien(obj->x + j*(ALIEN_WIDTH + ALIEN_SPACING), obj->y + (i + 1) * (ALIEN_WIDTH), JELLYFISH);
		}
	}
	//Create 2 crab rows
	for(i = 0; i < 2; i++) {

		for(j = 0; j < N_ALIEN; j++) {
			obj->crabs[i][j] = create_alien(obj->x + j*(ALIEN_WIDTH + ALIEN_SPACING), obj->y + (i + 3) * (ALIEN_WIDTH), CRAB);
		}
	}
	return obj;
}
void draw_wave(struct wave* obj) {

	int i;
	for(i = 0; i < N_ALIEN; i++) {
		
		if(obj->squids[i])
			draw_alien(obj->squids[i]);
		if(obj->jellyfishes[0][i])
			draw_alien(obj->jellyfishes[0][i]);
		if(obj->jellyfishes[1][i])
			draw_alien(obj->jellyfishes[1][i]);
		if(obj->crabs[0][i])
			draw_alien(obj->crabs[0][i]);
		if(obj->crabs[1][i])
			draw_alien(obj->crabs[1][i]);
	}
}
