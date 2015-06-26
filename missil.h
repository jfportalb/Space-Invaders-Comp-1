#ifndef MISSIL_H
#define MISSIL_H

#include <allegro5/allegro.h>

struct Missil{
	int posicao_x, posicao_y;
	ALLEGRO_BITMAP* imagem;
	float velocidade[2];
};

Missil* cria_missil(int posicao_x, int posicao_y);

void processa_missil(Missil* missil);

void desenha_missil(Missil* missil);

Missil* destroi_missil(Missil* missil);

#endif