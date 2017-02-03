#include "lists_chains.h"
#include "IO_chains.h"

int main (void) 
{
  CellPoint *parcoursPoints;
  Chaines *secondTemp = NULL;
  CellChaine *parcoursChaines;
  double resultat; int retour;

  FILE *fichier = fopen ("../cha/00014_burma.cha", "r");

  secondTemp = lectureChaine (fichier);

  printf("******** AFFICHAGE DANS LE MAIN **********\n\n");
  parcoursChaines = secondTemp->chaines;
  while (parcoursChaines) {
    printf("%d ", parcoursChaines->numero);
    parcoursPoints = parcoursChaines->points;
    while (parcoursPoints) {
      printf ("%.2lf %.2lf ", parcoursPoints->x, parcoursPoints->y);
      parcoursPoints = parcoursPoints->suivant;
    }
    printf("\n");
    parcoursChaines = parcoursChaines->suivant;
  }
  printf("\n");
  fclose(fichier);

  fichier = fopen("rendu_chaine.cha", "w");
  ecrireChaineTxt (secondTemp, fichier);
  fclose(fichier);

  resultat = longueurChaine(secondTemp->chaines);
  printf("La longueur de la première chaine est : %f.\n", resultat);

  resultat = longueurTotale(secondTemp);
  printf("La longueur totale des chaines est : %f.\n", resultat);

  retour = comptePointsTotal(secondTemp);
  printf("Le nombre de points de l'instance est : %d.\n", retour);

  afficheChaineGnuplot(secondTemp, "00014_burma");
  return 0;
}
