#include "lists_chains.h"

/* Fonctions de gestion de CellPoint. */

CellPoint *CreateCellPoint (double x, double y) 
{
  CellPoint *cellReturn = NULL;
  cellReturn = (CellPoint *) malloc (sizeof(CellPoint));

  if (!cellReturn) { fprintf(stderr, "Error IO.\n"); exit(1); }
  else {
    cellReturn->x = x;
    cellReturn->y = y;
    cellReturn->suivant = NULL;
  }

  return cellReturn;
}

CellPoint *AddCellPoint (double x, double y, CellPoint **listePremier, CellPoint *listeDernier)
{
  CellPoint *cellReturn = CreateCellPoint (x, y);

  if (!(*listePremier)) { *listePremier = cellReturn; return cellReturn; }
  else {
    listeDernier->suivant = cellReturn;
    return cellReturn;
  }
}

void FreeCellPoint (CellPoint *liste)
{
  if (liste) {
    CellPoint *temporaire = liste->suivant;
    free(liste);
    FreeCellPoint (temporaire);
  }
}

/* Fonctions de gestion de CellChaine. */

CellChaine *CreateCellChaine (int numero, CellPoint *points)
{
  CellChaine *cellReturn = (CellChaine *) malloc (sizeof(CellChaine));

  if (!cellReturn) { fprintf(stderr, "Error IO.\n"); exit(1); }
  else {
    cellReturn->numero = numero;
    cellReturn->points = points;
    cellReturn->suivant = NULL;
  }

  return cellReturn;
}

CellChaine *AddCellChaine (int numero, CellPoint *points, CellChaine **listePremier, CellChaine *listeDernier)
{
  CellChaine *cellReturn = CreateCellChaine(numero, points);

  if (!(*listePremier)) { *listePremier = cellReturn; return cellReturn; }
  else {
    listeDernier->suivant = cellReturn;
    return cellReturn;
  }
}

void FreeCellChaine (CellChaine *liste)
{
  if (liste){
    CellChaine *temporaire = liste->suivant;
    FreeCellPoint(liste->points);
    free(liste);
    FreeCellChaine(temporaire);
  }
}

/* Fonctions de gestion de Chaines. */

Chaines *CreateChaines (int gamma, int nbChaines, CellChaine *liste)
{
  Chaines * chaineReturn = (Chaines *) malloc (sizeof(Chaines));
  
  if (!chaineReturn) { fprintf(stderr, "Error IO.\n"); exit(1); }
  else {
    chaineReturn->gamma = gamma;
    chaineReturn->nbChaines = nbChaines;
    chaineReturn->chaines = liste;
  }

  return chaineReturn;
}

void FreeChaines (Chaines *liste)
{
  FreeCellChaine (liste->chaines);
  free(liste);
}
