CC = g++ 
CFLAGS= -std=c++17 -Wall -g -pedantic  #options de compilations en C++
LDFLAGS= None #options de l'édition de liens
EXEC = maze  

$@ : nom de la cible 
$< : nom de la première dépendance
$^ : liste des dépendances
$? : liste des dépendances plsu récentes que la cible 
$* : nom du fichier sans suffixe

-pedantic : warn on language extensions 
-w : suppress all warning
-Wall : show all warnings
-o <filename> :compiles and links files into an executable named <filename>
-g :provides debugging features for program
   
all: $(EXEC)

hello:hello.o main.o
	$(CC) -o $@ $^ 

hello.o :hello.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o : main.cpp hello.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean : 
	rm -rf *.o hello

mrproper : clearn
	rm -rf $(EXEC) 
