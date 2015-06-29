#include "botao.h"
#include <stdio.h>

void inicializa_botao(BOTAO* botao,int largura_jogo, int altura_jogo, 
					  ALLEGRO_FONT *fonte, int altura_fonte, char* texto, COLOR botao_cor) {
	botao->texto = texto;
	botao->clique = false;

	botao->botao_cor = botao_cor;

	botao->normal_color = al_map_rgb(63, 63, 63);
	botao->highlight_color = al_map_rgb(0, 0, 0);

	botao->botao_width = al_get_text_width(fonte, texto);
	botao->botao_height = altura_fonte;

	int delta_x = botao->botao_width/2;
	int delta_y = botao->botao_height/2;

	botao->botao_pos_x = largura_jogo/2 - delta_x;
	botao->botao_pos_y = altura_jogo/2 + delta_y;
}

void desenha_botao(BOTAO* botao, ALLEGRO_FONT* fonte, int botao_pos_x, int botao_pos_y, COLOR botao_cor){
	if(botao_cor == NORMAL)
		al_draw_text(fonte, botao->normal_color, botao_pos_x, botao_pos_y, 0, botao->texto);
	if(botao_cor == HIGHLIGHT)
		al_draw_text(fonte, botao->highlight_color, botao_pos_x, botao_pos_y, 0, botao->texto);
}

void clica_botao(MYBUTTONS botao, GAME_STATE* game_state, GAME_STATE game_state_anterior){
	switch(*game_state){
		case PUSH_START:
			switch (botao){
				case P_START:
					*game_state = MENU_INICIAL;
					break;
			}
			break;
		case MENU_INICIAL:
			switch (botao){
				case PLAY:
					*game_state = PLAY_GAME;
					break;
				case OPTIONS:
					*game_state = OPCOES;
					break;
				case EXIT:
					*game_state = GAME_OVER;
					break;
			}
			break;
		case OPCOES:
			switch(botao){
				case BACK:
					*game_state = game_state_anterior;
					break;
			}
			break;
		case MENU_PAUSA:
			switch(botao){
				case RESUME_GAME:
					*game_state = PLAY_GAME;
					break;
				//case RESTART_GAME:
					//	inicializa_jogo();
					//*game_state = PLAY_GAME;
					//break;
				case MAIN_MENU:
					*game_state = MENU_INICIAL;
					break;
			}
			break;
	}
}

/*void finaliza_botao(BOTAO* botao){

}*/