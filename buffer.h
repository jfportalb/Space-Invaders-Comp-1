#ifndef BUFFER_H
#define BUFFER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "escudo.h"
#include "tanque.h"

#define N_ESCUDOS 7


struct Buffer{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* buffer;
	ALLEGRO_FONT* fonte;

	int largura_inicial, altura_inicial;
	int* vidas, *score;

	Escudo** escudo;
	Tanque* tanque;
};

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, ALLEGRO_FONT* fonte, int largura, int altura, Escudo* escudo[], Tanque *tanque, int* vidas, int* score);

void processa_buffer(Buffer* buffer);

void desenha_buffer(Buffer* buffer, int largura, int altura);

Buffer* destroi_buffer(Buffer* buffer);

#endif