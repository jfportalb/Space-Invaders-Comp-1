#include "menu.h"
#include <stdio.h>

#define ESCALA_TITULO 3

void inicializa_menu(Menu* menu, ALLEGRO_FONT* fonte, int largura_jogo, int altura_jogo, GAME_STATE menu_type) {
	
	menu->menu_type = menu_type;

    menu->altura_fonte = al_get_font_line_height(fonte);

    menu->botoes_y_offset = menu->altura_fonte + altura_jogo/24;

	switch(menu->menu_type){
		case PUSH_START:
			//Inicializa o Título
			menu->titulo = al_load_bitmap("imagens/title.png");
			menu->titulo_width = al_get_bitmap_width(menu->titulo);
			menu->titulo_height = al_get_bitmap_height(menu->titulo);
			if(!menu->titulo){
				fprintf(stderr, "%s\n", "Falha ao inicializar imagem de título.");
				exit(1);
			}
			menu->delta_x = menu->titulo_width*ESCALA_TITULO/2;
			menu->delta_y = menu->titulo_height*ESCALA_TITULO/2;
			menu->titulo_pos_x = largura_jogo/2 - menu->delta_x;
			menu->titulo_pos_y = menu->delta_y/2;

			//Inicializa Botoẽs
			
			menu->botoes_texto_start[0] = "PUSH START";

			menu->numero_botoes = N_BOTOES_PUSH_START;
			menu->botoes = (BOTAO*) malloc(sizeof(BOTAO) * menu->numero_botoes);

			for(int i = 0; i < N_BOTOES_PUSH_START; i++)
				inicializa_botao(&(menu->botoes[i]), largura_jogo, altura_jogo,
								 fonte, menu->altura_fonte, menu->botoes_texto_start[i], NORMAL);
			

			menu->botao_highlight = P_START;
			menu->botoes[0].botao_cor = HIGHLIGHT;

			break;
		case MENU_INICIAL:
			//Inicializa o Título
			menu->titulo = al_load_bitmap("imagens/title.png");
			menu->titulo_width = al_get_bitmap_width(menu->titulo);
			menu->titulo_height = al_get_bitmap_height(menu->titulo);
			if(!menu->titulo){
				fprintf(stderr, "%s\n", "Falha ao inicializar imagem de título.");
				exit(1);
			}
			menu->delta_x = menu->titulo_width*ESCALA_TITULO/2;
			menu->delta_y = menu->titulo_height*ESCALA_TITULO/2;
			menu->titulo_pos_x = largura_jogo/2 - menu->delta_x;
			menu->titulo_pos_y = menu->delta_y/2;

			//Inicializa Botoẽs
			menu->botoes_texto_inicial[0] = "PLAY";
			menu->botoes_texto_inicial[1] = "OPTIONS";
			menu->botoes_texto_inicial[2] = "EXIT";

			menu->numero_botoes = N_BOTOES_MENU_INICIAL;
			menu->botoes = (BOTAO*) malloc(sizeof(BOTAO) * menu->numero_botoes);

			for(int i = 0; i < N_BOTOES_MENU_INICIAL; i++)
				inicializa_botao(&(menu->botoes[i]), largura_jogo, altura_jogo,
								 fonte, menu->altura_fonte, menu->botoes_texto_inicial[i], NORMAL);

			menu->botao_highlight = PLAY;
			menu->botoes[0].botao_cor = HIGHLIGHT;

			break;
		case MENU_PAUSA:
			//Inicializa Botoẽs
			menu->botoes_texto_pausa[0] = "RESUME GAME";
			menu->botoes_texto_pausa[1] = "RESTART GAME";
			menu->botoes_texto_pausa[2] = "MAIN MENU";

			menu->numero_botoes = N_BOTOES_MENU_PAUSA;
			menu->botoes = (BOTAO*) malloc(sizeof(BOTAO) * menu->numero_botoes);

			for(int i = 0; i < N_BOTOES_MENU_PAUSA; i++)
				inicializa_botao(&(menu->botoes[i]), largura_jogo, altura_jogo,
								 fonte, menu->altura_fonte, menu->botoes_texto_pausa[i], NORMAL);

			menu->botao_highlight = RESUME_GAME;
			menu->botoes[0].botao_cor = HIGHLIGHT;

			break;
		case OPCOES:
			//Inicializa Botoẽs
			menu->botoes_texto_opcoes[0] = "BACK";

			menu->numero_botoes = N_BOTOES_OPCOES;
			menu->botoes = (BOTAO*) malloc(sizeof(BOTAO) * menu->numero_botoes);

			for(int i = 0; i < N_BOTOES_OPCOES; i++)
				inicializa_botao(&(menu->botoes[i]), largura_jogo, altura_jogo,
								 fonte, menu->altura_fonte, menu->botoes_texto_opcoes[i], NORMAL);

			menu->botao_highlight = BACK;
			menu->botoes[0].botao_cor = HIGHLIGHT;

			break;
	}

}

void desenha_menu(Menu* menu, ALLEGRO_FONT* fonte, bool titulo){
	al_clear_to_color(al_map_rgb(255, 255, 255));
	if (titulo)
		al_draw_scaled_bitmap(menu->titulo, 0, 0, menu->titulo_width, menu->titulo_height, menu->titulo_pos_x,
						  menu->titulo_pos_y, menu->titulo_width*ESCALA_TITULO, menu->titulo_height*ESCALA_TITULO, 0);

	
	for(int i = 0; i < menu->numero_botoes; i++)
		desenha_botao(&(menu->botoes[i]), fonte, menu->botoes[i].botao_pos_x, 
				  menu->botoes[i].botao_pos_y + i * menu->botoes_y_offset, menu->botoes[i].botao_cor);

	al_flip_display();
}

void menu_up(Menu* menu){

}

void menu_down(Menu* menu){
	if (menu->botao_highlight < menu->numero_botoes - 1){
								menu->botoes[menu->botao_highlight].botao_cor = NORMAL;
								menu->botao_highlight = (MYBUTTONS) (menu->botao_highlight + 1);
								menu->botoes[menu->botao_highlight].botao_cor = HIGHLIGHT;
							} else {
								menu->botoes[menu->botao_highlight].botao_cor = NORMAL;
								menu->botao_highlight = (MYBUTTONS) 0;
								menu->botoes[menu->botao_highlight].botao_cor = HIGHLIGHT;
							}
}

void menu_enter(Menu* menu){

}

void finaliza_menu(Menu* menu){
	//for(int i = 0; i < menu->numero_botoes; i++)
	//	finaliza_botao();

	free(menu->botoes);
}