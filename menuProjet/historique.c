#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "historique.h"

#include "type.h"

void initHistorique(Boutique *b) {
    b->historique.operations = NULL;
    b->historique.nbOperations = 0;
    b->historique.capaciteOperations = 0;
}

void ajouterOperation(Boutique *b,const char *type, const char *description) {
    Historique *h = &b->historique;   // raccourci

    // 1. agrandir le tableau s'il est plein
    if (h->nbOperations == h->capaciteOperations) {
        int nouvelleCapacite;

        if (h->capaciteOperations == 0) {
            nouvelleCapacite = 10;
        } else {
            nouvelleCapacite = h->capaciteOperations * 2;
        }

        Operation *tmp = realloc(h->operations, nouvelleCapacite * sizeof(Operation));
        if (tmp == NULL) {
            printf("Erreur d'allocation memoire\n");
            return;
        }
        h->operations = tmp;
        h->capaciteOperations = nouvelleCapacite;
    }

    // 2. remplir la nouvelle operation
    Operation op;

    strncpy(op.type, type, sizeof(op.type) - 1);
    op.type[sizeof(op.type) - 1] = '\0';

    strncpy(op.description, description, sizeof(op.description) - 1);
    op.description[sizeof(op.description) - 1] = '\0';

    // date du jour
    time_t maintenant = time(NULL);
    struct tm *t = localtime(&maintenant);
    op.date.jour = t->tm_mday;
    op.date.mois = t->tm_mon + 1;       // tm_mon va de 0 a 11
    op.date.annee = t->tm_year + 1900;  // tm_year compte depuis 1900

    // 3. ranger l'operation dans le tableau
    h->operations[h->nbOperations] = op;
    h->nbOperations++;
}

// Affiche toutes les operations, de la plus ancienne a la plus recente
void afficherHistorique(Boutique *b) {
    Historique *h = &b->historique;

    if (h->nbOperations == 0) {
        printf("Historique vide\n");
        return;
    }

    for (int i = 0; i < h->nbOperations; i++) {
        printf("[%02d/%02d/%04d] %s : %s\n",
               h->operations[i].date.jour,
               h->operations[i].date.mois,
               h->operations[i].date.annee,
               h->operations[i].type,
               h->operations[i].description);
    }
}

// A appeler a la fin du programme
void libererHistorique(Boutique *b) {
    free(b->historique.operations);
    b->historique.operations = NULL;
    b->historique.nbOperations = 0;
    b->historique.capaciteOperations = 0;
}
