#include "IO_network.h"

int main (void)
{
  FILE *fichier = fopen("../res/00014_burma.res", "r");
  Reseau *reseauTemporaire;
  CellNoeud *parcoursNoeuds, *parcoursVoisins;
  CellCommodite *parcoursCommo;
  int compteCable;

  reseauTemporaire = lectureReseau(fichier);

  fclose(fichier);

  printf("*********** AFFICHAGE DES NOEUDS **************\n");
  parcoursNoeuds = reseauTemporaire->noeuds;
  while (parcoursNoeuds) {
    printf("Noeud numero : %d, valeurs : %.2lf, %.2lf\n", parcoursNoeuds->courant->num, parcoursNoeuds->courant->x, parcoursNoeuds->courant->y);
    parcoursVoisins = parcoursNoeuds->courant->voisins;
    while (parcoursVoisins) {
      printf("\tNoeud numero : %d, valeurs : %.2lf, %.2lf\n", parcoursVoisins->courant->num, parcoursVoisins->courant->x, parcoursVoisins->courant->y);
      parcoursVoisins = parcoursVoisins->suivant;
    }
    parcoursNoeuds = parcoursNoeuds->suivant;
  }
  printf("\n*********** AFFICHAGE DES COMMODITES ************\n");
  parcoursCommo = reseauTemporaire->commodites;
  while (parcoursCommo){
    printf("Les noeuds de la commodite : %d, %d\n", parcoursCommo->extrA->num, parcoursCommo->extrB->num);
    parcoursCommo = parcoursCommo->suivant;
  }
  
  compteCable = CompteCable(reseauTemporaire);
  printf("\n************** COMPTAGE DES CABLES **************\nLe reseau comporte %d cables.\n", compteCable);
  
  printf("\n************** ECRITURE DANS UN FICHIER *********\n");
  fichier = fopen("resultat.res", "w");
  ecrireReseauTxt(reseauTemporaire, fichier);
  fclose(fichier);

  afficheReseauGnuplot(reseauTemporaire, "00014_burma_res");

  printf("Done.\n");
  return 0;
}
