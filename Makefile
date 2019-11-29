all: jeu client server

jeu: jeu.o
	gcc -o jeu jeu.o

client: client.o
	gcc -o client client.o

server: server.o
	gcc -o server server.o

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c -Werror

client.o: client.c
	gcc -o client.o -c client.c -Werror 

server.o: server.c 
	gcc -o server.o -c server.c -Werror 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf client
	rm -rf server
	rm -rf jeu
