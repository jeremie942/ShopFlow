#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "initialisation.h"

int main()
{
    Boutique b;
    strcpy(b.nom, "ShopFlow");
    b.capaciteClients = 4;
    b.nbClients = 0;
    b.clients = (Client *) malloc(b.capaciteClients * sizeof(Client));

    b.clients[0] = (Client) {1, "lacombat", "jeremie", "truc@gmail.com", "067978", {"rue", "ville", "codepostal", "pays"}, 0,0,1,{},1};
    return 0;
}