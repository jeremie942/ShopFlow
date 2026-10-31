
#ifndef SHOPFLOW_COMMANDES_H
#define SHOPFLOW_COMMANDES_H
#include "type.h"
#include "commandes.c"

void creerCommande(Boutique *b);
void ajouterLigne();
void supprimerLigne();
void changerStatut();
void annulerCommande();
void afficherCommande();

#endif //SHOPFLOW_COMMANDES_H