#include "buffer.h"
#include <stdio.h>

Buffer* inicializa_buffer( ALLEGRO_DISPLAY *display, ALLEGRO_FONT* fonte, int largura, int altura, Escudo* escudo[], int n_escudos, Tanque *tanque, wave* invasores, nave* ovni, int* vidas, int* score, bool* game_on){
	Buffer* buffer = (Buffer*) malloc (sizeof(Buffer));

	buffer->vidas = vidas;
	buffer->score = score;
	buffer->game_on = game_on;
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

void tanque_morreu(Buffer* buffer){
	*(buffer->vidas) -= 1;
	reinicia_tanque(buffer->tanque);
}

void processa_colisao(Buffer* buffer){
	Missil* missil_tanque = get_missil_tanque(buffer->tanque);
	if (missil_tanque)
		if( get_y_missil(missil_tanque) < 0)
			destroi_missil_tanque(buffer->tanque);
		else {
			int pts = colide_wave(buffer->invasores, missil_tanque);
			if(pts){
				*buffer->score += pts;
				destroi_missil_tanque(buffer->tanque);
			}
			else if(colide_nave(buffer->ovni, missil_tanque)){
				*buffer->score += PONTOS_NAVE_MAE;
				buffer->ovni = NULL; 
				destroi_missil_tanque(buffer->tanque);
			}
			else
				for (int i = 0; i < buffer->n_escudos && missil_tanque; i++)
					if (colide_escudo(buffer->escudo[i], missil_tanque)){
						destroi_missil_tanque(buffer->tanque);
						break;
					}
		}
	for (int i=0; i<MAX_MISSEIS; i++){
		Missil* missil_wave = get_missil_wave(buffer->invasores, i);
		if (missil_wave){
			if ( get_y_missil(missil_wave) > buffer->altura_inicial)
				destroi_missil_wave(buffer->invasores, i);
			else{
				for (int j = 0; j < buffer->n_escudos && missil_wave; j++)
					if (colide_escudo(buffer->escudo[j], missil_wave)){
						destroi_missil_wave(buffer->invasores, i);
						break;
					}
				if (colide_tanque(buffer->tanque, missil_wave)){
						destroi_missil_wave(buffer->invasores, i);
						tanque_morreu(buffer);
				}
			}
		}
	}
	if(get_bottom_wave(buffer->invasores) >= get_top_escudo(buffer->escudo[0]))
		for(int i=0; i<buffer->n_escudos; i++)
			destroi_topo_escudo(buffer->escudo[i]);
}
//Te q escrever algo aqui.
void end_game(Buffer* buffer){
	*buffer->game_on = false;
}

void processa_buffer(Buffer* buffer){
	processa_wave(buffer->invasores);
	processa_nave(buffer->ovni);
	move_nave(buffer->ovni);
	processa_tanque(buffer->tanque);
	processa_colisao(buffer);

	//Caso vitorioso:
	if (get_linhas_wave(buffer->invasores) == 0)
		end_game(buffer);

	//Derrota:
	if(get_bottom_wave(buffer->invasores) >= get_top_tanque(buffer->tanque) || *buffer->vidas < 0){
		*buffer->vidas = -1;
		end_game(buffer);
	}
}

void desenha_buffer(Buffer* buffer, int largura, int altura){
	al_set_target_bitmap(buffer->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for( int i = 0; i < buffer->n_escudos; i++ )
		desenha_escudo( buffer->escudo[i] );

	draw_wave(buffer->invasores);
	if (buffer->ovni) desenha_nave(buffer->ovni);

	desenha_tanque(buffer->tanque);
	char strScore[100], strVidas[5];
	sprintf(strScore, "SCORE: %d", *(buffer->score));
	sprintf(strVidas, "X %d", *(buffer->vidas));
	al_draw_text(buffer->fonte, al_map_rgb(255,255,255), 0, 10, 0, strScore );
	al_draw_bitmap(get_imagem_tanque(buffer->tanque),10+ buffer->largura_inicial/5*3 , 5, 0);
	al_draw_text(buffer->fonte, al_map_rgb(255,255,255), buffer->largura_inicial/4*3, 10, 0, strVidas);


	al_flip_display();
	al_set_target_backbuffer(buffer->display);
	al_draw_scaled_bitmap(buffer->buffer, 0, 0, buffer->largura_inicial, buffer->altura_inicial, 0, 0, largura, altura, 0);	
}

Buffer* destroi_buffer(Buffer* buffer){
	free(buffer);
	return buffer;
}
