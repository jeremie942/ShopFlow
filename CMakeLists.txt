cmake_minimum_required(VERSION 4.1)
project(ShopFlow C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(menuProjet)

add_executable(ShopFlow
        menuProjet/client.c
        menuProjet/client.h
        menuProjet/commandes.c
        menuProjet/commandes.h
        menuProjet/initialisation.c
        menuProjet/initialisation.h
        menuProjet/main.c
        menuProjet/produit.c
        menuProjet/produit.h
        menuProjet/test.c
        menuProjet/type.h)
