#include "tanque.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

Tanque* inicializa_tanque( int posicao_x, int posicao_y){
	Tanque* tanque = (Tanque*) malloc(sizeof(Tanque));
	tanque->posicao_x = posicao_x;
	tanque->posicao_y = posicao_y;
	tanque->velocidade = 0;

	tanque->imagem = al_load_bitmap("imagens/tanque.png");
	tanque->delta_x = al_get_bitmap_width(tanque->imagem)/2;
	tanque->missil = NULL;

	if(!tanque->imagem)
		tanque = NULL;

	return tanque;
}

void desenha_tanque(Tanque* tanque){
	al_draw_bitmap(tanque->imagem, tanque->posicao_x - tanque->delta_x, tanque->posicao_y, 0);
	if(tanque->missil)
		desenha_missil(tanque->missil);
}

void move_tanque(Tanque* tanque){
	tanque->posicao_x += tanque->velocidade;
}

void processa_tanque(Tanque* tanque){
	if(tanque->missil){
		processa_missil(tanque->missil);
	}
}
		
void tanque_move_esquerda(Tanque* tanque){
	tanque->posicao_x -= PASSO;
}

void tanque_move_direita(Tanque* tanque){
	tanque->posicao_x += PASSO;
}

void atira_tanque(Tanque* tanque){
	if(!tanque->missil)
		tanque->missil = cria_missil(tanque->posicao_x, tanque->posicao_y, 0, -10);
}

void destroi_missil_tanque(Tanque* tanque){
	tanque->missil = destroi_missil(tanque->missil);
}

int get_posicao_x_min_tanque (Tanque* tanque){
	return tanque->posicao_x - tanque->delta_x;
}

int get_posicao_x_max_tanque (Tanque* tanque){
	return tanque->posicao_x + tanque->delta_x;
}

Missil* get_missil_tanque(Tanque* tanque){
	return tanque->missil;
}

Tanque* destroi_tanque(Tanque* tanque){
	if(tanque->missil)
		tanque->missil = destroi_missil(tanque->missil);
	al_destroy_bitmap(tanque->imagem);
	free(tanque);
	tanque = NULL;
	return tanque;
}

ALLEGRO_BITMAP* get_imagem_tanque(Tanque* tanque){
	return tanque->imagem;
}