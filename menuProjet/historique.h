
#ifndef SHOPFLOW_HISTORIQUE_H
#define SHOPFLOW_HISTORIQUE_H

#include "type.h"

void initHistorique(Boutique *b);
void ajouterOperation(Boutique *b, const char *type, const char *description);
void afficherHistorique(Boutique *b);
void libererHistorique(Boutique *b);

#endif //SHOPFLOW_HISTORIQUE_H
