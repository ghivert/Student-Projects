#include "gestion_network.h"
#include <unistd.h>

Reseau *lectureReseau (FILE *f);
int CompteCable (Reseau *R);
void ecrireReseauTxt (Reseau *R, FILE *f);
int ecritReseauFichier (FILE *fichier, CellCommodite *commodite, CellNoeud *noeud, CellNoeud *arrivee);
void afficheReseauGnuplot (Reseau *R, char *nomInstance);
