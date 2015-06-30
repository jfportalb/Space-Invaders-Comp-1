#ifndef MISSIL_H
#define MISSIL_H

#include <allegro5/allegro.h>

struct Missil{
	int ponta[2];
	ALLEGRO_BITMAP* imagem;
	float velocidade[2];
	int delta_x;
};

Missil* cria_missil(int posicao_x, int posicao_y, int vel_x, int vel_y);

void processa_missil(Missil* missil);

void desenha_missil(Missil* missil);

Missil* destroi_missil(Missil* missil);

int* get_ponta_missil(Missil* missil);

#endif