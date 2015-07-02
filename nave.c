#include "nave.h"
#include <stdio.h>
#include <math.h>

//Variáveis de atraso em segundos
struct nave* cria_nave(int y, int min_atraso, int max_atraso, int velocidade) {

	struct nave* obj = (struct nave*) malloc(sizeof(struct nave));

	obj->imagem = al_load_bitmap("imagens/nave.png");
	obj->explosao = al_load_bitmap("imagens/explosao.png");

	obj->x = -1 * al_get_bitmap_width(obj->imagem);
	obj->y = y;

	obj->movimenta = false;
	obj->troca_sprite = false;

	obj->min_atraso = min_atraso;
	obj->max_atraso = max_atraso;

	obj->move_atraso = 60 * (min_atraso + (rand() % (min_atraso - max_atraso)));
	obj->velocidade = velocidade;
}

void move_nave(struct nave* obj) {

	if(obj->movimenta)
		obj->x += obj->velocidade;
}
void desenha_nave(struct nave* obj) {
	//puts("NAVE?");
	if(obj->troca_sprite)
		al_draw_bitmap(obj->explosao, obj->x, obj->y, 0);
	else
		al_draw_bitmap(obj->imagem, obj->x, obj->y, 0);
}
void processa_nave(struct nave* obj) {

	if(!(obj->move_atraso--)) {
		obj->movimenta = true;
	}
	else {
		if(obj->x >= 640 && obj->movimenta) {
			
			obj->movimenta = false;
			obj->move_atraso = 60 * (obj->min_atraso + (rand() % (obj->min_atraso - obj->max_atraso)));
			obj->velocidade *= -1;
		}
		if(obj->x <= (-1 * al_get_bitmap_width(obj->imagem)) && obj->movimenta) {

			obj->movimenta = false;
			obj->move_atraso = 60 * (obj->min_atraso + (rand() % (obj->min_atraso - obj->max_atraso)));
			obj->velocidade *= -1;
		}
	}
}
