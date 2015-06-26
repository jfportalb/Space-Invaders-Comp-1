lall: jogo.o escudo.o alien.o missil.o tanque.o buffer.o space.c
	g++ space.c jogo.o escudo.o alien.o missil.o tanque.o buffer.o -o space -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
buffer.o: buffer.c
	g++ -c buffer.c
jogo.o: jogo.c
	g++ -c jogo.c 
escudo.o: escudo.c
	g++ -c escudo.c
alien.o: alien.c
	g++ -c alien.c
missil.o: missil.c
	g++ -c missil.c
tanque.o: tanque.c
	g++ -c tanque.c
clean:
	rm -f jogo.o escudo.o alien.o missil.o tanque.o vetor.o buffer.o