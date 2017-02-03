#include "gestion_tree.h"
#include "IO_chains.h"
#include "IO_network.h"

int main(void)
{
  Chaines *chainePourReseau;
  Reseau *reseauReconstitue;
  FILE *fichier = fopen("../cha/00014_burma.cha", "r");
  
  printf("************** CREER UNE LISTE DE CHAINES *****************\n");
  chainePourReseau = lectureChaine (fichier);
  printf("Liste de chaines creee.\n\n");
  printf("**************** RECONSTITUER UN RESEAU *******************\n");
  reseauReconstitue = recreeReseauArbre(chainePourReseau);
  printf("Reseau reconstitue.\n\n");
  printf("*********** AFFICHAGE DU RESEAU RECONSTITUE ***************\n");
  afficheReseauGnuplot(reseauReconstitue, "./00014_burma_tree");
  printf("Affichage du reseau effectue.\n\n");
  
  return 0;
}
