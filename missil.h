#ifndef MISSIL_H
#define MISSIL_H

#include <allegro5/allegro.h>

#define VEL_MISSIL 6

struct Missil{
	int pos_x, pos_y;
	ALLEGRO_BITMAP* imagem;
	float velocidade[2];
	int delta_x;
};

Missil* cria_missil(int posicao_x, int posicao_y, int vel_x, int vel_y);

void processa_missil(Missil* missil);

void desenha_missil(Missil* missil);

Missil* destroi_missil(Missil* missil);

int get_y_missil(Missil* missil);

int get_x_missil(Missil* missil);

#endif