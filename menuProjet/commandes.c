#include "type.h"
#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void ajouterLigne(Boutique *b, int num_commande) {
    int client = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    Commande *nv_cmd = &b->clients[client].commandes[commande];
    // afficherCatalogue(&b);
    printf("Veuillez entrez l'objet que vous voulez acheter: ");
    char des[60];
    int trouve = 0,nb = 0;
    getchar();
    fgets(des, sizeof(des), stdin);
    des[strcspn(des, "\n")] = '\0';
    for (int i=0; i<b->nbProduits; i++) {
        if (strcmp(des, b->produits[i].designation) == 0 && trouve == 0) {
            trouve = 1;
            do {
                printf("Combien en voulez vous en acheter? (max: %d): ", b->produits[i].quantiteStock);
                scanf("%d", &nb);
            } while (nb > b->produits[i].quantiteStock || nb == 0);
            if (nb != 0) {
                if (nv_cmd->capaciteLignes <= nv_cmd->nbLignes) {
                    nv_cmd->lignes = realloc(nv_cmd->lignes, sizeof(LigneCommande) * (nv_cmd->nbLignes + 1));
                }
                strcpy(nv_cmd->lignes[nv_cmd->nbLignes].refProduit, b->produits[i].reference);
                strcpy(nv_cmd->lignes[nv_cmd->nbLignes].designation, b->produits[i].designation);
                nv_cmd->lignes[nv_cmd->nbLignes].quantite = nb;
                b->produits[i].quantiteStock -= nb;
                nv_cmd->lignes[nv_cmd->nbLignes].prixUnitaireHT = b->produits[i].prixUnitaireHT;
                nv_cmd->lignes[nv_cmd->nbLignes].sousTotalHT = b->produits[i].prixUnitaireHT * nb;
                nv_cmd->nbLignes++;
                printf("Votre article a bien ete ajouter a votre commande.\n");
            }
        }
    }
    if (trouve == 0) {
        printf("Le produit que vous avez demander n'existe pas.");
    }
}

void supprimerLigne(Boutique *b, int num_commande, char des[60]) {
    int client = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    int indice = -1;
    Commande *cmd = &b->clients[client].commandes[commande];
    for (int j = 0; j < cmd->nbLignes; j++) {
        if (strcmp(cmd->lignes[j].designation, des) == 0) {
            indice = j;
            break;
        }
    }
    if (indice == -1) {
        printf("Produit introuvable\n");
        return;
    }
    b->produits[indice].quantiteStock += cmd->lignes[indice].quantite;
    for (int i = indice; i < cmd->nbLignes-1 ; i++) {
        cmd->lignes[i] = cmd->lignes[i+1];
    }
    cmd->nbLignes--;
}

void creerCommande(Boutique *b) {
    int id, trouve = 0;
    int i;
    printf("Veuillez entrez l'id du client: ");
    scanf("%d", &id);
    for (i = 0; i < b->nbClients; i++) {
        if (id == b->clients[i].idClient) {
            trouve = 1;
            break;
        }
    }
    if (trouve == 1) {
        if (b->clients[i].nbCommandes == b->clients[i].capaciteCommandes) {
            b->clients[i].capaciteCommandes++;
            b->clients[i].commandes = realloc(b->clients[i].commandes, sizeof(Commande)*b->clients[i].capaciteCommandes);
        }
        Commande *nv_commande = &b->clients[i].commandes[b->clients[i].nbCommandes];
        //ID de la commande
        nv_commande->idClient = id;
        //Numéro de la commande
        nv_commande->numero = nv_commande->idClient * 100 + b->clients[i].nbCommandes + 1;
        // Date de création de la commande
        time_t maintenant;
        struct tm *date;
        time(&maintenant);
        date = localtime(&maintenant);
        nv_commande->dateCommande.jour = date->tm_mday;
        nv_commande->dateCommande.mois = date->tm_mon + 1;
        nv_commande->dateCommande.annee = date->tm_year + 1900;
        //Statut de la commande
        strcpy(nv_commande->statut, "EN_COURS");
        // Ajout des lignes pour la nouvelle commande
        nv_commande->nbLignes = 0;
        nv_commande->capaciteLignes = 5;
        nv_commande->lignes = (LigneCommande*) malloc(sizeof(LigneCommande) * nv_commande->capaciteLignes);
        int fin = 0;
        do {
            //afficherCatalogue(b);
            printf("Pour ajouter un produit a votre liste entrez 1, pour suprimer un produit 2 sinon 0: ");
            scanf(" %d", &fin);
            if (fin == 1) {
                ajouterLigne(b, nv_commande->idClient*100 + b->clients[i].nbCommandes + 1);
            }
            if (fin == 2) {
                printf("Quel produit voulez vous retirer de la liste: ");
                getchar();
                char des[60];
                fgets(des, sizeof(des), stdin);
                des[strcspn(des, "\n")] = '\0';
                supprimerLigne(b, nv_commande->idClient*100 + b->clients[i].nbCommandes + 1, des);
            }
        } while (fin == 1 || fin == 2);
        // Initialisation des prix, remsies etc...
        int somme = 0;
        for (int i=0; i<nv_commande->nbLignes; i++) {
            somme+= nv_commande->lignes[i].sousTotalHT;
        }
        nv_commande->montantBrutHT = somme;
        if (somme < 100) {
            nv_commande->tauxRemise = 0;
        } else if (somme >= 100 && somme < 300) {
            nv_commande->tauxRemise = 5;
        } else if (somme >= 300 && somme < 600) {
            nv_commande->tauxRemise = 10;
        } else {nv_commande->tauxRemise = 15;}
        nv_commande->montantRemise = nv_commande->montantBrutHT * nv_commande->tauxRemise / 100;
        nv_commande->montantHT = nv_commande->montantBrutHT - nv_commande->montantRemise;
        nv_commande->montantTVA = nv_commande->montantHT * 20 / 100;
        if (nv_commande->montantHT >= 60) {
            nv_commande->fraisPort = 0;
        } else {nv_commande->fraisPort = 5.90;}
        nv_commande->montantTTC = nv_commande->montantHT + nv_commande->montantTVA + nv_commande->fraisPort;

        // Adresse de livraison
        strcpy(nv_commande->adresseLivraison.rue,  b->clients[i].adresse.rue);
        strcpy(nv_commande->adresseLivraison.ville,  b->clients[i].adresse.ville);
        strcpy(nv_commande->adresseLivraison.codePostal,  b->clients[i].adresse.codePostal);
        strcpy(nv_commande->adresseLivraison.pays,  b->clients[i].adresse.pays);
        printf("Une commande a bien ete creer pour %s %s", b->clients[i].nom, b->clients[i].prenom);
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


void afficherCommande(Boutique *b, int num_commande) {
    int id = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    Commande *cmd = b->clients[id].commandes;
    printf("\n-------------------------------------\n");
    printf("Commande %d\n", commande + 1);
    printf("-------------------------------------\n");

    printf("Numero            : %d\n", cmd->numero);
    printf("ID Client         : %d\n", cmd->idClient);

    printf("Date              : %02d/%02d/%04d\n",
    cmd->dateCommande.jour,
    cmd->dateCommande.mois,
    cmd->dateCommande.annee);

    printf("Statut            : %s\n", cmd->statut);

    printf("Montant brut HT   : %.2f \n", cmd->montantBrutHT);
    printf("Taux remise       : %.2f %%\n", cmd->tauxRemise);
    printf("Montant remise    : %.2f \n", cmd->montantRemise);
    printf("Montant HT        : %.2f \n", cmd->montantHT);
    printf("Montant TVA       : %.2f \n", cmd->montantTVA);
    printf("Montant TTC       : %.2f \n", cmd->montantTTC);
    printf("Frais de port     : %.2f \n", cmd->fraisPort);

    printf("\nAdresse livraison :\n");
    printf("  Rue             : %s\n", cmd->adresseLivraison.rue);
    printf("  Ville           : %s\n", cmd->adresseLivraison.ville);
    printf("  Code postal     : %s\n", cmd->adresseLivraison.codePostal);
    printf("  Pays            : %s\n", cmd->adresseLivraison.pays);

    printf("\nLignes de commande : %d\n", cmd->nbLignes);

    if (cmd->nbLignes == 0)
    {
        printf("  Aucune ligne.\n");
    }
    else
    {
        for (int k = 0; k < cmd->nbLignes; k++)
        {
            LigneCommande *ligne = &cmd->lignes[k];

            printf("\n  Ligne %d\n", k + 1);
            printf("    Reference     : %s\n", ligne->refProduit);
            printf("    Designation   : %s\n", ligne->designation);
            printf("    Quantite      : %d\n", ligne->quantite);
            printf("    Prix HT       : %.2f\n", ligne->prixUnitaireHT);
            printf("    Sous-total HT : %.2f\n", ligne->sousTotalHT);
        }
    }
}

void annulerCommande(Boutique *b, int num_commande) {
    int id = num_commande / 100 - 1;
    int commande = num_commande % 100 - 1;
    Commande *cmd = b->clients[id].commandes;
    if (strcmp(cmd->statut, "EN_COURS") == 0) {
        if (cmd->nbLignes > 0) {
            for (int i=0; i < cmd->nbLignes; i++) {
                for (int j=0; j < b->nbProduits; j++) {
                    if (strcmp(b->produits[j].designation, cmd->lignes[i].designation) == 0) {
                        b->produits[j].quantiteStock += cmd->lignes[i].quantite;
                        break;
                    }
                }
            }
            strcpy(cmd->statut, "ANNULEE");
            printf("Votre commande a bien ete annulee");
        }
    } else {
        printf("La commande n'existe pas");
    }
}