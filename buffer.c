#include "buffer.h"
#include <stdio.h>

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, ALLEGRO_FONT* fonte, int largura, int altura, Escudo* escudo[], int n_escudos, Tanque *tanque, wave* invasores, nave* ovni, int* vidas, int* score){
	Buffer* buffer = (Buffer*) malloc (sizeof(Buffer));

	buffer->vidas = vidas;
	buffer->score = score;
	buffer->largura_inicial = largura;
	buffer->altura_inicial = altura;

	buffer->display = display;
	buffer->fonte = fonte;
	buffer->buffer = al_create_bitmap(largura, altura);

	buffer->escudo = escudo;
	buffer->n_escudos = n_escudos;
	buffer->tanque = tanque;
	buffer->invasores = invasores;
	buffer->ovni = ovni;

	return buffer;
}

void processa_colisao(Buffer* buffer){
	Missil* missil = get_missil_tanque(buffer->tanque);
	if (missil)
		if( get_y_missil(missil) < 0)
			destroi_missil_tanque(buffer->tanque);
		else {
		if(get_y_missil(missil) <= get_bottom_wave(buffer->invasores) && colide_wave(buffer->invasores, missil))
			destroi_missil_tanque(buffer->tanque);
		else
			for (int i = 0; i < buffer->n_escudos && missil; i++)
				if (colide_escudo(buffer->escudo[i], missil)){
					destroi_missil_tanque(buffer->tanque);
					break;
				}
		}
}
//Te q escrever algo aqui.
void game_over(){

}

void processa_buffer(Buffer* buffer){
	processa_wave(buffer->invasores);
	processa_nave(buffer->ovni);
	move_nave(buffer->ovni);
	processa_tanque(buffer->tanque);
	processa_colisao(buffer);

	if(get_bottom_wave(buffer->invasores) >= get_top_tanque(buffer->tanque))
		game_over();
}

void desenha_buffer(Buffer* buffer, int largura, int altura){
	al_set_target_bitmap(buffer->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for( int i = 0; i < buffer->n_escudos; i++ )
		desenha_escudo( buffer->escudo[i] );

	draw_wave(buffer->invasores);
	desenha_nave(buffer->ovni);

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
