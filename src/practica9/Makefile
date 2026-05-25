cflags = -std=c99 -O2 -arch arm64
dflags = -std=c99 -g
includes = -I ../iostring -I ../structures/Hash -I ../structures/nodos -I ../structures/heap -I ../structures/pila -I ../structures/arbol
libs = ../../lib -liostring -lHash -lHeap -lPila -lArbol
source = $(wildcard *.c)
output = ../../bin/practica9

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run :
	$(output)
rebuild:
	make -C ..\iostring
	make -C ..\structures\nodos
	make -C ..\structures\arbol
	make -C ..\structures\heap
	make -C ..\structures\pila
	make -C ..\structures\Hash
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
