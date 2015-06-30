#include "missil.h"
#include <stdio.h>

Missil* cria_missil(int posicao_x, int posicao_y, int vel_x, int vel_y){
	Missil* missil;
	missil = (Missil*) malloc(sizeof(Missil));
	missil->imagem = al_load_bitmap("imagens/missil.png");
	missil->ponta[0] = posicao_x - al_get_bitmap_width(missil->imagem)/2;
	missil->ponta[1] = posicao_y;
	missil->velocidade[0] = vel_x;
	missil->velocidade[1] = vel_y;
	missil->delta_x = al_get_bitmap_width(missil->imagem)/2;
	return missil;
}

void move_missil(Missil* missil){
	missil->ponta[0] += missil->velocidade[0];
	missil->ponta[1] += missil->velocidade[1];
}

void desenha_missil(Missil* missil){
	al_draw_bitmap(missil->imagem, missil->ponta[0] - missil->delta_x, missil->ponta[1], 0);
}

Missil* destroi_missil(Missil* missil){
	free(missil);
	missil = NULL;
	return missil;
}

void processa_missil(Missil* missil){
	move_missil(missil);
}

int* get_ponta_missil(Missil* missil){
	return missil ? missil->ponta : NULL;
}