#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "botao.h"

#define MAX_BOTOES 3
#define N_BOTOES_INICIAL 3
#define N_BOTOES_PAUSA 3
#define N_BOTOES_OPCOES 1

#define LETRAS_MAX_BOTAO 30

struct Menu {

	ALLEGRO_BITMAP* titulo = NULL;
	int titulo_pos_x, titulo_pos_y;
	int titulo_width, titulo_height;
	int delta_x, delta_y;

	int altura_fonte;

	GAME_STATE menu_type;

	BOTAO* botoes;
	MYBUTTONS botao_highlight;
	int numero_botoes;
	int botoes_y_offset;

	char botoes_texto[MAX_BOTOES][LETRAS_MAX_BOTAO];

};

void inicializa_menu_inicial(Menu* menu, ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo);

void inicializa_menu_pausa(Menu* menu, ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo);

void inicializa_menu_opcoes(Menu* menu, ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo);

void desenha_menu(Menu* menu, ALLEGRO_FONT* fonte, bool titulo);

void menu_up(Menu* menu);

void menu_down(Menu* menu);

void menu_enter(Menu* menu);

Menu* finaliza_menu(Menu* menu);


#endif