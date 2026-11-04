#ifndef SHOPFLOW_COMMANDES_H
#define SHOPFLOW_COMMANDES_H
#include "type.h"

void ajouterLigne(Boutique *b, int num_commande);
void supprimerLigne(Boutique *b, int num_commande, char des[60]);
void creerCommande(Boutique *b);
void changerStatut(Boutique *b, int num_commande);
void afficherCommande(Boutique *b);
void annulerCommande(Boutique *b, int num_commande);

#endif //SHOPFLOW_COMMANDES_H
