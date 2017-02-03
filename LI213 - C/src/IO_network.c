#include "IO_network.h"

/**
 * Lit un réseau dans un fichier et le stocke dans la structure réseau.
 *
 * @param f
 * Fichier dans lequel est stocké le réseau.
 * @return Le réseau résultant.
 */
Reseau *lectureReseau (FILE *f)
{
  char junk[256], lettre;
  int nbNoeuds, gamma, numNoeud, i, noeud1, noeud2; double x, y;
  CellNoeud *listeNoeudsPremier = NULL, *parcoursNoeuds;
  Noeud *extrA, *extrB;
  CellCommodite *listeCommoPremier = NULL, *listeCommoDernier = NULL;

  fscanf(f, " %s %d", junk, &nbNoeuds);
  fscanf(f, " %s %d", junk, &gamma);
  
  for (i = 0 ; i < nbNoeuds ; i++) {
    fscanf(f, " %d %lf %lf", &numNoeud, &x, &y);
    listeNoeudsPremier = AddCellNoeud(CreateNoeud(numNoeud, x, y, NULL), listeNoeudsPremier);
  }
  
  while (fscanf(f, " %c %d %d", &lettre, &noeud1, &noeud2) != EOF) {
    if (lettre == 'a') {
      parcoursNoeuds = listeNoeudsPremier;
      while (parcoursNoeuds) {
	if (parcoursNoeuds->courant->num == noeud1) 
	  extrA = parcoursNoeuds->courant;
	if (parcoursNoeuds->courant->num == noeud2) 
	  extrB = parcoursNoeuds->courant;
	parcoursNoeuds = parcoursNoeuds->suivant;
      }
      extrA->voisins = AddCellNoeud(extrB, extrA->voisins);
      extrB->voisins = AddCellNoeud(extrA, extrB->voisins);
    }
    if (lettre == 'o') {
      parcoursNoeuds = listeNoeudsPremier;
      while (parcoursNoeuds) {
	if(parcoursNoeuds->courant) {
	  if (parcoursNoeuds->courant->num == noeud1) 
	    extrA = parcoursNoeuds->courant;
	  if (parcoursNoeuds->courant->num == noeud2) 
	    extrB = parcoursNoeuds->courant;
	}
	parcoursNoeuds = parcoursNoeuds->suivant;
      }
      listeCommoDernier = AddCellCommodite(extrA, extrB, &listeCommoPremier, listeCommoDernier);
    }
  }

  Reseau *reseauReturn = CreateReseau(nbNoeuds, gamma, listeNoeudsPremier, listeCommoPremier);

  return reseauReturn;
}

/**
 * Compte le nombre de câbles contenus dans un réseau.
 *
 * @param R
 * Le réseau duquel on compte le nombre de câbles.
 * @return Le nombre de cables du réseau.
 */
int CompteCable (Reseau *R)
{
  CellNoeud *parcoursNoeuds, *parcoursVoisins;
  int compteCable = 0;
  
  parcoursNoeuds = R->noeuds;
      while (parcoursNoeuds) {
	parcoursVoisins = parcoursNoeuds->courant->voisins;
	while (parcoursVoisins) {
	  if ((parcoursVoisins->courant->num) < (parcoursNoeuds->courant->num))
	    compteCable++;
	  parcoursVoisins = parcoursVoisins->suivant;
	}
	parcoursNoeuds = parcoursNoeuds->suivant;
      }
      return compteCable;
}

/**
 * Ecrit dans le réseau dans un fichier réseau .res.
 *
 * @param R
 * Le réseau à écrire.
 * @param f
 * Le fichier dans lequel écrire.
 */
void ecrireReseauTxt (Reseau *R, FILE *f)
{
  CellNoeud *parcoursNoeuds = R->noeuds, *parcoursVoisins;
  CellCommodite *parcoursCommodite;
  
  fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
  fprintf(f, "Gamma: %d\n\n", R->gamma);

  while (parcoursNoeuds) {
    fprintf(f, "%d %.2lf %.2lf\n", parcoursNoeuds->courant->num, parcoursNoeuds->courant->x, parcoursNoeuds->courant->y);
    parcoursNoeuds = parcoursNoeuds->suivant;
  }

  fprintf(f, "\n");
  parcoursNoeuds = R->noeuds;
  while (parcoursNoeuds) {
    parcoursVoisins = parcoursNoeuds->courant->voisins;
    while (parcoursVoisins) {
      if ((parcoursVoisins->courant->num) < (parcoursNoeuds->courant->num))
	fprintf(f, "a %d %d\n", parcoursVoisins->courant->num,  parcoursNoeuds->courant->num);
      parcoursVoisins = parcoursVoisins->suivant;
    }
    parcoursNoeuds = parcoursNoeuds->suivant;
  }

  fprintf(f, "\n");

  parcoursCommodite = R->commodites;
  while (parcoursCommodite) {
    if (parcoursCommodite->extrA && parcoursCommodite->extrB)
      fprintf(f, "o %d %d\n", parcoursCommodite->extrA->num, parcoursCommodite->extrB->num);
    parcoursCommodite = parcoursCommodite->suivant;
  }
}

/**
 * Prend un réseau en entrée et en fait un graphique représentant de manière visuelle un réseau.
 *
 * @param R
 * Le réseau que l'on doit représenter.
 * @param nomInstance
 * Le nom du fichier à créer.
 */
void afficheReseauGnuplot (Reseau *R, char *nomInstance)
{
  CellNoeud *parcoursNoeuds = R->noeuds, *noeudsVoisins;
  FILE *fichier; char titre[24];
  char nomFichier[256]; int numeroNoeud = 0, fichiersNum = 0;
  char *directory = getcwd(NULL, 0);
  
  while (parcoursNoeuds){
    noeudsVoisins = parcoursNoeuds->courant->voisins;
    while(noeudsVoisins){
      //if (parcoursNoeuds->courant->num <= noeudsVoisins->courant->num) {
	sprintf(nomFichier, "Noeud%d.txt", numeroNoeud++);
	fichier = fopen(nomFichier, "w");
	fprintf(fichier, "%.2lf %.2lf\n", 
		parcoursNoeuds->courant->x, 
		parcoursNoeuds->courant->y);
	fprintf(fichier, "%.2f %.2f\n", 
		noeudsVoisins->courant->x, 
		noeudsVoisins->courant->y);
	noeudsVoisins = noeudsVoisins->suivant;
	fclose(fichier);
	//}
    }
    parcoursNoeuds = parcoursNoeuds->suivant;
  }

  if (0 < 1) {
    fichier = fopen("config_gnuplot.plt", "w");
    fprintf(fichier, "set title \"%s\"\n", nomInstance);
    fprintf(fichier, "set xlabel \"X\"\n");
    fprintf(fichier, "set ylabel \"Y\"\n");
    fprintf(fichier, "set grid\n");
    fprintf(fichier, "unset key\n\n");
    fprintf(fichier, "set terminal png\n");
    fprintf(fichier, "set output \"%s/%s.png\"\n\n", directory, nomInstance);
  
    sprintf(nomFichier, "Noeud%d.txt", fichiersNum);
    sprintf(titre, "Noeud %d", fichiersNum);
    fichiersNum++;
    fprintf(fichier, "plot \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1, \\\n", directory, nomFichier, titre);
    
    while (fichiersNum < (numeroNoeud -1)) {
      sprintf(nomFichier, "Noeud%d.txt", fichiersNum);
      sprintf(titre, "Noeud %d", fichiersNum);
      fichiersNum++;
      fprintf(fichier, "     \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1, \\\n", directory, nomFichier, titre);
    }
    sprintf(nomFichier, "Noeud%d.txt", fichiersNum);
    sprintf(titre, "Noeud %d", fichiersNum);
    fichiersNum++;
    fprintf(fichier, "     \"%s/%s\" using 1:2 title \"%s\" with linespoint ls 1\n", directory, nomFichier, titre);
    fclose(fichier);
    free(directory);
    
    system("gnuplot < config_gnuplot.plt");
  }
}
