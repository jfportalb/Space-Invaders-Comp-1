#include "tanque.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

Tanque* inicializa_tanque( int posicao_x, int posicao_y, SOUND_MANAGER* sound_mng){
	Tanque* tanque = (Tanque*) malloc(sizeof(Tanque));
	tanque->posicao_x_inicial = posicao_x;
	tanque->posicao_y_inicial = posicao_y;

	tanque->sound_mng = sound_mng;

	tanque->imagem = al_load_bitmap("imagens/tanque.png");
	tanque->delta_x = al_get_bitmap_width(tanque->imagem)/2;

	if(!tanque->imagem)
		tanque = NULL;

	tanque->altura = al_get_bitmap_height(tanque->imagem);

	tanque->missil = NULL;
	reinicia_tanque(tanque);

	return tanque;
}

void reinicia_tanque(Tanque* tanque){
	tanque->posicao_x = tanque->posicao_x_inicial;
	tanque->posicao_y = tanque->posicao_y_inicial;
}

void desenha_tanque(Tanque* tanque){
	al_draw_bitmap(tanque->imagem, tanque->posicao_x - tanque->delta_x, tanque->posicao_y, 0);
	if(tanque->missil)
		desenha_missil(tanque->missil);
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
	if(!tanque->missil){
		play_sound(tanque->sound_mng, SHOOT);
		tanque->missil = cria_missil(tanque->posicao_x, tanque->posicao_y, 0, -VEL_MISSIL);
	}
}

void destroi_missil_tanque(Tanque* tanque){
	tanque->missil = destroi_missil(tanque->missil);
}

bool colide_tanque(Tanque* tanque, Missil* missil){
	int x = get_x_missil(missil);
	int y = get_y_missil(missil);
	x-=tanque->posicao_x - tanque->delta_x;
	y-=tanque->posicao_y;
	if( y >= 0 && y <= tanque->altura && x < tanque->delta_x*2 && x >= 0){
		return true;
	}
	return false;
}

int get_posicao_x_min_tanque (Tanque* tanque){
	return tanque->posicao_x - tanque->delta_x;
}

int get_posicao_x_max_tanque (Tanque* tanque){
	return tanque->posicao_x + tanque->delta_x;
}

int get_top_tanque ( Tanque* tanque ){
	return tanque->posicao_y;
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