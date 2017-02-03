#include <stdlib.h>
#include <stdio.h>

#ifndef __CHAINE_H__
#define __CHAINE_H__

typedef struct cellPoint {
  double x, y;
  struct cellPoint *suivant;
} CellPoint;

typedef struct cellChaine {
  int numero;
  CellPoint *points;
  struct cellChaine *suivant;
} CellChaine;

typedef struct {
  int gamma;
  int nbChaines;
  CellChaine *chaines;
} Chaines;

/* Fonctions de gestion de CellPoint. */
CellPoint *CreateCellPoint (double x, double y);
CellPoint *AddCellPoint (double x, double y, CellPoint **listePremier, CellPoint *listeDernier);
void FreeCellPoint (CellPoint *liste);

/* Fonctions de gestion de CellChaine. */
CellChaine *CreateCellChaine (int numero, CellPoint *points);
CellChaine *AddCellChaine (int numero, CellPoint *points, CellChaine **listePremier, CellChaine *listeDernier);
void FreeCellChaine (CellChaine *liste);

/* Fonctions de gestion de Chaines. */
Chaines *CreateChaines (int gamma, int nbChaines, CellChaine *liste);
void FreeChaines (Chaines *liste);

#endif
