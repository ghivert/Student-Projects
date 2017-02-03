#include "gestion_network.h"
#include "lists_chains.h"

#ifndef __ARBRE_QUAT_H__
#define __ARBRE_QUAT_H__

typedef struct arbreQuat {
  double xc, yc;
  double coteX;
  double coteY;
  Noeud *noeud;
  struct arbreQuat *so;
  struct arbreQuat *se;
  struct arbreQuat *no;
  struct arbreQuat *ne;
} ArbreQuat ;

void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax);
ArbreQuat *creerArbreQuat(double xc, double yc, double coteX, double coteY);
ArbreQuat *insererNoeudArbre(Noeud *n, ArbreQuat *a, ArbreQuat *parent);
Noeud *chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent);
Reseau *recreeReseauArbre (Chaines *C);

#endif
