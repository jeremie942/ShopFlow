#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include <time.h>
#include <string.h>

void ajouterLigne(Boutique *b, int num_commande) {
    int client = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    Commande *nv_cmd = &b->clients[client].commandes[commande];
    // afficherCatalogue(&b);
    printf("Veuillez entrez l'objet que vous voulez acheter: ");
    char des[60];
    int trouve=0,nb=0;
    fgets(des, sizeof(des), stdin);
    des[strcspn(des, "\n")] = '\0';
    for (int i=0; i<b->nbProduits; i++) {
        if (strcmp(des, b->produits[i].designation) == 0 && trouve==0)
        {
            trouve=1;
            do
            {
                printf("Combient en voulez vous en acheter? (max: %d): ",b->produits[i].quantiteStock);
                scanf("%d", &nb);
            } while (nb > b->produits[i].quantiteStock || nb ==0);
            if (nb != 0) {
                if (nv_cmd->capaciteLignes >= nv_cmd->nbLignes) {
                    realloc(nv_cmd->lignes, sizeof(LigneCommande)*nv_cmd->nbLignes+1);
                }
                strcpy(nv_cmd->lignes[nv_cmd->nbLignes].refProduit, b->produits[i].reference);
                strcpy(nv_cmd.lignes[nv_cmd.nbLignes].designation, b->produits[i].designation);
                nv_cmd.lignes[nv_cmd.nbLignes].quantite = nb;
                nv_cmd.lignes[nv_cmd.nbLignes].prixUnitaireHT = b->produits[i].prixUnitaireHT;
                nv_cmd.lignes[nv_cmd.nbLignes].sousTotalHT = b->produits[i].prixUnitaireHT*nb;
                nv_cmd.nbLignes++;
                printf("Votre article a bien été ajouter à voitre commande.");
            }
        }
    }
    if (trouve==0)
    {
        printf("Le produit que vous avez demander n'existe pas.");
    }
}

void creerCommande(Boutique *b) {
    int id,trouve=0;
    int i;
    printf("Veuillez entrez l'id du client: ");
    scanf("%d", &id);
    for (i=0; i<b->nbClients; i++) {
        if (id == b->clients[i].idClient) {
            trouve=1;
            break;
        }
    }
    if (trouve==1) {
        if (b->clients[i].nbCommandes == b->clients[i].capaciteCommandes) {
            b->clients[i].capaciteCommandes++;
            b->clients[i].commandes = realloc(b->clients[i].commandes, sizeof(Commande)*b->clients[i].capaciteCommandes);
        }
        Commande *nv_commande = &b->clients[i].commandes[b->clients[i].nbCommandes];
        //ID de la commande
        nv_commande->idClient = id;
        //Numéro de la commande
        nv_commande->numero = nv_commande->idClient*100 + b->clients[i].nbCommandes + 1;
        // Date de création de la commande
        time_t maintenant;
        struct tm *date;
        time(&maintenant);
        date = localtime(&maintenant);
        nv_commande->dateCommande.jour = date->tm_mday;
        nv_commande->dateCommande.mois = date->tm_mon+1;
        nv_commande->dateCommande.annee = date->tm_year+1900;
        //Statut de la commande
        strcpy(nv_commande->statut, "EN_COURS");
        // Ajout des lignes pour la nouvelle commande
        nv_commande->nbLignes = 0;
        nv_commande->capaciteLignes = 5;
        int fin=0;
        do
        {
            printf("Pour ajouter un produit à votre liste entrez 1 sinon 0: ");
            scanf(" %d", &fin);
            if (fin == 1)
            {
                printf("test0");
                ajouterLigne(b, id);
                printf("test");
            }
        }while (fin == 1);
        nv_commande->lignes = (LigneCommande*) malloc(sizeof(LigneCommande)*nv_commande->capaciteLignes);
        // Initialisation des prix, remsies etc...
        nv_commande->montantBrutHT = 0;
        nv_commande->tauxRemise = 0;
        nv_commande->montantRemise = 0;
        nv_commande->montantHT = 0;
        nv_commande->montantTVA = 0;
        nv_commande->montantTTC = 0;
        nv_commande->fraisPort = 5.90;
        // Adresse de livraison
        strcpy(nv_commande->adresseLivraison.rue,  b->clients[i].adresse.rue);
        strcpy(nv_commande->adresseLivraison.ville,  b->clients[i].adresse.ville);
        strcpy(nv_commande->adresseLivraison.codePostal,  b->clients[i].adresse.codePostal);
        strcpy(nv_commande->adresseLivraison.pays,  b->clients[i].adresse.pays);
        printf("Une commande vide à bien été créer pour %s %s", b->clients[i].nom, b->clients[i].prenom);
        b->clients[i].nbCommandes++;
    } else {
        printf("L'id que vous avez rentrer est invalide");
    }
}

void changerStatut(Boutique *b, int num_commande) {
    int client = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    if (strcmp(b->clients[client].commandes[commande].statut, "EN_COURS") == 0) {
        strcpy(b->clients[client].commandes[commande].statut, "EXPEDIEE");
    }else if (strcmp(b->clients[client].commandes[commande].statut, "EXPEDIEE") == 0) {
        strcpy(b->clients[client].commandes[commande].statut,"LIVREE");
    }
}