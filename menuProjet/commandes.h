#ifndef SHOPFLOW_COMMANDES_H
#define SHOPFLOW_COMMANDES_H
#include "type.h"
#include "commandes.c"

void creerCommande(Boutique *b); // ne pas oublier d'afficher les produits avant chaque ajout de nouveau produits --> plus lisible
void ajouterLigne(Boutique *b, int num_commande);
void supprimerLigne(Boutique *b, int num_commande, char des[60]);
void changerStatut(Boutique *b, int num_commande);
void annulerCommande();
void afficherCommande();

#endif //SHOPFLOW_COMMANDES_H