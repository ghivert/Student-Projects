#include "hash_table.h"
#include <math.h>
#define A ((sqrt(5) - 1)/2)

/**
 * Calcule la clé du point en fonction des coordonnées.
 *
 * @param x
 * Abscisse du point.
 * @param y
 * Ordonné du point.
 * @return Clé du point.
 */
int clef (int x, int y)
{
  return (y + ((x + y)*(x + y + 1)/2));
}

/**
 * Calcule la clé de la table de hachage.
 * 
 * @param k
 * Clé du point.
 * @param taille
 * Taille de la table de hachage.
 * @return Clé de la table de hachage.
 */
int hachage (float k, int taille)
{
  return (int) (taille*(k*A - (int) (k*A)));
}

/**
 * Cherche un noeud dans la table de hachage et le retourne. Si le noeud n'existe pas dans la
 * table, la fonction crée le noeud, l'ajoute à la table et la retourne.
 *
 * @param R
 * Réseau dans lequel on cherche le point.
 * @param H
 * Table de hachage dans lequel on cherche le point.
 * @param x
 * Abscisse du point recherché.
 * @param y
 * Ordonné du point recherché.
 * @return Noeud recherché.
 */
Noeud *rechercheCreeNoeudHachage(Reseau *R, Hachage *H, double x, double y)
{
  Noeud *noeud;
  CellNoeud *parcoursNoeuds;
  int num = hachage(clef(x, y), H->taille);
  
  parcoursNoeuds = H->tableauPointeursCellNoeud[num];
  while (parcoursNoeuds) {
    if (parcoursNoeuds->courant->x == x && parcoursNoeuds->courant->y == y)
      break;
    parcoursNoeuds = parcoursNoeuds->suivant;
  }
  if (parcoursNoeuds)
    return parcoursNoeuds->courant;
  noeud = CreateNoeud(num, x, y, NULL);
  H->tableauPointeursCellNoeud[num] = AddCellNoeud(noeud, H->tableauPointeursCellNoeud[num]);
  return noeud;
}

/**
 * Fonction qui recrée un réseau à partir d'une liste de chaînes.
 *
 * @param C
 * Listes de chaînes à partir de laquelle on recrée le réseau.
 * @return Réseau recréé à partir de la liste de chaînes.
 */
Reseau *recreeReseauHachage(Chaines *C)
{
  CellChaine *parcoursChaines = C->chaines; CellNoeud *parcoursCellNoeud;
  CellPoint *parcoursPoints; Noeud *noeudReturn, *noeudVoisin, *noeudCommo1;
  Reseau *reseauReturn = CreateReseau(0, 0, NULL, NULL);
  Hachage *tableHachage = (Hachage *) malloc (sizeof(Hachage));
  int i;
  tableHachage->taille = 1000;
  tableHachage->tableauPointeursCellNoeud = \
    (CellNoeud **) malloc (tableHachage->taille*sizeof(CellNoeud *));
  CellCommodite *commoditeDernier = reseauReturn->commodites, *commoditePremier = NULL;
  while (parcoursChaines) {
    parcoursPoints = parcoursChaines->points;
    noeudReturn = rechercheCreeNoeudHachage(reseauReturn,   \
					    tableHachage,	 \
					    parcoursPoints->x,	 \
					    parcoursPoints->y);
    noeudCommo1 = noeudReturn;
    while (parcoursPoints) {
      noeudReturn = rechercheCreeNoeudHachage(reseauReturn, \
					      tableHachage, \
					      parcoursPoints->x, \
					      parcoursPoints->y);
      if (parcoursPoints->suivant) {
	noeudVoisin = rechercheCreeNoeudHachage(reseauReturn,		\
						tableHachage,		\
						parcoursPoints->suivant->x, \
						parcoursPoints->suivant->y);
	noeudVoisin->voisins = AddCellNoeud (noeudReturn, noeudVoisin->voisins);
	noeudReturn->voisins = AddCellNoeud (noeudVoisin, noeudReturn->voisins);
      }
      parcoursPoints = parcoursPoints->suivant;
    }
    commoditeDernier = AddCellCommodite(noeudCommo1, noeudReturn, &commoditePremier, commoditeDernier);
    commoditeDernier->extrB = noeudReturn;
    parcoursChaines = parcoursChaines->suivant;
  }
  for (i = 0 ; i < tableHachage->taille ; i++) {
    parcoursCellNoeud = tableHachage->tableauPointeursCellNoeud[i];
    while (parcoursCellNoeud) {
      reseauReturn->noeuds = AddCellNoeud(parcoursCellNoeud->courant, \
					  reseauReturn->noeuds);
      reseauReturn->nbNoeuds++;
      parcoursCellNoeud = parcoursCellNoeud->suivant;
    }
  }
  reseauReturn->commodites = commoditePremier;
  reseauReturn->gamma = C->gamma;
  return reseauReturn;
}
