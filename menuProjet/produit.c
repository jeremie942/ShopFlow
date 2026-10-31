#include "produit.h"
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include <string.h>

void ajouter_Produit(Boutique *bout) {
    if (bout->capaciteProduits <= bout->nbProduits) {
        bout->produits=realloc(bout->produits, (bout->nbProduits+1)*sizeof(Produit));
        bout->capaciteProduits++;
    }
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
            printf("Quel est la reference ?\n");
            fgets(ref, sizeof(ref), stdin);
            des[strcspn(ref, "\n")] = '\0';
            for (int i = 0; i < bout->nbProduits; i++) {
                if (strcmp(ref, bout->produits[i].reference) == 0){
                    test = 1;
                    printf("la reference est deja assigne, veuillez en donner une autre\n");
                }
            }
        }while (test == 1);

        printf("Appellation du produit ?\n");
        fgets(des, sizeof(des), stdin);
        des[strcspn(des, "\n")] = '\0';

        printf("Quelle est la categorie ?\n");
        fgets(cat, sizeof(cat), stdin);
        des[strcspn(des, "\n")] = '\0';
        printf("Quel est le prix a l'unite ?\n");
        scanf(" %f", &prix);

        printf("Quelle est la quantite actuelle ?\n");
        scanf(" %d", &qStock);

        printf("Quel est le seuil de reapprovisionnement ?\n");
        scanf(" %d", &sAlert);

        printf("Produit actif ? (0 ou 1)\n");
        scanf(" %d", &act);

        strcpy(bout->produits[bout->nbProduits].reference,ref);
        strcpy(bout->produits[bout->nbProduits].designation,des);
        strcpy(bout->produits[bout->nbProduits].categorie,cat);
        bout->produits[bout->nbProduits].prixUnitaireHT=prix;
        bout->produits[bout->nbProduits].quantiteStock = qStock;
        bout->produits[bout->nbProduits].sueilAlerte = sAlert;
        bout->produits[bout->nbProduits].actif = act;
        bout->nbProduits++;

}


void modifierProduit(Boutique *bout) {
    int index = -1;
    char ref[12];

    printf("Entrez la reference du produit a modifier : ");

    // Vider le buffer si un scanf précédent a laissé un \n (sécurité)
    int c;
    fgets(ref, sizeof(ref), stdin);
    ref[strcspn(ref, "\n")] = '\0'; // Supprimer le saut de ligne
    for (int i = 0; i < bout->nbProduits; i++) {
        if (strcmp(bout->produits[i].reference, ref) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("[!] Aucun produit ne possede la reference : %s\n", ref);
        return;
    }

    printf("\n--- Modification du produit : %s ---\n",bout->produits[index].designation);

    printf("Prix unitaire HT actuel (%.2f) - Nouveau prix : ", bout->produits[index].prixUnitaireHT);
    scanf(" %f", &bout->produits[index].prixUnitaireHT);

    printf("Quantite en stock actuelle (%d) - Nouvelle quantite : ", bout->produits[index].quantiteStock);
    scanf(" %d", &bout->produits[index].quantiteStock);

    printf("Seuil d'alerte actuel (%d) - Nouveau seuil : ", bout->produits[index].sueilAlerte);
    scanf(" %d", &bout->produits[index].sueilAlerte);

    printf("[+] Produit modifie avec succes !\n");
}