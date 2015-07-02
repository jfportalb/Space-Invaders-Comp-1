#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "wave.h"
 
//ADICIONAR NAVE-MÃE!!!
//A função posiciona a wave no meio de tela de largura 640. Ainda é preciso torná-la agóstica a resolução
//O valor do campo velocidade precisa ser um divisor de (largura do display - largura wave)/2 para que colida com o limite direito da tela
//Do contrário, a wave irá atravesá-los antes de voltar.
//Uma outra possibilidade é tornar o limite o 
wave* create_wave(int y_inicial, int n_aliens) {
 
    struct wave* obj = (struct wave*) malloc(sizeof(struct wave));
    obj->x = 72; 
    obj->y = y_inicial;
    obj->anima_contador = 0;
    obj->ritmo = 20;
    obj->velocidade = ALIEN_SPEED;

    obj->n_aliens = n_aliens;
    obj->wave_width = (n_aliens * ALIEN_SIZE) + ((n_aliens - 1) * ALIEN_SPACING);
    //create squids row
    int i;
    int j;
    obj->linhas = 5;

    obj->squids = (alien**) malloc (sizeof(alien*)*obj->n_aliens);
    for(i = 0; i < obj->n_aliens; i++) {
        obj->squids[i] = create_alien(obj->x + i*(ALIEN_SIZE + ALIEN_SPACING), obj->y, SQUID);
    }
    //Create 2 jellyfish rows
    for(i = 0; i < 2; i++) {
    	obj->jellyfishes[i] = (alien**) malloc (sizeof(alien*)*obj->n_aliens);
        for(j = 0; j < obj->n_aliens; j++) {
            obj->jellyfishes[i][j] = create_alien(obj->x + j*(ALIEN_SIZE + ALIEN_SPACING), obj->y + (i + 1) * (ALIEN_SIZE), JELLYFISH);
        }
    }
    //Create 2 crab rows
    for(i = 0; i < 2; i++) {
 
    	obj->crabs[i] = (alien**) malloc (sizeof(alien*)*obj->n_aliens);
        for(j = 0; j < obj->n_aliens; j++) {
            obj->crabs[i][j] = create_alien(obj->x + j*(ALIEN_SIZE + ALIEN_SPACING), obj->y + (i + 3) * (ALIEN_SIZE), CRAB);
        }
    }

    for (int i=0; i<5; i++){
        obj->aliens_mortos[i]=0;
    }
    return obj;
}
void draw_wave(struct wave* obj) {
 
    int i;
    for(i = 0; i < obj->n_aliens; i++) {
         
        if(obj->squids[i])
            draw_alien(obj->squids[i]);
        if(obj->jellyfishes[0][i])
            draw_alien(obj->jellyfishes[0][i]);
        if(obj->jellyfishes[1][i])
            draw_alien(obj->jellyfishes[1][i]);
        if(obj->crabs[0][i])
            draw_alien(obj->crabs[0][i]);
        if(obj->crabs[1][i])
            draw_alien(obj->crabs[1][i]);
    }
}
void anima_wave(struct wave* obj) {
 
    int i;
    for(i = 0; i < obj->n_aliens; i++) {
         
        if(obj->squids[i])
            anima_alien(obj->squids[i]);
        if(obj->jellyfishes[0][i])
            anima_alien(obj->jellyfishes[0][i]);
        if(obj->jellyfishes[1][i])
            anima_alien(obj->jellyfishes[1][i]);
        if(obj->crabs[0][i])
            anima_alien(obj->crabs[0][i]);
        if(obj->crabs[1][i])
            anima_alien(obj->crabs[1][i]);
    }
}
//Chama a função de movimentação da wave apropriada com base na direção de velocidade da wave e sua posição na tela
void move_wave_horizontal(struct wave* obj) {
    obj->x+=obj->velocidade;
    int i;
    for(i = 0; i < obj->n_aliens; i++) {
         
        if(obj->squids[i])
            move_alien_horizontal(obj->squids[i], obj->velocidade);
        if(obj->jellyfishes[0][i])
            move_alien_horizontal(obj->jellyfishes[0][i], obj->velocidade);
        if(obj->jellyfishes[1][i])
            move_alien_horizontal(obj->jellyfishes[1][i], obj->velocidade);
        if(obj->crabs[0][i])
            move_alien_horizontal(obj->crabs[0][i], obj->velocidade);
        if(obj->crabs[1][i])
            move_alien_horizontal(obj->crabs[1][i], obj->velocidade);
    }
}
void move_wave_baixo(struct wave* obj) {
 
    int velocidade = abs(obj->velocidade);
    obj->y += velocidade;
    int i;
    for(i = 0; i < obj->n_aliens; i++) {
         
        if(obj->squids[i])
            move_alien_baixo(obj->squids[i], velocidade);
        if(obj->jellyfishes[0][i])
            move_alien_baixo(obj->jellyfishes[0][i], velocidade);
        if(obj->jellyfishes[1][i])
            move_alien_baixo(obj->jellyfishes[1][i], velocidade);
        if(obj->crabs[0][i])
            move_alien_baixo(obj->crabs[0][i], velocidade);
        if(obj->crabs[1][i])
            move_alien_baixo(obj->crabs[1][i], velocidade);
    }
}

void atira_wave (struct wave* obj){
    int shooter = rand() % obj->n_aliens;
    
}

//Agrupa em uma única função toda a lógica de movimentação e animação da wave. Essa função é
//chamada em processa_jogo() toda vez que um ALLEGRO_EVENT_TIMER é recebido
void processa_wave(struct wave* obj) {
    obj->anima_contador++;
    static bool move_baixo = false;
    if(!(obj->anima_contador%obj->ritmo)){
             
        obj->anima_contador = 0;
        anima_wave(obj);
         
        if(move_baixo) {
            move_baixo = false;
            move_wave_baixo(obj);
        } else {
            move_wave_horizontal(obj);
            //Na linha seguinte os limites de largura do display estão inseridos forçadamente no código
            if(obj->x <= 0|| (obj->x + obj->wave_width)>=640) {
                obj->velocidade *= -1;
                move_baixo = true;
            }
        }
    }
}


bool colide_wave(wave* invasores, Missil* missil){
	int x = get_x_missil(missil);
	int y = get_y_missil(missil);
	x-= invasores->x;
	y-= invasores->y;
	if( x >= 0 && y >= 0 && x <  invasores->wave_width && y < ALIEN_SIZE * invasores->linhas + ALIEN_SPACING * (invasores->linhas - 1)){
		int coluna = x/(ALIEN_SIZE + ALIEN_SPACING);
		int linha = (y + ALIEN_SPACING)/(ALIEN_SIZE + ALIEN_SPACING);
        switch (linha){
            case 0:
                if ( acerta_alien (invasores->squids[coluna], get_x_missil(missil), get_y_missil(missil))){
                    invasores->squids[coluna] = NULL;
                    invasores->aliens_mortos[0] ++;
                    if ( invasores->aliens_mortos[0] == invasores->n_aliens) invasores->linhas--;
                    return true;
                }
                break;
            case 1:
                if ( acerta_alien (invasores->jellyfishes[0][coluna], get_x_missil(missil), get_y_missil(missil))){
                    invasores->jellyfishes[0][coluna] = NULL;
                    invasores->aliens_mortos[1] ++;
                    if ( invasores->aliens_mortos[1] == invasores->n_aliens) invasores->linhas--;
                    return true;
                }
                break;
            case 2:
                if ( acerta_alien (invasores->jellyfishes[1][coluna], get_x_missil(missil), get_y_missil(missil))){
                    invasores->jellyfishes[1][coluna] = NULL;
                    invasores->aliens_mortos[2] ++;
                    if ( invasores->aliens_mortos[2] == invasores->n_aliens) invasores->linhas--;
                    return true;
                }
                break;
            case 3:
                if ( acerta_alien (invasores->crabs[0][coluna], get_x_missil(missil), get_y_missil(missil))){
                    invasores->crabs[0][coluna] = NULL;
                    invasores->aliens_mortos[3] ++;
                    if ( invasores->aliens_mortos[3] == invasores->n_aliens) invasores->linhas--;
                    return true;
                }
                break;
            case 4:
                if ( acerta_alien (invasores->crabs[1][coluna], get_x_missil(missil), get_y_missil(missil))){
                    invasores->crabs[1][coluna] = NULL;
                    invasores->aliens_mortos[4] ++;
                    if ( invasores->aliens_mortos[4] == invasores->n_aliens) invasores->linhas--;
					return true;
                }
				break;
		}
	}
	return false;
}

int get_bottom_wave(wave* obj){
    return obj->linhas * ALIEN_SIZE + (obj->linhas - 1) * ALIEN_SPACING;
}