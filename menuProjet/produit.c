
#include <stdio.h>
#include "produit.h"
#include <stdlib.h>
#include "type.h"
#include <string.h>

void ajouterProduit(Boutique *bout) {
    if (bout->capaciteProduit > bout->nbProduits) {
        char ref[12];
        char des[60];
        char cat[30];
        float prix;
        int qStock;
        int sAlert;
        int act;
        int test;

        do {
            test = 0;
            printf("Quel est la référence ?\n");
            scanf("%s",&ref);
            for (int i = 0; i < bout->nbProduits; i++) {
                if (ref == bout->produits[i].reference) {
                    test = 1;
                    printf("la référence est déja assigné, veuillez en donner une autre\n");
                }
            }
        }while (test == 1);
        printf("Appelation du produit ?\n");
        scanf("%s",&des);
        printf("Quel est la catégorie ?\n");
        scanf("%s",&cat);
        printf("Quel est le prix a l'unité ?\n");
        scanf("%d",&prix);
        printf("Quel est la quantité actuelle ?\n");
        scanf("%d",&qStock);
        printf("Quel est le seuil de réapprovisionnement ?\n");
        scanf("%d",&sAlert);
        printf("Est-ce un produit actif ?\n");
        scanf("%d",&act);

        strcpy(bout->produits[bout->nbProduits].reference,ref);
        strcpy(bout->produits[bout->nbProduits].designation,res);
        strcpy(bout->produits[bout->nbProduits].categorie,cat);
        bout->produits[bout->nbProduits].prixUnitaireHT=prix;
        bout->produits[bout->nbProduits].quantiteStock = qStock;
        bout->produits[bout->nbProduits].sueilAlerte = sAlert;
        bout->produits[bout->nbProduits].actif = act;
        bout->nbProduits++;
    }
}