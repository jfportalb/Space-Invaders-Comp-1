#ifndef MENU_H
#define MENU_H

#include "botao.h"
#include <allegro5/allegro_image.h>

#define BOTAO_NORMAL al_map_rgb(0, 0, 0)
#define BOTAO_SELECIONADO al_map_rgb(200, 0, 0)

struct Menu {
	ALLEGRO_BITMAP* buffer;

	int largura, altura;

	ALLEGRO_BITMAP* titulo;
	int titulo_pos_x, titulo_pos_y;
	int titulo_width, titulo_height;
	int delta_x, delta_y;
	
	ALLEGRO_FONT* fonte;

	Botao** botoes;
	int numero_botoes;
	int botao_selecionado;
	int botoes_y_offset;
	int *y_botoes, x_botoes;
};

Menu* inicializa_menu( ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo, int n_botoes, const char* titulo);

void cria_botao(Menu* menu, int pos_botao, const char texto[LETRAS_MAX_BOTAO], Funcao retorno, void* parametro_retorno);

void desenha_menu(Menu* menu, int largura, int altura, const char* texto);

void reinicia_menu(Menu* menu);

void menu_up(Menu* menu);

void menu_down(Menu* menu);

void menu_enter(Menu* menu);

Menu* finaliza_menu(Menu* menu);

#endif