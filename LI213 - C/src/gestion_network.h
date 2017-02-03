#include <stdlib.h>
#include <stdio.h>

#ifndef __RESEAU_H__
#define __RESEAU_H__

/* Liste chainee de noeuds. */
typedef struct cellNoeud {
  struct noeud *courant;
  struct cellNoeud *suivant;
} CellNoeud;
  
/* Liste chainee de commodites. */
typedef struct cellCommodite {
  struct noeud *extrA, *extrB;
  struct cellCommodite *suivant;
} CellCommodite;

/* Noeud du reseau. */ 
typedef struct noeud {
  int num;
  double x, y;
  struct cellNoeud *voisins;
} Noeud;

/* Un reseau. */
typedef struct {
  int nbNoeuds;
  int gamma;
  struct cellNoeud *noeuds;
  struct cellCommodite *commodites;
} Reseau;

CellNoeud *CreateCellNoeud (Noeud *node);
CellNoeud *AddCellNoeud (Noeud *node, CellNoeud *listePremier);
void FreeCellNoeud (CellNoeud *liste);

CellCommodite *CreateCellCommodite (Noeud *nodeA, Noeud *nodeB);
CellCommodite *AddCellCommodite (Noeud *nodeA, Noeud *nodeB, CellCommodite **listePremier, CellCommodite *listeDernier);
void FreeCellCommodite (CellCommodite *liste);

Noeud *CreateNoeud (int num, double x, double y, CellNoeud *voisins);
void FreeNoeud (Noeud *node);

Reseau *CreateReseau (int nbNoeuds, int gamma, CellNoeud *noeuds, CellCommodite *commodites);
void FreeReseau (Reseau *reseau);

#endif
