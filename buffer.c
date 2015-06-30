#include "buffer.h"
#include <stdio.h>

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, ALLEGRO_FONT* fonte, int largura, int altura, Escudo* escudo[], Tanque *tanque, int* vidas, int* score){
	Buffer* buffer = (Buffer*) malloc (sizeof(Buffer));

	buffer->vidas = vidas;
	buffer->score = score;
	buffer->largura_inicial = largura;
	buffer->altura_inicial = altura;

	buffer->display = display;
	buffer->fonte = fonte;
	buffer->buffer = al_create_bitmap(largura, altura);

	buffer->escudo = escudo;
	buffer->tanque = tanque;

	return buffer;
}

void processa_buffer(Buffer* buffer){
	processa_tanque(buffer->tanque);
	// processa_horda(buffer->horda);
}

void desenha_buffer(Buffer* buffer, int largura, int altura){
	al_set_target_bitmap(buffer->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for( int i = 0; i < 4; i++ )
		desenha_escudo( buffer->escudo[i] );

	desenha_tanque(buffer->tanque);
	char strScore[100];
	sprintf(strScore, "SCORE: %d", *(buffer->score));
	al_draw_text(buffer->fonte, al_map_rgb(255,255,255), 0, 10, 0, strScore );
	al_draw_text(buffer->fonte, al_map_rgb(255,255,255), buffer->largura_inicial/4*3, 10, ALLEGRO_ALIGN_RIGHT, "VIDAS");
	for(int i=0; i< *(buffer->vidas); i++)
		al_draw_bitmap(get_imagem_tanque(buffer->tanque),10+ buffer->largura_inicial/4*3 + i*(al_get_bitmap_width(get_imagem_tanque(buffer->tanque))+10), 5, 0);


	al_flip_display();
	al_set_target_backbuffer(buffer->display);
	al_draw_scaled_bitmap(buffer->buffer, 0, 0, buffer->largura_inicial, buffer->altura_inicial, 0, 0, largura, altura, 0);	
}

Buffer* destroi_buffer(Buffer* buffer){
	free(buffer);
	return buffer;
}