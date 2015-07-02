#include <stdio.h>
#include "alien.h"
#include <allegro5/allegro_image.h>
 
//Type is an integer between 0 and 2. Check the enum ALIEN_TYPE in alien.h
alien* create_alien(int x, int y, ALIEN_TYPE type) {
 
    struct alien* obj = (alien*) malloc(sizeof(alien));
    obj->alien_type = type;
 
    switch(obj->alien_type){
 
        case SQUID:
            obj->imagem_1 = al_load_bitmap("imagens/squid_1.png");
            obj->imagem_2 = al_load_bitmap("imagens/squid_2.png");
            break;
 
        case JELLYFISH:
            obj->imagem_1 = al_load_bitmap("imagens/jellyfish_1.png");
            obj->imagem_2 = al_load_bitmap("imagens/jellyfish_2.png");
            break;
 
        case CRAB:
            obj->imagem_1 = al_load_bitmap("imagens/crab_1.png");
            obj->imagem_2 = al_load_bitmap("imagens/crab_2.png");
            break;
 
    }
 
    if (!obj->imagem_1 || !obj->imagem_2){
        printf("Imagens não encontradas!\n");       
        exit(1);    
    }
 
    obj->x = x;
    obj->y = y;
    obj->troca_sprite = 1;
     
    return obj;
}
 
alien* destroy_alien(struct alien* obj) {
 
    al_destroy_bitmap(obj->imagem_1);
    al_destroy_bitmap(obj->imagem_2);
    free(obj);
    return NULL;
}
void move_alien_right(struct alien* obj) {
 
    obj->x+= ALIEN_SPEED;
}
void move_alien_left(struct alien* obj) {
 
    obj->x-= ALIEN_SPEED;
}
void move_alien_down(struct alien* obj) {
 
    obj->y+= ALIEN_SPEED;
}
void draw_alien(struct alien* obj) {
     
    if(obj->troca_sprite) {
         
        al_draw_bitmap(obj->imagem_1, obj->x, obj->y, 0);
    }
    else {
        al_draw_bitmap(obj->imagem_2, obj->x, obj->y, 0);
    }
}
void anima_alien(struct alien* obj) {
 
    obj->troca_sprite = obj->troca_sprite ? 0 : 1;
}
 
void move_alien_horizontal(struct alien* obj, int speed) {
 
    obj->x+= speed;
}
void move_alien_baixo(struct alien* obj, int speed) {
 
    obj->y += speed;
}