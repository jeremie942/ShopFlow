#include "initialisation.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"


void initialiserDonneesTest(Boutique *b) {
    /* 1. Catalogue : allocation dynamique de 10 emplacements */
    strcpy(b->nom,"ShopFlow");
    b->capaciteProduits = 10;
    b->produits = (Produit *)malloc(b->capaciteProduits * sizeof(Produit));
    if (b->produits == NULL) { /* ... gestion d'erreur ... */ }
    b->nbProduits = 0;
    Produit modele[] = {
        {"PRD-0001", "Clavier mecanique",  "Informatique",  79.90,  42, 10, 1},
        {"PRD-0002", "Souris sans fil",    "Informatique",  24.50,   8, 15, 1},
        {"PRD-0003", "Ecran 27 pouces",    "Informatique", 199.00,   6,  5, 1},
        {"PRD-0004", "Casque audio",       "Audio",         89.90,  25, 10, 1},
        {"PRD-0005", "Enceinte Bluetooth", "Audio",         59.90,  12,  8, 1},
        {"PRD-0006", "Cable HDMI 2 m",     "Accessoires",    9.90, 120, 30, 1},
        {"PRD-0007", "Hub USB-C 7 ports",  "Accessoires",   49.90,   4, 10, 1},
        {"PRD-0008", "Disque SSD 1 To",    "Stockage",     109.00,  18,  6, 1}
    };
    for (int i = 0; i < 8; i++)
        b->produits[b->nbProduits++] = modele[i];

    /* 2. Clients : allocation dynamique de 8 emplacements */
    b->capaciteClients = 8;
    b->clients = (Client *)malloc(b->capaciteClients * sizeof(Client));
    if (b->clients == NULL) { /* ... gestion d'erreur ... */ }
    b->nbClients = 0;
    Client modelo[] = {
        {1, "Pierre", "Jean", "pierre.jean@gmail.com", "0765854987",
            {"1 rue Victor Hugo", "Paris", "75001", "France"},
            0, 0, 0, NULL, 1},

        {2, "Martin", "Sophie", "sophie.martin@gmail.com", "0612345678",
            {"12 avenue des Fleurs", "Lyon", "69000", "France"},
            0, 0, 0, NULL, 1},

        {3, "Durand", "Lucas", "lucas.durand@gmail.com", "0623456789",
            {"8 rue du Port", "Marseille", "13000", "France"},
            0, 0, 0, NULL, 1},

        {4, "Bernard", "Emma", "emma.bernard@gmail.com", "0634567890",
            {"15 boulevard Central", "Toulouse", "31000", "France"},
            0, 0, 0, NULL, 1},

        {5, "Petit", "Nathan", "nathan.petit@gmail.com", "0645678901",
            {"22 rue des Écoles", "Nantes", "44000", "France"},
            0, 0, 0, NULL, 1},

        {6, "Robert", "Julie", "julie.robert@gmail.com", "0656789012",
            {"5 place de la Gare", "Lille", "59000", "France"},
            0, 0, 0, NULL, 1}
    };
    for (int j = 0;j < 8; j++)
        b->clients[b->nbClients++] = modelo[j];

}
/* Liberation complete : une seule fuite memoire est sanctionnee */
void detruireBoutique(Boutique *b)
{
    for (int i = 0; i < b->nbClients; i++) {
        for (int j = 0; j < b->clients[i].nbCommandes; j++)
            free(b->clients[i].commandes[j].lignes);
        free(b->clients[i].commandes);
    }
    free(b->clients);
}


void afficherBoutique(Boutique *b)
{
    printf("Nom: %s\n",b->nom);
    for (int i=0; i<b->nbProduits; i++) {
        printf("Produit %d : reference: %s, designation: %s, categorie: %s, prix: %.2f, quantite: %d, suil d'alerte: %d, actif: %d\n",i,b->produits[i].reference,b->produits[i].designation,b->produits[i].categorie,b->produits[i].prixUnitaireHT,b->produits[i].quantiteStock,b->produits[i].sueilAlerte,b->produits[i].actif);
    }
    printf("nb produit: %d\n",b->nbProduits);
    printf("capacite produits: %d\n",b->capaciteProduits);

    for (int j=0; j<b->capaciteProduits; j++) {
        printf("id: %d, nom: %s, prenom: %s, email: %s, telephone: %s, Adresse rue: %s, ville: %s, code: %s, pays: %s, point de fidelite: %d, nb commandes: %d, capacite commande: %d, commandes: a faire plus tard, actif: %d\n",b->clients[j].idClient,b->clients[j].nom,b->clients[j].prenom,b->clients[j].email,b->clients[j].telephone,b->clients[j].adresse.rue,b->clients[j].adresse.ville,b->clients[j].adresse.codePostal,b->clients[j].adresse.pays,b->clients[j].pointsFidelite,b->clients[j].nbCommandes,b->clients[j].actif);
    }
    printf("nb client: %d\n",b->nbClients);
    printf("capacite client: %d\n",b->capaciteClients);
    printf("numero suivant: %d\n",b->numeroSuivant);
    printf("id client suivant: %d\n",b->idClientSuivant);
}

int main()
{
    Boutique b;
    initialiserDonneesTest(&b);
    afficherBoutique(&b);
    return 0;
}