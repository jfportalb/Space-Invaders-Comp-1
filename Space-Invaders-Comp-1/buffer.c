#include "buffer.h"

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, int largura, int altura, Escudo* escudo[], Tanque *tanque){
	Buffer* buffer = (Buffer*) malloc (sizeof(Buffer));

	buffer->display = display;
	buffer->buffer = al_create_bitmap(largura, altura);

	buffer->escudo = escudo;
	buffer->tanque = tanque;

	return buffer;
}

void processa_buffer(Buffer* buffer){
	processa_tanque(buffer->tanque);
	// processa_horda(buffer->horda);
}

void desenha_buffer(Buffer* buffer, int altura, int largura){
	al_set_target_bitmap(buffer->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for( int i = 0; i < 4; i++ )
		desenha_escudo( buffer->escudo[i] );

	desenha_tanque(buffer->tanque);

	al_flip_display();
	al_set_target_backbuffer(buffer->display);
	al_draw_bitmap(buffer->buffer, 0, 0, 0);	
}

Buffer* destroi_buffer(Buffer* buffer){
	free(buffer);
	return buffer;
}