
#ifndef SHOPFLOW_COMMANDES_H
#define SHOPFLOW_COMMANDES_H
#include "type.h"
#include "commandes.c"

void creerCommande(Boutique *b);
void ajouterLigne(Boutique *b, int num_commande);
void supprimerLigne(Boutique *b, int num_commande);
void changerStatut(Boutique *b, int num_commande);
void annulerCommande();
void afficherCommande();

#endif //SHOPFLOW_COMMANDES_H