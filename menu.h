#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "botao.h"

#define N_BOTOES_PUSH_START 1
#define N_BOTOES_MENU_INICIAL 3
#define N_BOTOES_MENU_PAUSA 3
#define N_BOTOES_OPCOES 1

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

	char* botoes_texto_start[N_BOTOES_PUSH_START];
    char* botoes_texto_inicial[N_BOTOES_MENU_INICIAL];
    char* botoes_texto_pausa[N_BOTOES_MENU_PAUSA];
    char* botoes_texto_opcoes[N_BOTOES_OPCOES];

};

void inicializa_menu(Menu* menu, ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo, GAME_STATE menu_type);

void desenha_menu(Menu* menu, ALLEGRO_FONT* fonte, bool titulo);

void menu_up(Menu* menu);

void menu_down(Menu* menu);

void menu_enter(Menu* menu);

void finaliza_menu(Menu* menu);


#endif