#include "missil.h"
#include <stdio.h>

Missil* cria_missil(int posicao_x, int posicao_y){
	Missil* missil;
	missil = (Missil*) malloc(sizeof(Missil));
	missil->imagem = al_load_bitmap("imagens/missil.png");
	missil->posicao_x = posicao_x - al_get_bitmap_width(missil->imagem)/2;
	missil->posicao_y = posicao_y;
	missil->velocidade[0] = 0;
	missil->velocidade[1] = 5;
	return missil;
}

void move_missil(Missil* missil){
	missil->posicao_y -= missil->velocidade[1];
}

void desenha_missil(Missil* missil){
	al_draw_bitmap(missil->imagem, missil->posicao_x, missil->posicao_y, 0);
}

Missil* destroi_missil(Missil* missil){
	free(missil);
	missil = NULL;
	return missil;
}

void processa_missil(Missil* missil){
	move_missil(missil);
}