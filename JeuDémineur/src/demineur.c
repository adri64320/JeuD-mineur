/*!
 *  \file demineur.c
 *  \author BERNARD Adrien <bernardadr@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 08 December 2022
 *
 *  \brief fonction pour le jeu du démineur
 *
 *
 */

#include "demineur.h"

int saisie_entier()
{
    int int_retour; // variable de vérification du scanf
    int int_choix;  // valeur saisie par l'utilisateur
    /*l'utilisateur saisie son choix */
    int_retour = scanf("%d", &int_choix);
    /*si la valeur de retour est égale à 0 alors il y a eu un problemme dans la saisie*/
    if (int_retour == 0)
    {
        /*envoyer un message d'erreur*/
        fprintf(stderr, "Erreur de saisie ");
        /*faire arreter le programme*/
        exit(SORTIE_ERREUR);
    }
    /*sinon si la saisie n'a pas de probleme alors retoutner int_choix*/
    return int_choix;
}

scase **allocation_plateau(int int_taille)
{
    // decllaration du tableau 2Ds
    scase **ppsc_plateau;
    // variable de boucle
    int i;
    // allocation du tableau
    ppsc_plateau = malloc(int_taille * sizeof(scase *));
    // si l'allocation a échoué
    if (ppsc_plateau == NULL)
    {
        // envoyer un message d'erreur
        fprintf(stderr, "Erreur d'allocation");
        // faire arreter le programme
        exit(SORTIE_ERREUR);
    }
    // parcourir les lignes du tableau
    for (i = 0; i < int_taille; i++)
    {
        //
        ppsc_plateau[i] = malloc(int_taille * sizeof(scase));
        // si l'allocation a échoué
        if (ppsc_plateau[i] == NULL)
        {
            // envoyer un message d'erreur
            fprintf(stderr, "Erreur d'allocation");
            // faire arreter le programme
            exit(SORTIE_ERREUR);
        }
    }
    // retourner le tableau
    return (ppsc_plateau);
}

void initialisation_plateau(scase **ppsc_plateau, int int_taille)
{
    // variable de boucle
    int i;
    // variable de boucle
    int j;
    // parcourir les lignes du tableau
    for (i = 0; i < int_taille; i++)
    {
        // parcourir les colonnes du tableau
        for (j = 0; j < int_taille; j++)
        {
            // initialiser les cases
            // initialiser le nombre de mines voisines
            ppsc_plateau[i][j].int_nb_mines_voisines = 0;
            // initialiser le drapeau à SansDrapeau
            ppsc_plateau[i][j].edr_drapeau = SansDrapeau;
            // initialiser l'état de découverte à NonDecouverte
            ppsc_plateau[i][j].ede_decouverte = NonDecouverte;
            // initialiser l'état de la case à Vide
            ppsc_plateau[i][j].eca_mines = Vide;
        }
    }
}
void initialisation_plateau_fini(scase **ppsc_plateau, int int_taille)
{
    int i;

    int j;

    for (i = 0; i < int_taille; i++)
    {
        // parcourir les colonnes du tableau
        for (j = 0; j < int_taille; j++)
        {

            // initialiser l'état de la case à Bombe
            ppsc_plateau[i][j].ede_decouverte = Decouverte;
        }
    }
}

void placement_bombes(scase **ppsc_plateau, int int_taille, int int_nb_bombes)
{
    // variable de boucle
    int i;
    // variable qui prend une ligne aléatoire
    int int_lignes;
    // variable qui prend une colonne aléatoire
    int int_colonnes;
    // parcourir le nombre de bombes
    i = 0;
    while (i < int_nb_bombes)
    {
        // prendre une ligne et une colonne aléatoire
        int_lignes = rand() % int_taille;
        int_colonnes = rand() % int_taille;
        // verifier si la case n'est pas deja une mine
        if (ppsc_plateau[int_lignes][int_colonnes].eca_mines == Vide)
        {

            ppsc_plateau[int_lignes][int_colonnes].eca_mines = Bombe;
            i++;
        }
    }
}

// fonction qui verifie que toutes les cases vides ont leur voisins decouverts alors on les decouvre
void verif_voisins(scase **ppsc_plateau, int int_taille, int int_lignes, int int_colonnes)
{
    // si la case est n'est pas decouverte
    if (ppsc_plateau[int_lignes][int_colonnes].ede_decouverte == NonDecouverte)
    {

        // la decouvrir
        ppsc_plateau[int_lignes][int_colonnes].ede_decouverte = Decouverte;
        // si la case n'a pas de voisins
        if (ppsc_plateau[int_lignes][int_colonnes].int_nb_mines_voisines == 0)
        {
            // si la case n'est pas sur la premiere ligne et la premiere colonne et que la case du haut a gauche n'est pas decouverte
            if ((int_lignes > 0) && (int_colonnes > 0) && (ppsc_plateau[int_lignes - 1][int_colonnes - 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes - 1, int_colonnes - 1);
            }
            // si la case n'est pas sur la premiere ligne et que la case du haut n'est pas decouverte
            if ((int_lignes > 0) && (ppsc_plateau[int_lignes - 1][int_colonnes].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes - 1, int_colonnes);
            }
            // si la case n'est pas sur la premiere ligne et la derniere colonne et que la case du haut a droite n'est pas decouverte
            if ((int_lignes > 0) && (int_colonnes < int_taille - 1) && (ppsc_plateau[int_lignes - 1][int_colonnes + 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes - 1, int_colonnes + 1);
            }
            // si la case n'est pas sur la premiere colonne et que la case de gauche n'est pas decouverte
            if ((int_colonnes > 0) && (ppsc_plateau[int_lignes][int_colonnes - 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes, int_colonnes - 1);
            }
            // si la case n'est pas sur la derniere colonne et que la case de droite n'est pas decouverte
            if ((int_colonnes < int_taille - 1) && (ppsc_plateau[int_lignes][int_colonnes + 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes, int_colonnes + 1);
            }
            // si la case n'est pas sur la derniere ligne et la premiere colonne et que la case du bas a gauche n'est pas decouverte
            if ((int_lignes < int_taille - 1) && (int_colonnes > 0) && (ppsc_plateau[int_lignes + 1][int_colonnes - 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes + 1, int_colonnes - 1);
            }
            // si la case n'est pas sur la derniere ligne et que la case du bas n'est pas decouverte
            if ((int_lignes < int_taille - 1) && (ppsc_plateau[int_lignes + 1][int_colonnes].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes + 1, int_colonnes);
            }
            // si la case n'est pas sur la derniere ligne et la derniere colonne et que la case du bas a droite n'est pas decouverte
            if ((int_lignes < int_taille - 1) && (int_colonnes < int_taille - 1) && (ppsc_plateau[int_lignes + 1][int_colonnes + 1].ede_decouverte == NonDecouverte))
            {
                // relancer la fonction récurssivement
                verif_voisins(ppsc_plateau, int_taille, int_lignes + 1, int_colonnes + 1);
            }
        }
    }
}

scase **bombes_autour(scase **ppsc_plateau, int int_taille)
{

    int i;              // variable de boucle
    int j;              // variable de boucle
    int int_nb_voisins; // variable de nombre de voisins
    // parcourir le tableau
    for (i = 0; i < int_taille; i++)
    {
        for (j = 0; j < int_taille; j++)
        {
            // on initialise le nombre de voisins a 0
            int_nb_voisins = 0;
            // si la case n'est pas une bombe
            if ((ppsc_plateau[i][j].eca_mines != Bombe))
            {
                // si la case n'est pas sur la premiere ligne et la premiere colonne et que la case du haut a gauche est une bombe
                if (i > 0 && j > 0 && ppsc_plateau[i - 1][j - 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la premiere ligne et que la case du haut est une bombe
                if (i > 0 && ppsc_plateau[i - 1][j].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la premiere ligne et la derniere colonne et que la case du haut a droite est une bombe
                if (i > 0 && j < int_taille - 1 && ppsc_plateau[i - 1][j + 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la premiere colonne et que la case de gauche est une bombe
                if (j > 0 && ppsc_plateau[i][j - 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la derniere colonne et que la case de droite est une bombe
                if (j < int_taille - 1 && ppsc_plateau[i][j + 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la derniere ligne et la premiere colonne et que la case du bas a gauche est une bombe
                if (i < int_taille - 1 && j > 0 && ppsc_plateau[i + 1][j - 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la derniere ligne et que la case du bas est une bombe
                if (i < int_taille - 1 && ppsc_plateau[i + 1][j].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // si la case n'est pas sur la derniere ligne et la derniere colonne et que la case du bas a droite est une bombe
                if (i < int_taille - 1 && j < int_taille - 1 && ppsc_plateau[i + 1][j + 1].eca_mines == Bombe)
                {
                    // on incremente le nombre de voisins
                    int_nb_voisins++;
                }
                // on affecte le nombre de voisins a la case
                ppsc_plateau[i][j].int_nb_mines_voisines = int_nb_voisins;
            }
        }
    }
    // on retourne le tableau
    return (ppsc_plateau);
}

int choixJoueur(scase **ppsc_plateau, int int_taille, int int_nb_bombes)
{
    // variable qui prend la ligne
    int int_ligne;
    // variable qui prend la colonne
    int int_colonne;
    // variable qui prend le choix du joueur
    int int_choix;
    // variable qui va permettre de verifier si le joueur a gagne
    int int_gagner;
    // on l'initalise a 0
    int_gagner = 0;
    // on parcourt le tableau
    for (int i = 0; i < int_taille; i++)
    {
        // on parcourt le tableau
        for (int j = 0; j < int_taille; j++)
        {
            // si la case n'a pas ete decouverte
            if (ppsc_plateau[i][j].ede_decouverte == NonDecouverte)
            {

                int_gagner++;
            }
            // si la case est une bombe
            if (ppsc_plateau[i][j].eca_mines == Bombe)
            {
                int_gagner--;
            }
        }
    }
    // si le joueur a gagne
    if (int_gagner == 0)
    {
        // on affiche un message
        printf("Vous avez gagne\n");
        // on affiche le plateau avec les bombes
        initialisation_plateau_fini(ppsc_plateau, int_taille);
        affichage_plateau(ppsc_plateau, int_taille, int_nb_bombes);
        // on retourne 1
        return (1);
    }
    // afficher le menu
    printf("Tapez 1 pour poser un drapeau, 2 pour decouvrir une case : ");
    // prendre le choix du joueur et verifie le choix
    int_choix = saisie_entier();

    // switch en fonction du choix du joueur
    switch (int_choix)
    {
        // si le joueur veut poser un drapeau
    case 1:
        // on demande la ligne et la colonne
        printf("Choisissez une ligne : ");
        int_ligne = saisie_entier();
        printf("Choisissez une colonne : ");
        // on verifie que la ligne et la colonne sont valides
        int_colonne = saisie_entier();
        // on verifie que la ligne et la colonne sont valides
        if ((int_ligne < int_taille && int_ligne >= 0) && (int_colonne < int_taille && int_colonne >= 0))
        {
            // on verifie que la case n'est pas deja decouverte
            if (ppsc_plateau[int_ligne][int_colonne].edr_drapeau == Drapeau)
            {
                // on enleve le drapeau
                ppsc_plateau[int_ligne][int_colonne].edr_drapeau = SansDrapeau;
                return (0);
            }
            if (ppsc_plateau[int_ligne][int_colonne].ede_decouverte == NonDecouverte)
            {
                // on pose un drapeau
                ppsc_plateau[int_ligne][int_colonne].edr_drapeau = Drapeau;
                return (0);
            }

            else
            {
                // sinon on affiche un message d'erreur
                printf("Vous ne pouvez pas poser de drapeau sur une case deja decouverte");
                // on recommence
                return (-1);
            }
        }
        else
        {
            // sinon on affiche un message d'erreur
            printf("Veuillez saisir une ligne et une colonne valide");
            // on recommence
            return (-1);
        }

        break;
    case 2:
        // on demande la ligne et la colonne
        printf("Choisissez une ligne : ");
        int_ligne = saisie_entier();
        printf("Choisissez une colonne : ");
        int_colonne = saisie_entier();
        // on verifie que la ligne et la colonne sont valides
        if ((int_ligne < int_taille && int_ligne >= 0) || (int_colonne < int_taille && int_colonne >= 0))
        {
            // on verifie si la case est une mine
            if (ppsc_plateau[int_ligne][int_colonne].eca_mines == Bombe)
            {
                // fin du jeu, vous avez perdu
                printf("Vous avez perdu");
                initialisation_plateau_fini(ppsc_plateau, int_taille);
                affichage_plateau(ppsc_plateau, int_taille, int_nb_bombes);
                // on quitte le jeu
                return (1);
            }
            else
            {
                // sinon on decouvre la case
                // ppsc_plateau[int_ligne][int_colonne].ede_decouverte = Decouverte;
                verif_voisins(ppsc_plateau, int_taille, int_ligne, int_colonne);
                return (0);
            }
        }
        else
        {
            // sinon on affiche un message d'erreur
            printf("Veuillez saisir une ligne et une colonne valide");
            // on recommence
            return (-1);
        }

        break;

    default:
        // sinon on affiche un message d'erreur
        printf("Veuillez saisir un choix valide");
        // on recommence
        return (-1);
        break;
    }
}

void affichage_plateau(scase **ppsc_plateau, int int_taille, int int_nb_bombes)
{
    int int_nb_drapeau;
    // afficher le plateau avec les delimitations
    // variable de boucle
    int i;
    // variable de boucle
    int j;
    int_nb_drapeau = 0;
    for (i = 0; i < int_taille; i++)
    {
        printf("  %d ", i);
    }
    printf("\n");

    // parcourir les lignes du tableau
    for (i = 0; i < int_taille; i++)
    {

        // parcourir les colonnes du tableau
        for (j = 0; j < int_taille; j++)
        {
            // afficher les delimitations
            printf("+---");
        }
        // afficher les delimitations
        printf("+\n");
        // parcourir les colonnes du tableau
        for (j = 0; j < int_taille; j++)
        {
            // afficher les delimitations
            printf("|");
            // si la case est découverte
            if (ppsc_plateau[i][j].ede_decouverte == Decouverte)
            {
                // si la case est une mine
                if (ppsc_plateau[i][j].eca_mines == Bombe)
                {
                    // afficher une mine
                    printf(" X ");
                }
                // si la case à des mines voisines
                else if (ppsc_plateau[i][j].int_nb_mines_voisines != 0)
                {
                    // afficher un le nombre de mines voisines
                    printf(" %d ", ppsc_plateau[i][j].int_nb_mines_voisines);
                }
                else
                {
                    // afficher un point
                    printf(" . ");
                }
            }
            // si la case n'est pas découverte
            else if (ppsc_plateau[i][j].ede_decouverte == NonDecouverte)
            {
                // si la case a un drapeau
                if (ppsc_plateau[i][j].edr_drapeau == Drapeau)
                {
                    // afficher un drapeau
                    printf(" D ");
                }
                // si la case n'a pas de drapeau
                else if (ppsc_plateau[i][j].edr_drapeau == SansDrapeau)
                {
                    // afficher un espace
                    printf("   ");
                }
            }
        }
        // afficher les delimitations
        printf("| %d\n", i);
    }

    // parcourir les colonnes du tableau
    for (j = 0; j < int_taille; j++)
    {
        // afficher les delimitations
        printf("+---");
    }
    // afficher les delimitations
    printf("+\n");
    // parcourir les lignes du tableau
    for (i = 0; i < int_taille; i++)
    {
        // parcourir les colonnes du tableau
        for (j = 0; j < int_taille; j++)
        {
            // si la case a un drapeau
            if (ppsc_plateau[i][j].edr_drapeau == Drapeau)
            {
                // on incremente le nombre de drapeau
                int_nb_drapeau++;
            }
        }
    }
    // afficher le nombre de drapeau
    printf("Mines : %d / %d \n", int_nb_drapeau, int_nb_bombes);
}

void jouer(scase **ppsc_plateau, int int_taille, int int_nb_bombes)
{
    //appelle de la fonction d'initialisation du plateau
    initialisation_plateau(ppsc_plateau, int_taille);
    //appelle de la fonction de placement des bombes
    placement_bombes(ppsc_plateau, int_taille, int_nb_bombes);
    //appelle de la fonction de placement des bombes autour
    bombes_autour(ppsc_plateau, int_taille);
    //appelle de la fonction d'affichage du plateau
    affichage_plateau(ppsc_plateau, int_taille, int_nb_bombes);
    // tant que le joueur n'a pas gagné ou perdu
    while (choixJoueur(ppsc_plateau, int_taille, int_nb_bombes) != 1)
    {
        // on affiche le plateau
        affichage_plateau(ppsc_plateau, int_taille, int_nb_bombes);
    }
}

void liberation_plateau(scase**ppsc_plateau, int int_taille){
    int i;// variable de boucle
    for (i = 0; i < int_taille; i++)
    {
        // libération de la mémoire
        free(ppsc_plateau[i]);
    }
    // libération de la mémoire
    free(ppsc_plateau);
}
