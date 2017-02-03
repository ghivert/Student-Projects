#include "gestion_network.h"
#include "lists_chains.h"
#include "gestion_network.h"

#ifndef __HASH_T__
#define __HASH_T__

typedef struct hachage {
  CellNoeud **tableauPointeursCellNoeud;
  int taille;
} Hachage;

int clef (int x, int y);

int hachage (float k, int taille);

Noeud *rechercheCreeNoeudHachage(Reseau *R, Hachage *H, double x, double y);

Reseau *recreeReseauHachage(Chaines *C);

#endif
