/* Versão 0.2 do jogo Space Invaders
 *
 * Autor: João Felipe Porto de Albuquerque
 * Data: 25/06/2015
 */

#include "jogo.h"

int main(){
	Jogo jogo;

	inicializa_jogo(&jogo);

	main_loop_jogo(&jogo);

	destroi_jogo(&jogo);

	return 0;
}