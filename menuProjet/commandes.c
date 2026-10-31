#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include <time.h>
#include <string.h>

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
        nv_commande->lignes = (LigneCommande*) malloc(sizeof(LigneCommande)*nv_commande->capaciteLignes);
        // Initialisation des prix remsies etc...
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