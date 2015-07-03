/* O jogo Space Invaders
 *
 * Autores: Felipe de Barros, João Felipe Porto e Rafael Katopodis
 * Data de entrega: 03/07/2015
 */

#include "jogo.h"

int main(){
	Jogo jogo;

	inicializa_jogo(&jogo);

	main_loop_jogo(&jogo);

	destroi_jogo(&jogo);

	return 0;
}