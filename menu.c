# include "menu.h"
# define ESCALA_TITULO 3

void inicializa_titulo(Menu * menu, int largura_jogo) {
	menu->titulo = al_load_bitmap("imagens/title.png");
	menu->titulo_width = al_get_bitmap_width(menu->titulo);
	menu->titulo_height = al_get_bitmap_height(menu->titulo);
	if (!menu->titulo) {
		fprintf(stderr, "%s\n", "Falha ao inicializar imagem de título.");
		exit(1);
	}
	menu->delta_x = menu->titulo_width*ESCALA_TITULO/2;
	menu->delta_y = menu->titulo_height*ESCALA_TITULO/2;
	menu->titulo_pos_x = largura_jogo/2 - menu->delta_x;
	menu->titulo_pos_y = menu->delta_y/2;
}

Menu * inicializa_menu(ALLEGRO_FONT * fonte, int largura_jogo, int altura_jogo, int n_botoes, bool titulo) {
	Menu * menu = (Menu * ) malloc(sizeof(Menu));
	
	menu->largura = largura_jogo;
	menu->altura = altura_jogo;
	menu->buffer = al_create_bitmap(largura_jogo, altura_jogo);

	menu->numero_botoes = n_botoes;
	
	menu->botoes = (Botao * * ) malloc(sizeof(Botao * ) * n_botoes);
	menu->botao_selecionado = 0;
	
	menu->fonte = fonte;
	menu->x_botoes = largura_jogo / 2;
	
	int botoes_y_offset = al_get_font_line_height(fonte) + altura_jogo / 24;
	menu->y_botoes = (int * ) malloc(sizeof(int) * n_botoes);
	
	if (titulo) {
		inicializa_titulo(menu, largura_jogo);
		for (int i = 0; i < menu->numero_botoes; i++)
			menu->y_botoes[i] = altura_jogo / 2 + 20 +  botoes_y_offset * i;
	}
	else {
		for (int i = 0; i < menu->numero_botoes; i++)
			menu->y_botoes[i] = altura_jogo / 2 + botoes_y_offset * i;
		menu->titulo = NULL;
	}

	return menu;
}

void cria_botao(Menu * menu, int pos_botao,
	const char texto[LETRAS_MAX_BOTAO], Funcao retorno, void * parametro_retorno) {
	menu->botoes[pos_botao] = inicializa_botao(menu->fonte, menu->x_botoes, menu->y_botoes[pos_botao], texto, retorno, parametro_retorno);
}

void desenha_menu(Menu * menu, int largura, int altura) {
	al_set_target_bitmap(menu->buffer);

	al_clear_to_color(al_map_rgb(250, 250, 250));
	if (menu->titulo){
		al_draw_scaled_bitmap(menu->titulo, 0, 0, menu->titulo_width, menu->titulo_height, menu->titulo_pos_x,
						  menu->titulo_pos_y, menu->titulo_width*ESCALA_TITULO, menu->titulo_height*ESCALA_TITULO, 0);
	}
	for (int i = 0; i < menu->numero_botoes; i++)
		if (i == menu->botao_selecionado)
			desenha_botao(menu->botoes[i], BOTAO_SELECIONADO);
		else
			desenha_botao(menu->botoes[i], BOTAO_NORMAL);
	

	al_set_target_backbuffer(al_get_current_display());
	al_draw_scaled_bitmap(menu->buffer, 0, 0, menu->largura, menu->altura , 0, 0, largura, altura, 0);	

	al_flip_display();
}
void menu_up(Menu * menu) {
	menu->botao_selecionado = (menu->botao_selecionado + menu->numero_botoes - 1) % menu->numero_botoes;
}
void menu_down(Menu * menu) {
	menu->botao_selecionado = (menu->botao_selecionado + 1) % menu->numero_botoes;
}
void menu_enter(Menu * menu) {
	clica_botao(menu->botoes[menu->botao_selecionado]);
}
Menu * finaliza_menu(Menu * menu) {
	for (int i = 0; i < menu->numero_botoes; i++) menu->botoes[i] = finaliza_botao(menu->botoes[i]);
	free(menu);
	return NULL;
}