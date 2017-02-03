#include "gestion_network.h"

CellNoeud *CreateCellNoeud (Noeud *node)
{
  CellNoeud *cellReturn = (CellNoeud *) malloc (sizeof(CellNoeud));

  if (!cellReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }
  cellReturn->courant = node;
  cellReturn->suivant = NULL;
  return cellReturn;
}

CellNoeud *AddCellNoeud (Noeud *node, CellNoeud *listePremier)
{
  CellNoeud *cellReturn = CreateCellNoeud (node);
  if (!cellReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }

  if (!listePremier) return cellReturn;
  else {
    cellReturn->suivant = listePremier;
    return cellReturn;
  }
}


void FreeCellNoeud (CellNoeud *liste)
{
  CellNoeud *listeSuivant;
  if (liste) listeSuivant = liste->suivant;
  while (liste) {
    free(liste);
    liste = listeSuivant;
    listeSuivant = liste->suivant;
  }
}

CellCommodite *CreateCellCommodite (Noeud *nodeA, Noeud *nodeB)
{
  CellCommodite *cellReturn = (CellCommodite *) malloc (sizeof(CellCommodite));

  if (!cellReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }
  else {
    cellReturn->extrA = nodeA;
    cellReturn->extrB = nodeB;
    cellReturn->suivant = NULL;
    return cellReturn;
  }
}

CellCommodite *AddCellCommodite (Noeud *nodeA, Noeud *nodeB, CellCommodite **listePremier, CellCommodite *listeDernier)
{
  CellCommodite *cellReturn = CreateCellCommodite(nodeA, nodeB);
  if (!cellReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }

  if (!(*listePremier))  { *listePremier = cellReturn; return cellReturn; }
  else {
    listeDernier->suivant = cellReturn;
    return cellReturn;
  }
}

void FreeCellCommodite (CellCommodite *liste)
{
  CellCommodite *listeSuivant;
  if (liste) listeSuivant = liste->suivant;
  while (liste) {
    free(liste);
    liste = listeSuivant;
    listeSuivant = liste->suivant;
  }
}

Noeud *CreateNoeud (int num, double x, double y, CellNoeud *voisins)
{
  Noeud *nodeReturn = (Noeud *) malloc (sizeof(Noeud));

  if (!nodeReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }
  else {
    nodeReturn->num = num;
    nodeReturn->x = x;
    nodeReturn->y = y;
    nodeReturn->voisins = voisins;
    return nodeReturn;
  }
}

void FreeNoeud (Noeud *node)
{
  if (node) free(node);
}

Reseau *CreateReseau (int nbNoeuds, int gamma, CellNoeud *noeuds, CellCommodite *commodites)
{
  Reseau *reseauReturn = (Reseau *) malloc (sizeof(Reseau));

  if (!reseauReturn) { fprintf (stderr, "Memory Error.\n"); exit(1); }
  else {
    reseauReturn->nbNoeuds = nbNoeuds;
    reseauReturn->gamma = gamma;
    reseauReturn->noeuds = noeuds;
    reseauReturn->commodites = commodites;
    return reseauReturn;
  }
}

void FreeReseau (Reseau *reseau)
{
  if (reseau) free(reseau);
}
