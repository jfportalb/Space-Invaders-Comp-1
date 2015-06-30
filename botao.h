#ifndef BOTAO_H
#define BOTAO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#define LETRAS_MAX_BOTAO 30

typedef void (*Funcao)( void*);

struct Botao {
	char texto[LETRAS_MAX_BOTAO];
	ALLEGRO_FONT* fonte;
	int pos_x, pos_y;

	Funcao retorno;
	void* parametro_retorno;
};

Botao* inicializa_botao( ALLEGRO_FONT *fonte, int meio_botao_pos_x, int topo_botao_pos_y, const char texto[LETRAS_MAX_BOTAO], Funcao retorno, void* parametro_retorno);

void desenha_botao(Botao* botao, ALLEGRO_COLOR cor);

void clica_botao(Botao* botao);

Botao* finaliza_botao(Botao* botao);

#endif