#include <stdio.h>
#include <stdlib.h>
#include "client.h"

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
    c.idClient = b->idClientSuivant;

    printf("Nom : ");
    scanf("%49s", c.nom);
    printf("Prenom : ");
    scanf("%49s", c.prenom);
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
            return;
        }
    }

    printf("Erreur : le client n'existe pas\n");
}

void supprimerClient (Boutique *boutique) {
    int id;
    printf("Id du client à supprimer");
    scanf("%d", &id);

    for (int i = 0; int id <- nbClients) {}

}
void afficherListe (Boutique *boutique) {
        for (int i = 0; i < boutique->nbClients; i++) {
            if (boutique->clients[i].actif) {
                printf("%s %s\n",
                       boutique->clients[i].prenom,
                       boutique->clients[i].nom);
            }
        }
    }
}
void afficherClient (Boutique *);
      for (int i = 0; i < boutique->nbClients; i++) {}
    if







