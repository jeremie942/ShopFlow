cmake_minimum_required(VERSION 4.3)
project(ShopFlow C)

set(CMAKE_C_STANDARD 11)

include_directories(menuProjet)

add_executable(client.c,client.h,commandes.c,commandes.h,initialisation.c,initialisation.h,main.c,produit.c,produit.h,test.c,type.h
)
