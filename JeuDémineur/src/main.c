/*!
 *  \file main.c
 *  \author BERNARD Adrien <bernardadr@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 08 December 2022
 *
 *  \brief gerer le jeu du démineur
 *
 *
 */
// Inclusion des entêtes de librairie
#include "demineur.h"
 
int main(int argc, char **argv)
{
    //déclaration du plateau
    scase ** ppsc_plateau;
    //déclaration de la taille du plateau
    int int_taille;
    //déclaration du nombre de bombes
    int int_nb_bombes;
    //affichage du message de bienvenue
    printf("Bienvenue sur le jeu du démineur\n");
    //saisie de la taille du plateau
    printf("Quel taille de plateau voulez vous ? \n");
    int_taille = saisie_entier();
    //affichage de la taille du plateau
    printf("Vous avez choisis la taille : %d pour le plateau \n", int_taille);
    //saisie du nombre de bombes
    printf("Combien de bombes voulez vous mettre sur votre plateau ? \n");
    int_nb_bombes = saisie_entier();
    //allocation du plateau
    ppsc_plateau = allocation_plateau(int_taille);
    //initialisation du plateau
    initialisation_plateau(ppsc_plateau, int_taille);
    //initialisation du random
    srand(time(NULL));
    //fonction qui permet de faire jouer le démineur
    jouer(ppsc_plateau, int_taille, int_nb_bombes);
    //libération du plateau
    liberation_plateau(ppsc_plateau, int_taille);
    //verification que tout est ok
    return (SORTIE_SUCCES);
}
