#ifndef ALIEN_H
#define ALIEN_H

struct Alien{
	int posicao_x, posicao_y;
	ALLEGRO_BITMAP* imagem[3];
};

void inicializa_alien(Alien* alien, int posicao_x, int posicao_y);

void destroi_alien(Alien* alien);

void explode_alien(ALIEN* alien);

void move_alien_esquerda(ALIEN* alien);

void move_alien_direita(ALIEN* alien);

#endif