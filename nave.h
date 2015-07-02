#ifndef NAVE_H
#define NAVE_H

#include <stdbool.h>
#include <allegro5/allegro.h>

struct nave{

	int x, y, move_atraso, min_atraso, max_atraso, velocidade;
	bool movimenta, troca_sprite;
	ALLEGRO_BITMAP* imagem;
	ALLEGRO_BITMAP* explosao;
};

struct nave* cria_nave(int y, int min_atraso, int max_atraso, int velocidade);

void move_nave(struct nave* obj);

void desenha_nave(struct nave* obj);

void processa_nave(struct nave* obj);

#endif
