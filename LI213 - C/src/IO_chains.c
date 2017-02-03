#include "IO_chains.h"
#include <math.h>

/**
 * Lit un fichier .cha et retourne une structure Chaines remplie. 
 *
 * @param f
 * Le fichier à lire.
 */
Chaines *lectureChaine (FILE *f)
{
  char junk[256];
  int i, j; int nbChaines, gamma; int numChaine, nombrePoints;
  double x, y;
  CellPoint *listePoints = NULL, *listePointsDernier = NULL; 
  CellChaine *listeChaines = NULL, *listeChainesDernier = NULL;
  Chaines *chaineReturn = NULL;
  fscanf(f, "%s %d\n", junk, &nbChaines);
  fscanf(f, "%s %d\n", junk, &gamma);
  
  for (i = 0 ; i < nbChaines ; i++) {
    fscanf(f, "%d %d ", &numChaine, &nombrePoints);
    for (j = 0 ; j < nombrePoints ; j++) {
      fscanf(f, "%lf %lf ", &x, &y);
      listePointsDernier = AddCellPoint(x, y, &listePoints, listePointsDernier);
    }
    listeChainesDernier = AddCellChaine(numChaine, listePoints, &listeChaines, listeChainesDernier);
    listePoints = NULL;
  }
  
  chaineReturn = CreateChaines(gamma, nbChaines, listeChaines);
  return chaineReturn;
}

/**
 * Crée un fichier .cha a partir d'une structure Chaines. 
 * 
 * @param C
 * La liste de chaînes à écrire.
 * @param f
 * Le fichier dans lequel écrire.
 */
void ecrireChaineTxt (Chaines *C, FILE *f)
{
  if (!f) { fprintf(stderr, "Error IO.\n"); exit(1); }
  CellChaine *parcoursChaines = C->chaines;
  CellPoint *parcoursPoints;
  int nombreDePoints = 0;
  fprintf(f, "NbChaines: %d\n", C->nbChaines);
  fprintf(f, "Gamma: %d\n", C->gamma);
  while (parcoursChaines) {
    fprintf(f, "%d ", parcoursChaines->numero);
    parcoursPoints = parcoursChaines->points;
    while (parcoursPoints) { 
      nombreDePoints++; 
      parcoursPoints = parcoursPoints->suivant; 
    }
    fprintf(f, "%d ", nombreDePoints);
    parcoursPoints = parcoursChaines->points;
    while (parcoursPoints) {
      fprintf (f, "%.2lf %.2lf ", parcoursPoints->x, parcoursPoints->y);
      parcoursPoints = parcoursPoints->suivant;
    }
    fprintf(f, "\n");
    parcoursChaines = parcoursChaines->suivant;
  }
}

/**
 * Prends une structure Chaines en argument et affiche 
 * toutes les chaines sur un graphique. 
 * Nécessite gnuplot sinon la fonction retourne une erreur. 
 *
 * @param C
 * La liste de chaînes.
 * @param nomInstance
 * Le fichier à écrire.
 */
void afficheChaineGnuplot (Chaines *C, char *nomInstance)
{
  FILE *fichier; char nomFichier[24], titre[24];
  CellChaine *parcoursChaines = C->chaines;
  CellPoint *parcoursPoints;
  int numero = 1, fichiersNum = 1;
  char *directory = getcwd(NULL, 0);

  while (parcoursChaines) {
    parcoursPoints = parcoursChaines->points;
    
    sprintf(nomFichier, "Chaines%d.txt", numero);
    numero++;
    
    fichier = fopen(nomFichier, "w");
    
    while (parcoursPoints) {
      fprintf (fichier, "%.2lf %.2lf\n", parcoursPoints->x, parcoursPoints->y);
      parcoursPoints = parcoursPoints->suivant;
    }
    fprintf(fichier, "\n");
    fclose(fichier);
    parcoursChaines = parcoursChaines->suivant;
  }

  fichier = fopen("config_gnuplot.plt", "w");
  fprintf(fichier, "set title \"%s\"\n", nomInstance);
  fprintf(fichier, "set xlabel \"X\"\n");
  fprintf(fichier, "set ylabel \"Y\"\n");
  fprintf(fichier, "set grid\n");
  fprintf(fichier, "unset key\n\n");
  fprintf(fichier, "set terminal png\n");
  fprintf(fichier, "set output \"%s/%s.png\"\n\n", directory, nomInstance);
  
  sprintf(nomFichier, "Chaines%d.txt", fichiersNum);
  sprintf(titre, "Chaine %d", fichiersNum);
  fichiersNum++;
  fprintf(fichier, "plot \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1, \\\n", directory, nomFichier, titre);

  while (fichiersNum < (numero -1)) {
    sprintf(nomFichier, "Chaines%d.txt", fichiersNum);
    sprintf(titre, "Chaine %d", fichiersNum);
    fichiersNum++;
    fprintf(fichier, "     \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1, \\\n", directory, nomFichier, titre);
  }
  sprintf(nomFichier, "Chaines%d.txt", fichiersNum);
  sprintf(titre, "Chaine %d", fichiersNum);
  fichiersNum++;
  fprintf(fichier, "     \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1\n", directory, nomFichier, titre);
  fclose(fichier);
  free(directory);

  system("gnuplot < config_gnuplot.plt");
}

/**
 * Calcule la longueur d'une chaine. 
 *
 * @param c
 * La chaîne dont on doit calculer la longueur.
 * @return La longueur de la chaîne.
 */
double longueurChaine (CellChaine *c)
{
  CellPoint *parcoursPoints = c->points;
  double Xa = parcoursPoints->x, Ya = parcoursPoints->y, Xb, Yb;
  double resultat =  0;
  if (parcoursPoints->suivant) parcoursPoints = parcoursPoints->suivant;
  while (parcoursPoints) {
    Xb = parcoursPoints->x; Yb = parcoursPoints->y;
    resultat += sqrt((pow((Xb - Xa), 2) + pow((Yb - Ya), 2)));
    Xa = Xb; Ya = Yb;
    parcoursPoints = parcoursPoints->suivant;
  }
  return resultat;
}

/**
 * Calcul la longueur cumulée de toutes les chaînes d'une structure Chaines. 
 *
 * @param C
 * La liste des chaînes dont on doit connaître la longueur.
 * @return La longueur cumulée de toutes les chaînes.
 */
double longueurTotale (Chaines *C)
{
  CellChaine *parcoursChaines = C->chaines;
  double resultat = 0;

  while (parcoursChaines) {
    resultat += longueurChaine(parcoursChaines);
    parcoursChaines = parcoursChaines->suivant;
  }
  return resultat;
}

/**
 * Compte tous les points d'une structure Chaines. 
 * 
 * @param C
 * La liste des chaînes dont on veut le nombre de points.
 * @return Le nombre de points de la structure.
 */
int comptePointsTotal (Chaines *C)
{
  int resultat = 0;
  CellChaine *parcoursChaines = C->chaines;
  if (!parcoursChaines) { printf("Il n'y a pas de chaines !\n"); return 0; }
  CellPoint *parcoursPoints;

  while (parcoursChaines) {
    parcoursPoints = parcoursChaines->points;
    while (parcoursPoints) {
      resultat += 1;
      parcoursPoints = parcoursPoints->suivant;
    }
    parcoursChaines = parcoursChaines->suivant;
  }
  return resultat;
}
