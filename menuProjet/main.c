/* ==========================================================================
 * menu.c - Squelette de demarrage pour tester le projet (XTI101)
 * --------------------------------------------------------------------------
 * BUT : un programme qui COMPIL ET TOURNE en 1 commande, des le premier jour.
 *
 *
 * CONTENU : navigation complete (4 sous-menus) + bouchons [STUB] pour
 * chaque fonctionnalite. Vous devez changer les stubs,
 * un par un, par leurs vraies fonctions ecrites dans leurs modules :
 *
 * Le cycle de travail (à répéter pour chaque fonctionnalité)
 * Copy1. CHOISIR une fonctionnalité du menu           (ex. « ajouter un produit »)
 * 2. ÉCRIRE la fonction dans son module           (produit.c)
 * 3. DÉCLARER le prototype dans son header        (produit.h)
 * 4. INCLURE le header dans menu_rapide.c         (#include "produit.h")
 * 5. SUPPRIMER le stub correspondant              (la ligne [STUB] ajouterProduit)
 * 6. RECOMPILER et tester
 *
 * ========================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "client.h"
#include "produit.h"
#include "commandes.h"
#include "historique.h"
#include "statistique.h"
#include "initialisation.h"


/* --------------------------------------------------------------------------
 * Lecture d'un choix au clavier (version simple, suffisant pour demarrer).
 * A remplacer plus tard par une saisie securisee (module utils.c).
 * -------------------------------------------------------------------------- */
static int lireChoix(void)
{
    int choix;
    printf("  Votre choix : ");
    if (scanf("%d", &choix) != 1)
    {
        exit(EXIT_FAILURE); /* entree fermee : on quitte proprement */
    }
    return choix;
}

/* ==========================================================================
 * SOUS-MENUS : un seul motif a retenir, applique 4 fois.
 * Pour ajouter une fonctionnalite : un printf + un case + la borne max.
 * ========================================================================== */

static void menuProduits(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES PRODUITS =====\n");
        printf("  1. Ajouter un produit\n");
        printf("  2. Modifier un produit\n");
        printf("  3. Supprimer un produit\n");
        printf("  4. Afficher le catalogue\n");
        printf("  0. Retour au menu principal\n");
        choix = lireChoix();

        switch (choix)
        {
            case 1: ajouterProduit(b);    break;
            case 2: modifierProduit(b);   break;
            case 3: supprimerProduit(b);  break;
            case 4: afficherCatalogue(b); break;
            case 5: searchProduit(b);     break;
            case 0:                       break; /* retour automatique */
            default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);
}

static void menuClients(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES CLIENTS =====\n");
        printf("  1. Ajouter un client\n");
        printf("  2. Modifier un client\n");
        printf("  3. Supprimer un client\n");
        printf("  4. Afficher la liste des clients\n");
        printf("  5. Affichage d'un client \n");
        printf("  0. Retour au menu principal\n");
        choix = lireChoix();

        switch (choix)
        {
            case 1: ajouterClient(b);        break;
            case 2: mettreaJourClient(b);       break;
            case 3: supprimerClient(b);      break;
            case 4: afficherListe(b); break;
            case 5: afficherClient(b); break;
            case 0:                         break;
            default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);
}

static void menuCommandes(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES COMMANDES =====\n");
        printf("  1. Creer une commande\n");
        printf("  2. Afficher une commande\n");
        printf("  0. Retour au menu principal\n");
        choix = lireChoix();

        switch (choix)
        {
            case 1: creerCommande(b);       break;
            case 2: afficherCommande(b); break;
            case 0:                        break;
            default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);
}

static void menuStatistiques(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== STATISTIQUES =====\n");
        printf("  1. Chiffre d'affaires global\n");
        printf("  2. Palmares des produits \n");
        printf("  3. Palmares des clients\n");
        printf("  4. Verification des stocks\n");
        printf("  0. Retour au menu principal\n");
        choix = lireChoix();

        switch (choix)
        {
            case 1: chiffreDAfaire(b); break;
            case 2: palmaresProduits(b); break;
            case 3: palmaresClients(b); break;
            case 4: alerteStock(b); break;
            case 0:                            break;
            default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);
}

static void menuHistorique(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== Historique =====\n");
        printf("  1. Afficher l'historique\n");
        printf("  0. Retour au menu principal\n");
        choix = lireChoix();
        switch (choix)
        {
        case 1: afficherHistorique(b); break;
        case 0:                            break;
        default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);
}

/* ==========================================================================
 * PROGRAMME PRINCIPAL
 * ========================================================================== */
int main(void)
{
    int choix;
    Boutique b;
    initialiserDonneesTest(&b);

    printf("==============================================\n");
    printf("  SHOPFLOW - Boutique en ligne (squelette)\n");
    printf("==============================================\n");

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("  1. Gestion des produits\n");
        printf("  2. Gestion des clients\n");
        printf("  3. Gestion des commandes\n");
        printf("  4. Statistiques\n");
        printf("  5. Historique des actions\n");
        printf("  0. Quitter\n");
        choix = lireChoix();

        switch (choix)
        {
            case 1: menuProduits(&b);     break;
            case 2: menuClients(&b);      break;
            case 3: menuCommandes(&b);    break;
            case 4: menuStatistiques(&b); break;
            case 5: menuHistorique(&b);   break;
            case 0: printf("\n  Au revoir !\n"); break;
            default: printf("  [!] Choix invalide.\n"); break;
        }
    } while (choix != 0);

    return EXIT_SUCCESS;
}