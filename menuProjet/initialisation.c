#include "initialisation.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "produit.h"
#include "commandes.h"

void initialiserDonneesTest(Boutique *b) {
    /* 1. Catalogue : allocation dynamique de 10 emplacements */
    strcpy(b->nom,"ShopFlow");
    b->capaciteProduits = 8;
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
            0, 0, 5, NULL, 1},

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
    for (int j = 0;j < 6; j++)
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
    printf("\n=====================================\n");
    printf("          BOUTIQUE %s\n", b->nom);
    printf("=====================================\n");

    printf("\nNombre de produits : %d\n", b->nbProduits);
    printf("Capacite produits  : %d\n", b->capaciteProduits);

    printf("\n=========== PRODUITS ===========\n");

    for (int i = 0; i < b->nbProduits; i++)
    {
        Produit *p = &b->produits[i];

        printf("\nProduit %d\n", i + 1);
        printf("  Reference      : %s\n", p->reference);
        printf("  Designation    : %s\n", p->designation);
        printf("  Categorie      : %s\n", p->categorie);
        printf("  Prix HT        : %.2f €\n", p->prixUnitaireHT);
        printf("  Stock          : %d\n", p->quantiteStock);
        printf("  Seuil alerte   : %d\n", p->sueilAlerte);
        printf("  Actif          : %s\n",
               p->actif ? "Oui" : "Non");
    }

    printf("\n\n=========== CLIENTS ===========\n");

    for (int i = 0; i < b->nbClients; i++)
    {
        Client *c = &b->clients[i];

        printf("\n=====================================\n");
        printf("Client #%d\n", c->idClient);
        printf("=====================================\n");

        printf("Nom               : %s\n", c->nom);
        printf("Prenom            : %s\n", c->prenom);
        printf("Email             : %s\n", c->email);
        printf("Telephone         : %s\n", c->telephone);

        printf("Adresse :\n");
        printf("  Rue             : %s\n", c->adresse.rue);
        printf("  Ville           : %s\n", c->adresse.ville);
        printf("  Code postal     : %s\n", c->adresse.codePostal);
        printf("  Pays            : %s\n", c->adresse.pays);

        printf("Points fidelite   : %d\n", c->pointsFidelite);
        printf("Nb commandes      : %d\n", c->nbCommandes);
        printf("Capacite commande : %d\n", c->capaciteCommandes);
        printf("Actif             : %s\n",
               c->actif ? "Oui" : "Non");

        printf("\n------ COMMANDES ------\n");

        if (c->nbCommandes == 0)
        {
            printf("Aucune commande.\n");
        }
        else
        {
            for (int j = 0; j < c->nbCommandes; j++)
            {
                Commande *cmd = &c->commandes[j];

                printf("\n-------------------------------------\n");
                printf("Commande %d\n", j + 1);
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
                        printf("    Prix HT       : %.2f €\n", ligne->prixUnitaireHT);
                        printf("    Sous-total HT : %.2f €\n", ligne->sousTotalHT);
                    }
                }
            }
        }
    }

    printf("\n\n=========== STATISTIQUES ===========\n");
    printf("Nombre clients    : %d\n", b->nbClients);
    printf("Capacite clients  : %d\n", b->capaciteClients);
    printf("Numero suivant    : %d\n", b->numeroSuivant);
    printf("ID suivant client : %d\n", b->idClientSuivant);
    printf("=====================================\n");

}

int main()
{
    Boutique b;
    initialiserDonneesTest(&b);
    afficherBoutique(&b);
    creerCommande(&b);
    afficherBoutique(&b);
    return 0;
}