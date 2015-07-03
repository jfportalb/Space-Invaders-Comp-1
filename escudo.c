#include <allegro5/allegro.h>
#include <stdio.h>

#include "escudo.h"

Escudo* inicializa_escudo( int posicao_x, int posicao_y ) {
	Escudo* escudo = (Escudo*) malloc(sizeof(Escudo));
	escudo->posicao_x = posicao_x;
	escudo->posicao_y = posicao_y;
	escudo->topo_destruido = 0;
	
	for( int i = 0; i < PEDACOS_HORIZONTAL; i++ ) 
		for( int j = 0; j < PEDACOS_VERTICAL; j++ ) {
			escudo->pedaco[i][j] = 0;
			escudo->desenho[i][j] = QUADRADO;
		}
		 
	escudo->desenho[0][0] = SUDESTE;
	escudo->desenho[7][0] = SUDOESTE;
	escudo->desenho[2][2] = NOROESTE;
	escudo->desenho[5][2] = NORDESTE;
	escudo->pedaco[2][3] = DESTRUIDO;
	escudo->pedaco[3][3] = DESTRUIDO;
	escudo->pedaco[3][2] = DESTRUIDO;
	escudo->pedaco[4][3] = DESTRUIDO;
	escudo->pedaco[4][2] = DESTRUIDO;
	escudo->pedaco[5][3] = DESTRUIDO;

	escudo->imagem[0][0] = al_load_bitmap("imagens/quadrado-1.png");
	escudo->imagem[0][1] = al_load_bitmap("imagens/quadrado-2.png");
	escudo->imagem[1][0] = al_load_bitmap("imagens/sudeste-1.png");
	escudo->imagem[1][1] = al_load_bitmap("imagens/sudeste-2.png");
	escudo->imagem[2][0] = al_load_bitmap("imagens/noroeste-1.png");
	escudo->imagem[2][1] = al_load_bitmap("imagens/noroeste-2.png");
	escudo->imagem[3][0] = al_load_bitmap("imagens/nordeste-1.png");
	escudo->imagem[3][1] = al_load_bitmap("imagens/nordeste-2.png");
	escudo->imagem[4][0] = al_load_bitmap("imagens/sudoeste-1.png");
	escudo->imagem[4][1] = al_load_bitmap("imagens/sudoeste-2.png");

	for(int i=0; i<10; i++)
		if(!escudo->imagem[i%5][i/5]){
			escudo = finaliza_escudo(escudo);
			break;
		}

	return escudo;
}

void acerta_pedaco( Escudo* escudo, int pedaco_x, int pedaco_y){
	(escudo->pedaco[pedaco_x][pedaco_y]) ++;
}

bool colide_escudo(Escudo* escudo, Missil* missil){
	int x = get_x_missil(missil);
	int y = get_y_missil(missil);
	x-=escudo->posicao_x;
	y-=escudo->posicao_y;
	if( x >= 0 && y >= 0 && x < TAMANHO_PEDACO*PEDACOS_HORIZONTAL && y <=TAMANHO_PEDACO*PEDACOS_VERTICAL){
		int pedaco_x = x/TAMANHO_PEDACO;
		int pedaco_y = y/TAMANHO_PEDACO;
		if(escudo->pedaco[pedaco_x][pedaco_y] != DESTRUIDO){
			acerta_pedaco(escudo, pedaco_x, pedaco_y);
			return true;
		}
	}
	return false;
}

void desenha_pedaco_escudo( int x, int y, LegoEscudo lego, int estado, ALLEGRO_BITMAP* imagem[5][2]) {			 
	if( estado != DESTRUIDO)
		al_draw_bitmap(imagem[lego][estado], x, y, 0);
}
	
void desenha_escudo( Escudo* escudo ) {
	for( int i = 0, x = escudo->posicao_x; i < PEDACOS_HORIZONTAL; i++, x += TAMANHO_PEDACO )
		for( int j = 0, y = escudo->posicao_y; j < PEDACOS_VERTICAL; j++, y += TAMANHO_PEDACO )
			desenha_pedaco_escudo( x, y, escudo->desenho[i][j], escudo->pedaco[i][j], escudo->imagem);		 
}

Escudo* finaliza_escudo( Escudo *escudo ) {
	for(int i =0; i<5; i++)
		for(int j=0; j<2; j++){
			puts("ONE");
			al_destroy_bitmap(escudo->imagem[i][j]);
		}
	free(escudo);
	escudo = NULL;
	return escudo;
}

int get_top_escudo ( Escudo* escudo){
	return escudo->posicao_y + escudo->topo_destruido*TAMANHO_PEDACO;
}

void destroi_pedaco(Escudo* escudo, int pedaco_x, int pedaco_y){
	escudo->pedaco[pedaco_x][pedaco_y] = DESTRUIDO;
}
void destroi_topo_escudo (Escudo* escudo){
	for (int i=0; i< PEDACOS_HORIZONTAL; i++)
		destroi_pedaco(escudo, i, escudo->topo_destruido);
	escudo->topo_destruido++;
}