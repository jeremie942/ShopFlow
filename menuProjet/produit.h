#ifndef SHOPFLOW_PRODUIT_H
#define SHOPFLOW_PRODUIT_H
#include "type.h"
#include "produit.c"

void ajouterProduit(Boutique *bout);
void modifierProduit(Boutique *bout);
void afficherCatalogue(Boutique *bout);
void rechercheMultiCriteres(Boutique *bout);
void searchProduit(Boutique *bout);
void supprimerProduit(Boutique *bout);
#endif //SHOPFLOW_PRODUIT_H
