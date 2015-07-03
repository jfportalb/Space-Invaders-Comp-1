#include "jogo.h"
#include <stdio.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//Inicializações básicas do Allegro.
void allegro_init(Jogo* jogo);
void allegro_image_init(Jogo* jogo);
void allegro_primitives_init(Jogo* jogo);
void allegro_audio_init(Jogo* jogo);
void allegro_acodec_init(Jogo* jogo);
void allegro_reserve_samples(Jogo* jogo);
void allegro_font_init(Jogo* jogo);
void allegro_mouse_init(Jogo* jogo);
void allegro_keyboard_init(Jogo* jogo);
void allegro_display_init(Jogo* jogo, int largura, int altura);
void allegro_timer_init(Jogo* jogo);
void allegro_event_queue_init(Jogo* jogo);

//Outras inicializações do jogo:
void menu_inicial_init(Jogo* jogo);
void menu_pausa_init(Jogo* jogo);
void menu_opcoes_init(Jogo* jogo);
void menu_end_game_init(Jogo* jogo);

//Inicializações da partida:
void cria_escudos(Jogo* jogo);
void cria_tanque(Jogo* jogo);
void cria_sound_manager(Jogo *jogo);
void finaliza_jogo(Jogo* jogo);

//Botões dos menus:
void aumenta_tela(void* ptr);
void diminui_tela(void* ptr);
void game_start(void* ptr);
void ir_para_menu_inicial(void* ptr);
void ir_para_menu_de_pausa(Jogo* jogo);
void ir_para_menu_de_opcoes(void* ptr);
void voltar_ao_jogo(void* ptr);
void sair_jogo(void* ptr);

//Outras funções secundárias:
void get_keyboard_up(Jogo* jogo, ALLEGRO_EVENT ev);
void get_keyboard_down(Jogo* jogo, ALLEGRO_EVENT ev);

void inicializa_jogo (Jogo* jogo){
	jogo->largura = LARGURA_INICIAL;
	jogo->altura = ALTURA_INICIAL;
	jogo->sair = false;
	jogo->redraw = false;

	allegro_init(jogo);
	allegro_display_init(jogo, jogo->largura, jogo->altura);
	allegro_image_init(jogo);
	allegro_primitives_init(jogo);
	allegro_audio_init(jogo);
	allegro_acodec_init(jogo);
	allegro_reserve_samples(jogo);
	allegro_audio_init(jogo);
	allegro_font_init(jogo);
	
	allegro_mouse_init(jogo);
	allegro_keyboard_init(jogo);
	allegro_timer_init(jogo);
	
	allegro_event_queue_init(jogo);

	jogo->estado_do_jogo = MENU_INICIAL;

	menu_inicial_init( jogo);
	menu_pausa_init( jogo);
	menu_opcoes_init( jogo);
	menu_end_game_init( jogo);

	cria_sound_manager(jogo);
	
	for (int i = 0; i<N_ESCUDOS; i++)
		jogo->escudo[i] = NULL;
	jogo->tanque = NULL;
	jogo->invasores = NULL;

	al_set_window_title(jogo->display, "Space Invaders");
}

void processa_menu(Jogo* jogo, Menu* menu, ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		jogo->sair = true;
	else if (ev.type == ALLEGRO_EVENT_TIMER)
		jogo->redraw = true;
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_DOWN:
				menu_down(menu);
				break;
			case ALLEGRO_KEY_UP:
				menu_up(menu);
				break;
			case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_ENTER:
				menu_enter(menu);
				break;
		}
}

void processa_jogo(Jogo* jogo, ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		jogo->sair = true;
	else if (ev.type == ALLEGRO_EVENT_TIMER){
		if(jogo->key[KEY_LEFT] && get_posicao_x_min_tanque(jogo->tanque) > 0)
            tanque_move_esquerda(jogo->tanque);
        if(jogo->key[KEY_RIGHT] && get_posicao_x_max_tanque(jogo->tanque) < LARGURA_INICIAL)
            tanque_move_direita(jogo->tanque);
        processa_buffer(jogo->buffer);
		jogo->redraw = true;
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		get_keyboard_down ( jogo, ev );
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		get_keyboard_up ( jogo, ev );
	if (!jogo->game_on)
		if (jogo->vidas < 0)
			jogo->estado_do_jogo = GAME_OVER;
		else
			jogo->estado_do_jogo = VITORIA;
}

void desenha_jogo(Jogo* jogo){
	desenha_buffer(jogo->buffer, jogo->largura, jogo->altura);
}

void desenha_game_over(Jogo* jogo){
	// desenha_menu(jogo->menu[MENU_END_GAME], jogo->largura, jogo->altura);
	char strGameOver[100];
	sprintf(strGameOver, "Sua pontuacao foi: %d", jogo->score);
	// al_draw_text(jogo->fonte, al_map_rgb(00,0,0), 20, 200, 0, strGameOver);
	desenha_menu(jogo->menu[MENU_END_GAME], jogo->largura, jogo->altura, strGameOver);

	al_flip_display();
}

void desenha_vitoria(Jogo* jogo){
	char strVitoria[100];
	// al_draw_text(jogo->fonte, al_map_rgb(00,0,0), 20, 200, 0, "");
	sprintf(strVitoria, "Parabens, voce ganhou!!! Sua pontuacao foi: %d", jogo->score);
	// al_draw_text(jogo->fonte, al_map_rgb(00,0,0), 20, 230, 0, strVitoria);
	desenha_menu(jogo->menu[MENU_END_GAME], jogo->largura, jogo->altura, strVitoria);

	al_flip_display();
}

void main_loop_jogo(Jogo* jogo){
	al_start_timer(jogo->timer);
	while(!jogo->sair){
		ALLEGRO_EVENT ev;
		al_wait_for_event(jogo->event_queue, &ev);
		switch (jogo->estado_do_jogo){		
			case MENU_INICIAL:
				processa_menu(jogo, jogo->menu[MENU_PRINCIPAL], ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_menu(jogo->menu[MENU_PRINCIPAL], jogo->largura, jogo->altura, 0);
					al_flip_display();
				}
				break;
			case PLAY:
				processa_jogo(jogo, ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_jogo(jogo);
				}
				break;
			case MENU_PAUSA:
				processa_menu(jogo, jogo->menu[MENU_DE_PAUSA], ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_menu(jogo->menu[MENU_DE_PAUSA], jogo->largura, jogo->altura, 0);
					al_flip_display();
				}
				break;
			case MENU_OPCOES:
				processa_menu(jogo, jogo->menu[MENU_DE_OPCOES], ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_menu(jogo->menu[MENU_DE_OPCOES], jogo->largura, jogo->altura, 0);
					al_flip_display();
				}
				break;
			case GAME_OVER:
				processa_menu(jogo,jogo->menu[MENU_END_GAME], ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_game_over(jogo);
				}
				break;
			case VITORIA:
				processa_menu(jogo, jogo->menu[MENU_END_GAME], ev);
				if(jogo->redraw && al_is_event_queue_empty( jogo->event_queue)){
					jogo->redraw = false;
					desenha_vitoria(jogo);
				}
				break;
		}
	}
}

void destroi_jogo (Jogo* jogo){
	finaliza_jogo(jogo);
	finaliza_menu( jogo->menu[0]);
	finaliza_menu( jogo->menu[1]);
	finaliza_menu( jogo->menu[2]);
	if (jogo->sound_mng) jogo->sound_mng = finaliza_sound_manager(jogo->sound_mng);
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
void allegro_audio_init(Jogo *jogo){
	if(!al_install_audio()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o addon de audio do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);		
	}
}
void allegro_acodec_init(Jogo* jogo){
	if(!al_init_acodec_addon()){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar os codecs de audio do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);		
	}
}
void allegro_reserve_samples(Jogo *jogo){
	if(!al_reserve_samples(N_SAMPLES)){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao reservar as samples de audio do Allegro.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
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
void menu_inicial_init(Jogo* jogo){
	jogo->menu[MENU_PRINCIPAL] = inicializa_menu( jogo->fonte, jogo->largura, jogo->altura, 3, "imagens/title.png");
	cria_botao(jogo->menu[MENU_PRINCIPAL], 0, "Novo jogo", game_start, jogo);
	cria_botao(jogo->menu[MENU_PRINCIPAL], 1, "Opcoes", ir_para_menu_de_opcoes, jogo);
	cria_botao(jogo->menu[MENU_PRINCIPAL], 2, "Sair", sair_jogo, jogo);
}
void menu_pausa_init(Jogo* jogo){
	jogo->menu[MENU_DE_PAUSA] = inicializa_menu( jogo->fonte, jogo->largura, jogo->altura, 3, "imagens/pausa.png");
	cria_botao(jogo->menu[MENU_DE_PAUSA], 0, "Voltar ao jogo", voltar_ao_jogo, jogo);
	cria_botao(jogo->menu[MENU_DE_PAUSA], 1, "Novo jogo", game_start, jogo);
	cria_botao(jogo->menu[MENU_DE_PAUSA], 2, "Menu principal", ir_para_menu_inicial, jogo); 
}
void menu_opcoes_init(Jogo* jogo){
	jogo->menu[MENU_DE_OPCOES] = inicializa_menu( jogo->fonte, jogo->largura, jogo->altura, 3, 0);
	cria_botao(jogo->menu[MENU_DE_OPCOES], 0, "Aumenta resolucao", aumenta_tela, jogo); 
	cria_botao(jogo->menu[MENU_DE_OPCOES], 1, "Dimunui resolucao", diminui_tela, jogo); 
	cria_botao(jogo->menu[MENU_DE_OPCOES], 2, "Menu principal", ir_para_menu_inicial, jogo); 
}
void menu_end_game_init(Jogo* jogo){
	jogo->menu[MENU_END_GAME] = inicializa_menu( jogo->fonte, jogo->largura, jogo->altura, 3, 0);
	cria_botao(jogo->menu[MENU_END_GAME], 0, "Novo jogo", game_start, jogo);
	cria_botao(jogo->menu[MENU_END_GAME], 1, "Menu principal", ir_para_menu_inicial, jogo); 
	cria_botao(jogo->menu[MENU_END_GAME], 2, "Sair", sair_jogo, jogo);
}

//Funções usadas na inicialização da partida:
void cria_escudos(Jogo* jogo){
	for( int i = 0, x = (LARGURA_INICIAL / N_ESCUDOS - TAMANHO_PEDACO*PEDACOS_HORIZONTAL) / 2; 
		i < N_ESCUDOS; 
 		i++, x += LARGURA_INICIAL / N_ESCUDOS ) {
		jogo->escudo[i] = inicializa_escudo( x, ALTURA_INICIAL/4 * 3 );
		if(!jogo->escudo[i]){
			al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar imagem do escudo.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
			destroi_jogo(jogo);
			exit(1);
		}
	}
}
void cria_tanque(Jogo* jogo){
	jogo->tanque = inicializa_tanque(LARGURA_INICIAL/2, ALTURA_INICIAL/8 * 7, jogo->sound_mng);
	if(!jogo->tanque){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar imagem do tanque.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		destroi_jogo(jogo);
		exit(1);
	}
}
void cria_sound_manager(Jogo* jogo){
	jogo->sound_mng = inicializa_sound_manager();
	if(!jogo->sound_mng){
		al_show_native_message_box(jogo->display, "Erro", "Erro", "Falha ao iniciar o sound manager.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
		destroi_jogo(jogo);
		exit(1);
	}
}
void finaliza_jogo(Jogo* jogo){
	if(jogo->invasores) jogo->invasores = destroi_wave(jogo->invasores);
	if(jogo->tanque) jogo-> tanque = destroi_tanque(jogo->tanque);
	for(int i=0; i<N_ESCUDOS; i++)
		if(jogo->escudo[i]) jogo->escudo[i] = finaliza_escudo(jogo->escudo[i]);
}

void aumenta_tela(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	if (true){
		jogo->largura += MEDIDA_RESIZE*4;
		jogo->altura += MEDIDA_RESIZE*3;
		al_resize_display(jogo->display, jogo->largura , jogo->altura);
	}
}
void diminui_tela(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	if (jogo->largura > LARGURA_INICIAL){
		jogo->largura -= MEDIDA_RESIZE*4;
		jogo->altura -= MEDIDA_RESIZE*3;
		al_resize_display(jogo->display, jogo->largura , jogo->altura);
	}
}
void game_start(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	finaliza_jogo(jogo);
	jogo-> vidas = VIDAS_INICIAIS;
	jogo->score = 0;
	for(int i=0; i<N_KEYS;	 i++)
		jogo->key[i] = false;
	cria_escudos( jogo);
	cria_tanque( jogo);
	jogo->invasores = create_wave(70, N_ALIEN, jogo->sound_mng);
	jogo->ovni = cria_nave(50, 5, 10, 2);
	jogo->game_on = true;
	jogo->buffer = inicializa_buffer(jogo->display, jogo->fonte, LARGURA_INICIAL, ALTURA_INICIAL, jogo->escudo, N_ESCUDOS, 
									 jogo->tanque, jogo->invasores, jogo->ovni,&jogo->vidas, &jogo->score, &jogo->game_on, jogo->sound_mng);
	jogo->estado_do_jogo = PLAY;	
}
void ir_para_menu_inicial(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	finaliza_jogo(jogo);
	reinicia_menu(jogo->menu[MENU_PRINCIPAL]);
	jogo->estado_do_jogo = MENU_INICIAL;
}
void ir_para_menu_de_pausa(Jogo* jogo){
	reinicia_menu(jogo->menu[MENU_DE_PAUSA]);
	jogo->estado_do_jogo = MENU_PAUSA;
}
void ir_para_menu_de_opcoes(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	reinicia_menu(jogo->menu[MENU_DE_OPCOES]);
	jogo->estado_do_jogo = MENU_OPCOES;
}
void voltar_ao_jogo(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	jogo->estado_do_jogo = PLAY;
}
void sair_jogo(void* ptr){
	Jogo* jogo = (Jogo*) ptr;
	jogo->sair = true;
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
			ir_para_menu_de_pausa(jogo);
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
