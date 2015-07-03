#ifndef ESCUDO_H
#define ESCUDO_H

#include "missil.h"

#define PEDACOS_HORIZONTAL 8
#define PEDACOS_VERTICAL 4 
#define TAMANHO_PEDACO 8

enum EstadoEscudo { INTEIRO, AVARIADO, DESTRUIDO };
enum LegoEscudo { QUADRADO, SUDESTE, NOROESTE, NORDESTE, SUDOESTE, VAZIO };

struct Escudo {
  int posicao_x, posicao_y, topo_destruido;
  LegoEscudo desenho[PEDACOS_HORIZONTAL][PEDACOS_VERTICAL];
  int pedaco[PEDACOS_HORIZONTAL][PEDACOS_VERTICAL];
  ALLEGRO_BITMAP* imagem[5][2];
};

Escudo* inicializa_escudo( int posicao_x, int posicao_y );

bool colide_escudo(Escudo* escudo, Missil* missil);

void desenha_escudo( Escudo* escudo );

int get_top_escudo ( Escudo* escudo);

void destroi_topo_escudo (Escudo* escudo);

Escudo* finaliza_escudo( Escudo *escudo );

#endif