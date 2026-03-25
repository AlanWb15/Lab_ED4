
cflags = -Wall -Werror -std=c99 -O2 -arch arm64
dflags = -Wall -Werror -std=c99 -g

includes = -I ../iostring -I ../structures/nodos -I ../structures/lista

libs = ../../lib -liostring -lLista

source = $(wildcard *.c)

output = ../../bin/practica1

build:
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo " Compilacion Exitosa!"

rebuild:
	make -C ../iostring
	make -C ../structures/nodos
	make -C ../structures/lista
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo " Recompilacion Completa Exitosa!"
debug:
	gcc $(dflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo " Compilacion DEBUG Exitosa!"
clean:
	rm -f $(output)
	@echo "Ejecutable eliminado."

run: build
	$(output)


run-debug: debug
	$(output)

.PHONY: build rebuild debug clean run run-debug
