#include "botao.h"

Botao* inicializa_botao( ALLEGRO_FONT *fonte, int meio_botao_pos_x, int topo_botao_pos_y, const char texto[LETRAS_MAX_BOTAO], Funcao retorno, void* parametro_retorno){
	Botao* botao = (Botao*) malloc(sizeof(Botao));
	strcpy(botao->texto, texto);
	botao->fonte = fonte;

	int delta_x = al_get_text_width(botao->fonte, texto)/2;
	botao->pos_x = meio_botao_pos_x - delta_x;
	botao->pos_y = topo_botao_pos_y;

	botao->retorno = retorno;
	botao->parametro_retorno = parametro_retorno;
	return botao;
}

void desenha_botao(Botao* botao, ALLEGRO_COLOR cor){
	al_draw_text(botao->fonte, cor, botao->pos_x, botao->pos_y, 0, botao->texto);
}

void clica_botao(Botao* botao){
	botao->retorno(botao->parametro_retorno);
}

Botao* finaliza_botao(Botao* botao){
	if(botao) free(botao);
	return NULL;
}