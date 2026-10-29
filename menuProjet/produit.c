//
// Created by ewenh on 29/10/2026.
//
#include <stdio.h>
#include "produit.h"
#include <stdlib.h>
struct Produit{
    char reference[12];
    char designation[60];
    char categorie[30];
    float prixUnitaireHT;
    int quantiteStock;
    int seuilAlerte;
    int actif;
};

produits Produit* malloc (sizeof(Produit));

void ajouterProduit(void) {


}