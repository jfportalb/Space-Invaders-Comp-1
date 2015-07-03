#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define N_SAMPLES 9

typedef void (*Funcao)( void*);

enum SAMPLES {
	SHOOT, TANQUE_EXPLOSION, ALIEN_MOVE_1, 
	ALIEN_MOVE_2, ALIEN_MOVE_3, ALIEN_MOVE_4, 
	ALIEN_EXPLOSION, UFO_HIGHPITCH, UFO_LOWPITCH
};

struct SOUND_MANAGER{
	bool mudo;
	float volume;
	ALLEGRO_SAMPLE* sample[N_SAMPLES];
	ALLEGRO_SAMPLE_ID* sample_id;
};

SOUND_MANAGER* inicializa_sound_manager();

void toggle_sound_state(void* ptr);
void rise_sound_volume(void* ptr);
void low_sound_volume(void* ptr);

void play_sound(SOUND_MANAGER *sound, SAMPLES sample);

SOUND_MANAGER* finaliza_sound_manager(SOUND_MANAGER* sound);

#endif