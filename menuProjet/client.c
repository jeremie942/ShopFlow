#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "client.h"

#include "historique.h"

void ajouterClient (Boutique *b) {
    if (b->nbClients == b->capaciteClients) {
        int nouvelleCapacite;
        if (b->capaciteClients == 0) {
            nouvelleCapacite = 10;
        } else {
            nouvelleCapacite = b->capaciteClients * 2;
        }
        Client *tmp = realloc(b->clients, nouvelleCapacite * sizeof(Client));
        if (tmp == NULL) {
            printf("Erreur d'allocation memoire\n");
            return;
        }
        b->clients = tmp;
        b->capaciteClients = nouvelleCapacite;
    }
    Client c;
    c.idClient = b->nbClients+1;
    char nom[48], prenom[48];
    printf("Nom : ");
    scanf("%49s", nom);
    strcpy(c.nom, nom);
    printf("Prenom : ");
    scanf("%49s", c.prenom);
    strcpy(c.prenom, nom);
    printf("Email : ");
    scanf("%79s", c.email);
    printf("Telephone : ");
    scanf("%14s", c.telephone);
    printf("Rue : ");
    scanf(" %79[^\n]", c.adresse.rue);
    printf("Ville : ");
    scanf(" %49[^\n]", c.adresse.ville);
    printf("Code postal : ");
    scanf("%5s", c.adresse.codePostal);
    printf("Pays : ");
    scanf(" %49[^\n]", c.adresse.pays);

    char description[100];
    snprintf(description, sizeof(description), "Nom: %s, Prenom: %s", nom, prenom);
    ajouterOperation(b, "Nouveau client", description);

    c.pointsFidelite = 0;
    c.nbCommandes = 0;
    c.capaciteCommandes = 0;
    c.commandes = NULL;
    c.actif = 1;

    b->clients[b->nbClients] = c;
    b->nbClients++;
    b->idClientSuivant++;
}

void mettreaJourClient (Boutique *b) {
    int id;
    printf("Id du client a modifier : ");
    scanf("%d", &id);

    for (int i = 0; i < b->nbClients; i++) {
        if (b->clients[i].idClient == id) {
            printf("Nouvel email : ");
            scanf("%79s", b->clients[i].email);

            printf("Nouveau telephone : ");
            scanf("%14s", b->clients[i].telephone);

            printf("Nouvelle rue : ");
            scanf(" %79[^\n]", b->clients[i].adresse.rue);

            printf("Nouvelle ville : ");
            scanf(" %49[^\n]", b->clients[i].adresse.ville);

            printf("Nouveau code postal : ");
            scanf("%5s", b->clients[i].adresse.codePostal);

            printf("Nouveau pays : ");
            scanf(" %49[^\n]", b->clients[i].adresse.pays);

            printf("Client mis a jour\n");

            char description[100];
            snprintf(description, sizeof(description), "Nom: %s, Prenom: %s", b->clients[i].nom, b->clients[i].prenom);
            ajouterOperation(b, "Nouveau client", description);
            return;
        }
    }

    printf("Erreur : le client n'existe pas\n");
}

void supprimerClient (Boutique *b) {
    int id;
    printf("Id du client a supprimer: ");
    scanf("%d", &id);

    for (int i = 0; i < b->nbClients; i++) {
        if (b->clients[i].idClient == id) {
            char description[100];
            snprintf(description, sizeof(description), "Nom: %s, Prenom: %s", b->clients[i].nom, b->clients[i].prenom);
            ajouterOperation(b, "Nouveau client", description);
            free(b->clients[i].commandes);

            for (int j = i; j < b->nbClients - 1; j++) {
                b->clients[j+1].idClient--;
                b->clients[j] = b->clients[j + 1];
            }
            b->nbClients--;
            printf("Client supprime\n");
            return;
        }
    }
    printf("Erreur : le client n'existe pas\n");
}
void afficherListe (Boutique *boutique) {
    if (boutique->nbClients == 0) {
        printf("Aucun client dans la boutique\n");
        return;
    }

    for (int i = 0; i < boutique->nbClients; i++) {
        printf("Client %d : %s %s\n",
               boutique->clients[i].idClient,
               boutique->clients[i].prenom,
               boutique->clients[i].nom);
        printf("  Email : %s\n", boutique->clients[i].email);
        printf("  Telephone : %s\n", boutique->clients[i].telephone);
        printf("  Adresse : %s, %s %s, %s\n",
               boutique->clients[i].adresse.rue,
               boutique->clients[i].adresse.codePostal,
               boutique->clients[i].adresse.ville,
               boutique->clients[i].adresse.pays);
        int somme = 0;
        for (int j = 0; j < boutique->clients[i].nbCommandes; j++)
        {
            somme+= boutique->clients[i].commandes[j].montantHT;
        }
        printf("Chiffre d'afaire genere par le client: %d euros \n\n",somme);
    }
}

void afficherClient (Boutique *boutique) {
    int id;
    printf("Id du client a afficher : ");
    scanf("%d", &id);

    for (int i = 0; i < boutique->nbClients; i++) {
        if (boutique->clients[i].idClient == id) {
            Client *c = &boutique->clients[i];
            printf("Client %d : %s %s\n", c->idClient, c->prenom, c->nom);
            printf("  Email : %s\n", c->email);
            printf("  Telephone : %s\n", c->telephone);
            printf("  Adresse : %s, %s %s, %s\n",
                   c->adresse.rue,
                   c->adresse.codePostal,
                   c->adresse.ville,
                   c->adresse.pays);
            printf("  Points de fidelite : %d\n", c->pointsFidelite);
            printf("  Nombre de commandes : %d\n", c->nbCommandes);
            if (c->actif == 1) {
                printf("  Statut : actif\n");
            } else {
                printf("  Statut : inactif\n");
            }
            if (c->nbCommandes == 0) {
                break;
            }
            else {
                for (int j = 0; j < c->nbCommandes; j++) {
                    Commande *cmd = &c->commandes[j];
                    printf("Commande %d\n", j + 1);
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

                    if (cmd->nbLignes == 0) {
                        printf("  Aucune ligne.\n");
                    }
                    else {
                        for (int k = 0; k < cmd->nbLignes; k++) {
                            LigneCommande *ligne = &cmd->lignes[k];

                            printf("\n  Ligne %d\n", k + 1);
                            printf("    Reference     : %s\n", ligne->refProduit);
                            printf("    Designation   : %s\n", ligne->designation);
                            printf("    Quantite      : %d\n", ligne->quantite);
                            printf("    Prix HT       : %.2f\n", ligne->prixUnitaireHT);
                            printf("    Sous-total HT : %.2f\n\n", ligne->sousTotalHT);
                        }
                    }
                }
                return;
            }
        }
        printf("Erreur : le client n'existe pas\n");
    }
}
