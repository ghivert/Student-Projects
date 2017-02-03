CC = clang
CPPFLAGS = -Wall
CFLAGS =
LIB = -lm

SRC_CHA = main_lists_chains.c lists_chains.c IO_chains.c
SRC_RES = gestion_network.c IO_network.c main_gestion_network.c
SRC_HASH = hash_table.c main_hash_table.c
SRC_AQR = gestion_tree.c main_gestion_tree.c

OBJECTS_CHA = $(SRC_CHA:.c=.o)
OBJECTS_RES = $(SRC_RES:.c=.o)
OBJECTS_HASH = $(SRC_HASH:.c=.o)
OBJECTS_AQR = $(SRC_AQR:.c=.o)

all: Chaines Reseau Hachage ArbreQuat

Chaines: $(OBJECTS_CHA)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LIB) $^ -o $@

Reseau: $(OBJECTS_RES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

Hachage: $(OBJECTS_HASH) lists_chains.o gestion_network.o IO_chains.o IO_network.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LIB) $^ -o $@

ArbreQuat: $(OBJECTS_AQR) lists_chains.o gestion_network.o IO_chains.o IO_network.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LIB) $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

lib: libchained_lists.a
libchained_lists.a: chained_lists.o
	ar cru libchained_lists.a chained_lists.o
	ranlib libchained_lists.a

clean: 
	$(RM) $(OBJECTS_CHA) Chaines Chaines*.txt *.png config_gnuplot.plt rendu_chaine.cha
	$(RM) $(OBJECTS_RES) Reseau Noeud*.txt resultat.res
	$(RM) $(OBJECTS_HASH) Hachage
	$(RM) $(OBJECTS_AQR) ArbreQuat

.PHONY: all clean lib
