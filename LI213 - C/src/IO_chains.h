#include "lists_chains.h"
#include <unistd.h>
#include <math.h>

Chaines *lectureChaine (FILE *f);

/* Cree un fichier .cha a partir d'une structure Chaines. */
void ecrireChaineTxt (Chaines *C, FILE *f);

/* Prends une structure Chaines en argument et affiche 
   toutes les chaines sur un graphique. 
   NÈcessite gnuplot sinon la fonction retourne une erreur. */
void afficheChaineGnuplot (Chaines *C, char *nomInstance);

/* Calcul la longueur d'une chaine. */
double longueurChaine(CellChaine *c);

/* Calcul la longueur cumul√©e de toutes les chaines d'une structure Chaines. */
double longueurTotale (Chaines *C);

/* Compte tous les points d'une structure Chaines. */
int comptePointsTotal (Chaines *C);
