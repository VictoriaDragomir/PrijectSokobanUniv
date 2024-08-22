CC = gcc
#CHEMIN
IPATH = include
LPATH = levels
SRCPATH = src
BPATH = build

CFLAGS += -Wall -Wextra -std=c11
LDFLAGS += -lm -L/opt/homebrew/lib -lSDL2 -lSDL2main -v
CPPFLAGS = -Iinclude -I/opt/homebrew/include
CIBLE = sokoban

OBJETS = $(BPATH)/grid.o $(BPATH)/player.o $(BPATH)/sdl2.o $(BPATH)/main.o

$(CIBLE): $(OBJETS)
	$(CC) $(OBJETS) -o $(CIBLE) $(LDFLAGS)

all: compileLIB sokoban

sokoban: $(BPATH)/grid.o $(BPATH)/player.o $(BPATH)/sdl2.o $(BPATH)/main.o
	gcc -o sokoban main.o grid.o player.o sdl2.o $(LDFLAGS)

$(BPATH)/grid.o: grid.c grid.h
	mkdir -p build
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

$(BPATH)/player.o: player.c player.h
	mkdir -p build
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

$(BPATH)/sdl2.o: $(SRCPATH)/sdl2.c $(SRCPATH)/sdl2.h
	mkdir -p build
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

$(BPATH)/main.o: main.c
	mkdir -p build
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

clean:
	rm -rf *.o sokoban html install_dir *.tar.gz

doc:
	doxygen Doxyfile

config:
	cd SDL2 && ./configure --prefix=$(PWD)/../install_dir
	cd SDL2 && make install -j6

archive:
	tar -cJvf ZABETIAN_Hanieh__Dragomir_Victoria.tar.gz *.c *.h *.txt Makefile README.md Doxyfile main.c grid.c grid.h player.h level1.txt src SDL2

sdl2: ./$(CIBLE) --sdl2
console: ./$(CIBLE) --console