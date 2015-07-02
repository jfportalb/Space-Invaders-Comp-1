#ifndef ALIEN_H
#define ALIEN_H
 
#define ALIEN_SPEED 10
#define ALIEN_SIZE 36
 
#include <allegro5/allegro.h>
 
enum ALIEN_TYPE {
    SQUID, JELLYFISH, CRAB
};
struct alien{
    int troca_sprite;
    int x, y;
    ALIEN_TYPE alien_type;
    ALLEGRO_BITMAP* imagem_1;
    ALLEGRO_BITMAP* imagem_2;
};
 
alien* create_alien(int x, int y, ALIEN_TYPE type);
 
//Tem esse tipo de retorno para que retorne NULL a um dado ponteiro, o que é usado como teste condicional em funções de wave
alien* destroy_alien(struct alien* obj);
 
void explode_alien(struct alien* obj);
 
void move_alien_left(struct alien* obj);
 
void move_alien_right(struct alien* obj);
 
void move_alien_down(struct alien* obj);
 
void draw_alien(struct alien* obj);
 
void anima_alien(struct alien* obj);
 
void move_alien_horizontal(struct alien* obj, int speed);
 
void move_alien_baixo(struct alien* obj, int speed);

bool acerta_alien(struct alien* obj, int x, int y);
 
//Troca o sprite de um dado alien pelo sprite de explosão por um dado tempo antes de chamar destroy_alien()
void explode_alien(struct alien* obj);
 
#endif