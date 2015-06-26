#ifndef ESCUDO_H
#define ESCUDO_H

#define PEDACOS_HORIZONTAL 8
#define PEDACOS_VERTICAL 4 
#define TAMANHO_ESCUDO PEDACOS_HORIZONTAL*8

enum EstadoEscudo { INTEIRO, AVARIADO, DESTRUIDO };
enum LegoEscudo { QUADRADO, SUDESTE, NOROESTE, NORDESTE, SUDOESTE, VAZIO };

struct Escudo {
  int posicao_x, posicao_y;
  LegoEscudo desenho[PEDACOS_HORIZONTAL][PEDACOS_VERTICAL];
  EstadoEscudo pedaco[PEDACOS_HORIZONTAL][PEDACOS_VERTICAL];
  ALLEGRO_BITMAP* imagem[5][2];
};

Escudo* inicializa_escudo( int posicao_x, int posicao_y );

void acerta_escudo( Escudo* escudo);

void desenha_escudo( Escudo* escudo );

Escudo* finaliza_escudo( Escudo *escudo );

#endif