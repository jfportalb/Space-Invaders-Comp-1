lall: jogo.o escudo.o alien.o missil.o tanque.o buffer.o menu.o botao.o wave.o space.c
	g++ space.c jogo.o escudo.o alien.o wave.o missil.o tanque.o buffer.o menu.o botao.o -o space -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
alien.o: alien.c
	g++ -c alien.c
botao.o: botao.c
	g++ -c botao.c
buffer.o: buffer.c
	g++ -c buffer.c
escudo.o: escudo.c
	g++ -c escudo.c
jogo.o: jogo.c
	g++ -c jogo.c
menu.o: botao.o menu.c
	g++ -c menu.c 
missil.o: missil.c
	g++ -c missil.c
tanque.o: tanque.c
	g++ -c tanque.c
wave.o: wave.c
	g++ -c wave.c
clean:
	rm -f jogo.o escudo.o alien.o missil.o tanque.o vetor.o buffer.o botao.o menu.o
git:
	git add --all
	git commit
	git push