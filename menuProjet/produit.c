
#include <stdio.h>
#include "produit.h"
#include <stdlib.h>
#include "type.h"
#include <string.h>
Produit modele[] = {
    {"PRD-0001", "Clavier mecanique", "Informatique", 79.90, 42, 10, 1},
    {"PRD-0002", "Souris sans fil", "Informatique", 24.50, 8, 15, 1},
    {"PRD-0003", "Ecran 27 pouces", "Informatique", 199.00, 6, 5, 1},
    {"PRD-0004", "Casque audio", "Audio", 89.90, 25, 10, 1},
    {"PRD-0005", "Enceinte Bluetooth", "Audio", 59.90, 12, 8, 1},
    {"PRD-0006", "Cable HDMI 2 m", "Accessoires", 9.90, 120, 30, 1},
    {"PRD-0007", "Hub USB-C 7 ports", "Accessoires", 49.90, 4, 10, 1},
    {"PRD-0008", "Disque SSD 1 To", "Stockage", 109.00, 18, 6, 1}
};
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