#ifndef ALIEN_H
#define ALIEN_H

#define ALIEN_SPEED 10
#define ALIEN_WIDTH 36

#include <allegro5/allegro.h>

enum ALIEN_TYPE {
	SQUID, JELLYFISH, CRAB
};
struct alien{
	int troca_sprite;
	int x, y;
	ALIEN_TYPE alien_type;
	int alien_rhythm;            //Define o intervalo de tempo entre movimentos
	ALLEGRO_BITMAP* imagem_1;
	ALLEGRO_BITMAP* imagem_2;
};

alien* create_alien(int x, int y, ALIEN_TYPE type);

void destroy_alien(struct alien* obj);

void explode_alien(struct alien* obj);

void move_alien_left(struct alien* obj);

void move_alien_right(struct alien* obj);

void move_alien_down(struct alien* obj);

void draw_alien(struct alien* obj);

void anima_alien(struct alien* obj);

#endif
