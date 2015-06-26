#ifndef BUFFER_H
#define BUFFER_H

#include <allegro5/allegro.h>
#include "escudo.h"
#include "tanque.h"

struct Buffer{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* buffer;

	Escudo** escudo;
	Tanque* tanque;
};

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, int largura, int altura, Escudo* escudo[], Tanque *tanque);

void processa_buffer(Buffer* buffer);

void desenha_buffer(Buffer* buffer, int largura, int altura);

Buffer* destroi_buffer(Buffer* buffer);

#endif