#include "missil.h"
#include <stdio.h>

Missil* cria_missil(int posicao_x, int posicao_y, int vel_x, int vel_y){
	Missil* missil;
	missil = (Missil*) malloc(sizeof(Missil));
	missil->imagem = al_load_bitmap("imagens/missil.png");
	missil->pos_x = posicao_x - al_get_bitmap_width(missil->imagem)/2;
	missil->pos_y = posicao_y;
	missil->velocidade[0] = vel_x;
	missil->velocidade[1] = vel_y;
	missil->delta_x = al_get_bitmap_width(missil->imagem)/2;
	return missil;
}

void move_missil(Missil* missil){
	missil->pos_x += missil->velocidade[0];
	missil->pos_y += missil->velocidade[1];
}

void desenha_missil(Missil* missil){
	al_draw_bitmap(missil->imagem, missil->pos_x - missil->delta_x, missil->pos_y, 0);
}

Missil* destroi_missil(Missil* missil){
	free(missil);
	return NULL;
}

void processa_missil(Missil* missil){
	move_missil(missil);
}

int get_x_missil(Missil* missil){
	return missil->pos_x;
}
int get_y_missil(Missil* missil){
	return missil->pos_y;
}