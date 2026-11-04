#include "statistique.h"
#include <stdio.h>
#include <string.h>

void chiffreDAfaire(Boutique *b) {
    float montant = 0;
    for (int i=0; i< b->nbClients; i++)
    {
        for (int j=0; j<b->clients[i].nbCommandes; j++)
        {
            montant+= b->clients[i].commandes[j].montantHT;
        }
    }
    printf("Le chiffre d'afaire est de: %.2f \n",montant);
}

void palmaresProduits(Boutique *b) {
    int quantites[b->nbProduits];
    for (int i = 0; i < b->nbProduits; i++) {
        quantites[i] = 0;
    }
    // On compte le nombre de ventes
    for (int i = 0; i < b->nbClients; i++) {
        for (int j = 0; j < b->clients[i].nbCommandes; j++) {
            Commande *cmd = &b->clients[i].commandes[j];
            if (strcmp(cmd->statut, "ANNULEE") != 0) {
                for (int k = 0; k < cmd->nbLignes; k++) {
                    for (int p = 0; p < b->nbProduits; p++) {
                        if (strcmp(cmd->lignes[k].refProduit,
                                   b->produits[p].reference) == 0) {
                            quantites[p] += cmd->lignes[k].quantite;
                            break;
                        }
                    }
                }
            }
        }
    }
    // Partie affichage des produits
    printf("\n===== TOP 5 PRODUITS =====\n");
    for (int rang = 1; rang <= 5; rang++) {
        int meilleur = -1;
        for (int i = 0; i < b->nbProduits; i++) {
            if (quantites[i] >= 0 &&
                (meilleur == -1 ||
                 quantites[i] > quantites[meilleur])) {
                meilleur = i;
            }
        }
        if (meilleur == -1 || quantites[meilleur] == 0)
            break;
        printf("%d. %s : %d ventes\n",
               rang,
               b->produits[meilleur].designation,
               quantites[meilleur]);
        // Permet de ne pas afficher deux fois le meme produit
        quantites[meilleur] = -1;
    }
}

void palmaresClients(Boutique *b) {
    float ca[b->nbClients];
    // Calcul du chiffre d'afaire de chaque clients
    for (int i = 0; i < b->nbClients; i++) {
        ca[i] = 0;
        for (int j = 0; j < b->clients[i].nbCommandes; j++) {
            if (strcmp(b->clients[i].commandes[j].statut, "ANNULEE") != 0) {
                ca[i] += b->clients[i].commandes[j].montantHT;
            }
        }
    }
    // Partie affichage des clients
    printf("\n===== CLIENTS =====\n");
    for (int rang = 1; rang <= b->nbClients; rang++) {
        int meilleur = -1;
        for (int i = 0; i < b->nbClients; i++) {
            if (ca[i] >= 0 &&
                (meilleur == -1 || ca[i] > ca[meilleur])) {
                meilleur = i;
            }
        }
        if (meilleur == -1)
            break;
        printf("%d. %s %s : %.2f \n",
               rang,
               b->clients[meilleur].prenom,
               b->clients[meilleur].nom,
               ca[meilleur]);
        // Pour ne pas afficher deux fois le meme client
        ca[meilleur] = -1;
    }
}

void alerteStock(Boutique *b) {
    int trouve = 0;
    printf("\n===== ALERTES DE STOCK =====\n");
    for (int i = 0; i < b->nbProduits; i++) {
        if (b->produits[i].quantiteStock <= b->produits[i].sueilAlerte) {
            trouve = 1;
            printf("\nReference : %s\n",
                   b->produits[i].reference);
            printf("Designation : %s\n",
                   b->produits[i].designation);
            printf("Stock actuel : %d\n",
                   b->produits[i].quantiteStock);
            printf("Seuil d'alerte : %d\n",
                   b->produits[i].sueilAlerte);
        }
    }
    if (!trouve) {
        printf("Aucune alerte de stock.\n");
    }
}