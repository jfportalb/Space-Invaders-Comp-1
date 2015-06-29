#ifndef BOTAO_H
#define BOTAO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

enum GAME_STATE {
	MENU_INICIAL, PLAY_GAME, MENU_PAUSA, GAME_OVER, OPCOES, PUSH_START
};

enum MYBUTTONS {
	// Botões de PUSH_START 
	P_START = 0, 
	// Botões de MENU_INICIAL
	PLAY = 0, OPTIONS, EXIT,
	// Botões de MENU_PAUSA 
	RESUME_GAME = 0, RESTART_GAME, MAIN_MENU, 
	// Botões de OPCOES
	BACK = 0
};

enum COLOR {
	NORMAL, HIGHLIGHT
};

enum BOTAO_TIPO{
	COMUM, CHECK_BOX, RADIO_BUTTON, SLIDE, DROPDOWN
};

struct BOTAO {
	char* texto;
	bool clique;
	COLOR botao_cor;
	ALLEGRO_COLOR normal_color, highlight_color;
	int botao_pos_x, botao_pos_y;
	int botao_width, botao_height;
	
};

void inicializa_botao(BOTAO* botao,int largura_jogo, int altura_jogo, 
					  ALLEGRO_FONT *fonte, int altura_fonte, char* texto, COLOR botao_cor);

void desenha_botao(BOTAO* botao, ALLEGRO_FONT* fonte, int botao_pos_x, int botao_pos_y, COLOR botao_cor);

void clica_botao(MYBUTTONS botao, GAME_STATE* game_state, GAME_STATE game_state_anterior);

//void finaliza_botao(BOTAO* botao);

#endif