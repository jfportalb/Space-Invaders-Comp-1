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

	if(obj && obj->movimenta)
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
	if (obj){
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
}

bool colide_nave(struct nave* obj, Missil* missil){
	if (obj){
		int x = get_x_missil(missil);
		int y = get_y_missil(missil);
		if(y >= obj->y && y <= obj->y + al_get_bitmap_height(obj->imagem) && x > obj->x && x < obj->x + al_get_bitmap_width(obj->imagem)){
			obj = destroi_nave(obj);
			return true;
		}
		else
			return false;
	}
}

nave* destroi_nave(struct nave* obj){
	al_destroy_bitmap(obj->imagem);
	al_destroy_bitmap(obj->explosao);
	free(obj);
	return NULL;
}