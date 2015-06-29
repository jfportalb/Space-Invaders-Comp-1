#include "jogo.h"
#include <stdio.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

//Inicializações básicas do Allegro.
void allegro_init(Jogo* jogo);
void allegro_image_init(Jogo* jogo);
void allegro_primitives_init(Jogo* jogo);
void allegro_font_init(Jogo* jogo);
void allegro_mouse_init(Jogo* jogo);
void allegro_keyboard_init(Jogo* jogo);
void allegro_display_init(Jogo* jogo, int largura, int altura);
void allegro_timer_init(Jogo* jogo);
void allegro_event_queue_init(Jogo* jogo);

//Outras inicializações do jogo:
void game_start(Jogo* jogo);
void cria_escudos(Jogo* jogo);
void cria_tanque(Jogo* jogo);
void finaliza_jogo(Jogo* jogo);

//Outras funções secundárias:
void get_keyboard_up(Jogo* jogo, ALLEGRO_EVENT ev);
void get_keyboard_down(Jogo* jogo, ALLEGRO_EVENT ev);

void inicializa_jogo (Jogo* jogo, int largura, int altura){
	jogo->largura = largura;
	jogo->altura = altura;
	jogo->sair = false;
	jogo->redraw = false;

	allegro_init(jogo);
	allegro_display_init(jogo, jogo->largura, jogo->altura);
	allegro_image_init(jogo);
	allegro_primitives_init(jogo);
	allegro_font_init(jogo);
	
	allegro_mouse_init(jogo);
	allegro_keyboard_init(jogo);
	allegro_timer_init(jogo);
	
	allegro_event_queue_init(jogo);

	// jogo->estado_do_jogo = PUSH_START;
	jogo->estado_do_jogo = MENU_INICIAL;
	jogo->estado_do_jogo_anterior = MENU_INICIAL;

	// inicializa_menu(&(jogo->menu_start), jogo->fonte, jogo->largura, jogo->altura, PUSH_START); 
	inicializa_menu(&(jogo->menu_principal), jogo->fonte, jogo->largura, jogo->altura, MENU_INICIAL); 
	inicializa_menu(&(jogo->menu_opcoes), jogo->fonte, jogo->largura, jogo->altura, OPCOES); 
	inicializa_menu(&(jogo->menu_pausa), jogo->fonte, jogo->largura, jogo->altura, MENU_PAUSA); 

	for (int i = 0; i<N_ESCUDOS; i++)
		jogo->escudo[i] = NULL;
	jogo->tanque = NULL;

	game_start(jogo); //Esta função deve ser colocada dentro dos menus para o início de uma nova partida.
}

void processa_menu_inicial(Jogo* jogo, ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		jogo->sair = true;
	else if (ev.type == ALLEGRO_EVENT_TIMER)
		jogo->redraw = true;
}

void desenha_menu_inicial(Jogo* jogo){
	al_clear_to_color(al_map_rgb( 0, 150, 0));

	al_flip_display();
}

void processa_jogo(Jogo* jogo, ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		jogo->sair = true;
	else if (ev.type == ALLEGRO_EVENT_TIMER){
		if(jogo->key[KEY_LEFT] && get_posicao_x_min_tanque(jogo->tanque) > 0)
            tanque_move_esquerda(jogo->tanque);
        if(jogo->key[KEY_RIGHT] && get_posicao_x_max_tanque(jogo->tanque) < jogo->largura)
            tanque_move_direita(jogo->tanque);
        processa_buffer(jogo->buffer);
		jogo->redraw = true;
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		get_keyboard_down ( jogo, ev );
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		get_keyboard_up ( jogo, ev );
}

void desenha_jogo(Jogo* jogo){
	desenha_buffer(jogo->buffer, jogo->largura, jogo->altura);
}

void processa_menu_pausa(Jogo* jogo, ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		jogo->sair = true;
	else if (ev.type == ALLEGRO_EVENT_TIMER)
		jogo->redraw = true;
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		get_keyboard_down(jogo, ev);
}

void desenha_menu_pausa(Jogo* jogo){
	al_clear_to_color(al_map_rgb(150, 0, 0));
	al_draw_text(jogo->fonte, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, "Menu");
	al_flip_display();
}

void main_loop_jogo(Jogo* jogo){
	desenha_jogo(jogo);
	al_start_timer(jogo->timer);
	while(!jogo->sair){
		ALLEGRO_EVENT ev;
		al_wait_for_event(jogo->event_queue, &ev);
		switch (jogo->estado_do_jogo){
			// case PUSH_START:
			// 	if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
			// 		switch (ev.keyboard.keycode){
			// 			case ALLEGRO_KEY_ESCAPE:
			// 				jogo->estado_do_jogo = GAME_OVER;
			// 				break;
			// 			case ALLEGRO_KEY_SPACE:
			// 				clica_botao(jogo->menu_start.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
			// 				break;
			// 			case ALLEGRO_KEY_ENTER:
			// 				clica_botao(jogo->menu_start.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
			// 				break;
			// 		}

			// 	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			// 		jogo->estado_do_jogo = GAME_OVER;

			// 	desenha_menu(&(jogo->menu_start), jogo->fonte, true);
			// 	break;
			case MENU_INICIAL:
				if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_ESCAPE:
							jogo->estado_do_jogo = GAME_OVER;
							break;
						case ALLEGRO_KEY_DOWN:
							menu_down(&jogo->menu_principal);
							break;
						case ALLEGRO_KEY_UP:
							if (jogo->menu_principal.botao_highlight > 0){
								jogo->menu_principal.botoes[jogo->menu_principal.botao_highlight].botao_cor = NORMAL;
								jogo->menu_principal.botao_highlight = (MYBUTTONS) (jogo->menu_principal.botao_highlight - 1);
								jogo->menu_principal.botoes[jogo->menu_principal.botao_highlight].botao_cor = HIGHLIGHT;
							} else {
								jogo->menu_principal.botoes[jogo->menu_principal.botao_highlight].botao_cor = NORMAL;
								jogo->menu_principal.botao_highlight = (MYBUTTONS) (jogo->menu_principal.numero_botoes - 1);
								jogo->menu_principal.botoes[jogo->menu_principal.botao_highlight].botao_cor = HIGHLIGHT;
							}
							break;
						case ALLEGRO_KEY_SPACE:
							jogo->estado_do_jogo_anterior = MENU_PAUSA;
							clica_botao(jogo->menu_principal.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
							break;
						case ALLEGRO_KEY_ENTER:
							jogo->estado_do_jogo_anterior = MENU_INICIAL;
							clica_botao(jogo->menu_principal.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
							break;
					}

				if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					jogo->estado_do_jogo = GAME_OVER;
				desenha_menu(&(jogo->menu_principal), jogo->fonte, true);
				break;
			// case MENU_INICIAL:
			// 	processa_menu_inicial(jogo, ev);
			// 	if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
			// 		jogo->redraw = false;
			// 		desenha_menu_inicial(jogo);
			// 	}
			// 	break;
			case PLAY_GAME:
				processa_jogo(jogo, ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_jogo(jogo);
				}
				break;
			case MENU_PAUSA:
				if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_ESCAPE:
							jogo->estado_do_jogo = GAME_OVER;
							break;
						case ALLEGRO_KEY_DOWN:
							if (jogo->menu_pausa.botao_highlight < jogo->menu_pausa.numero_botoes - 1){
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = NORMAL;
								jogo->menu_pausa.botao_highlight = (MYBUTTONS) (jogo->menu_pausa.botao_highlight + 1);
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = HIGHLIGHT;
							} else {
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = NORMAL;
								jogo->menu_pausa.botao_highlight = (MYBUTTONS) 0;
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = HIGHLIGHT;
							}
							break;
						case ALLEGRO_KEY_UP:
							if (jogo->menu_pausa.botao_highlight > 0){
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = NORMAL;
								jogo->menu_pausa.botao_highlight = (MYBUTTONS) (jogo->menu_pausa.botao_highlight - 1);
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = HIGHLIGHT;
							} else {
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = NORMAL;
								jogo->menu_pausa.botao_highlight = (MYBUTTONS) (jogo->menu_pausa.numero_botoes - 1);
								jogo->menu_pausa.botoes[jogo->menu_pausa.botao_highlight].botao_cor = HIGHLIGHT;
							}
							break;
						case ALLEGRO_KEY_SPACE:
							jogo->estado_do_jogo_anterior = MENU_PAUSA;
							clica_botao(jogo->menu_pausa.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
							break;
						case ALLEGRO_KEY_ENTER:
							jogo->estado_do_jogo_anterior = MENU_PAUSA;
							clica_botao(jogo->menu_pausa.botao_highlight, &(jogo->estado_do_jogo), jogo->estado_do_jogo_anterior);
							break;
					}

				if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					jogo->estado_do_jogo = GAME_OVER;
				desenha_menu(&(jogo->menu_pausa), jogo->fonte, false);
				break;
			// case MENU_PAUSA:
			// 	processa_menu_pausa(jogo, ev);
			// 	if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
			// 		jogo->redraw = false;
			// 		desenha_menu_pausa(jogo);
			// 	}
			// 	break;
			case GAME_OVER:
				break;
		}
	}
}

void destroi_jogo (Jogo* jogo){
	finaliza_jogo(jogo);
	finaliza_menu(&(jogo->menu_start));
	finaliza_menu(&(jogo->menu_principal));
	finaliza_menu(&(jogo->menu_opcoes));
	finaliza_menu(&(jogo->menu_pausa));
	al_destroy_event_queue(jogo->event_queue);
	al_destroy_timer(jogo->timer);
	al_destroy_display(jogo->display);
}

//Funções usadas na inicialização do jogo.
void allegro_init(Jogo* jogo){
	if(!al_init()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}	
}
void allegro_image_init(Jogo* jogo){
	if(!al_init_image_addon()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o addon de imagens do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}
void allegro_primitives_init(Jogo* jogo){
	if(!al_init_primitives_addon()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o addon de primitivos do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);		
	}
}
void allegro_font_init(Jogo* jogo){
	al_init_font_addon();
	al_init_ttf_addon();
	jogo->fonte = al_load_ttf_font("imagens/space_invaders.ttf", 25, 0);
	if(!jogo->fonte){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar a fonte.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}
void allegro_mouse_init(Jogo* jogo){
	if(!al_install_mouse()) {
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o teclado.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
    	exit(1);
   }
}
void allegro_keyboard_init(Jogo* jogo){
	if(!al_install_keyboard()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o teclado.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	for(int i=0; i<N_KEYS;	 i++)
		jogo->key[i] = false;
}
void allegro_display_init(Jogo* jogo, int largura, int altura){
	jogo->display = al_create_display(largura, altura);
	if(!jogo->display){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o display.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}
void allegro_timer_init(Jogo* jogo){
	jogo->timer = al_create_timer(1.0/FPS);
	if(!jogo->timer){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o timer do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}
void allegro_event_queue_init(Jogo* jogo){
	jogo->event_queue = al_create_event_queue();
	if(!jogo->event_queue){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar a lista de eventos.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		destroi_jogo(jogo);
		exit(1);
	}

	al_register_event_source(jogo->event_queue, al_get_mouse_event_source());
	al_register_event_source(jogo->event_queue, al_get_keyboard_event_source());
	al_register_event_source(jogo->event_queue, al_get_timer_event_source(jogo->timer));
	al_register_event_source(jogo->event_queue, al_get_display_event_source(jogo->display));
}

//Funções usadas na inicialização da partida:
void game_start(Jogo* jogo){
	finaliza_jogo(jogo);
	jogo-> vidas = 2;
	jogo->score = 0;
	cria_escudos( jogo);
	cria_tanque( jogo);
	jogo->buffer = inicializa_buffer(jogo->display, jogo->fonte, jogo->largura, jogo->altura, jogo->escudo, jogo->tanque, &jogo->vidas, &jogo->score);
	jogo->estado_do_jogo = PLAY_GAME;	
}
void cria_escudos(Jogo* jogo){
	for( int i = 0, x = (jogo->largura / N_ESCUDOS - TAMANHO_ESCUDO) / 2; 
		i < N_ESCUDOS; 
 		i++, x += jogo->largura / N_ESCUDOS ) {
		jogo->escudo[i] = inicializa_escudo( x, jogo->altura/4 * 3 );
		if(!jogo->escudo[i]){
			al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar imagem do escudo.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
			destroi_jogo(jogo);
			exit(1);
		}
	}
}
void cria_tanque(Jogo* jogo){
	jogo->tanque = inicializa_tanque(jogo->largura/2, jogo->altura/8 * 7);
	if(!jogo->tanque){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar imagem do tanque.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		destroi_jogo(jogo);
		exit(1);
	}
}
void finaliza_jogo(Jogo* jogo){
	if(jogo->tanque) jogo-> tanque = destroi_tanque(jogo->tanque);
	for(int i=0; i<N_ESCUDOS; i++)
		if(jogo->escudo[i]) jogo->escudo[i] = finaliza_escudo(jogo->escudo[i]);
}


//Funções Secundárias:
void get_keyboard_up(Jogo* jogo, ALLEGRO_EVENT ev){
	switch (ev.keyboard.keycode){
		case ALLEGRO_KEY_SPACE:
			jogo->key[KEY_SPACE] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			jogo->key[KEY_LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			jogo->key[KEY_RIGHT] = false;
			break;
	}
}
void get_keyboard_down(Jogo* jogo, ALLEGRO_EVENT ev){
	switch (ev.keyboard.keycode){
		case ALLEGRO_KEY_ESCAPE:
			if(jogo->estado_do_jogo == PLAY_GAME)
				jogo->estado_do_jogo = MENU_PAUSA;
			else if(jogo->estado_do_jogo == MENU_PAUSA)
				jogo->estado_do_jogo = PLAY_GAME;
			break;
		case ALLEGRO_KEY_SPACE:
			jogo->key[KEY_SPACE] = true;
			atira_tanque(jogo->tanque);
			break;
		case ALLEGRO_KEY_LEFT:
			jogo->key[KEY_LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			jogo->key[KEY_RIGHT] = true;
			break;
		}
}