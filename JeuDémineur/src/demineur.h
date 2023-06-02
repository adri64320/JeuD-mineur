/*!
 *  \file demineur.h
 *  \author BERNARD Adrien <bernardadr@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 08 December 2022
 *
 *  \brief header du demineur
 *
 *
 */

// Inclusion des entêtes de librairie
// Librairie standard
#include <stdlib.h>
// Librairie entree sortie
#include <stdio.h>
// Librairie pour le temps
#include <time.h>

#ifndef __cryptage_H_
#define __cryptage_H_

/*!
 \def SORTIE_SUCCES
 \brief Code de sortie confirmant le bon déroulement du programme
*/
#define SORTIE_SUCCES 0

/*!
 \def SORTIE_ERREUR
 \brief Code de sortie informant d'une erreur
*/
#define SORTIE_ERREUR -1

/*!
 \enum typeDecouverte
 \brief enumeration pour savoir si la case a ete decouverte
*/
typedef enum typeDecouverte
{
    NonDecouverte, /*! case non decouverte*/
    Decouverte     /*! case decouverte*/
} typeDecouverte;
/*!
 \enum typeDrapeau
 \brief enumeration pour savoir si la case à un drapeau ou non
 */
typedef enum typeDrapeau
{
    SansDrapeau, /*! case sans drapeau */
    Drapeau      /*! case avec un drapeau*/
} typeDrapeau;
/*!
 \enum typeCase
 \brief enumeration pour savoir si la case est une bombe ou non
*/
typedef enum typeCase
{
    Vide, /*! case sans bombe*/
    Bombe /*! case avec bombe*/
} typeCase;

/*!
 \struct case
 \brief structure pour les cases du démineur
*/
typedef struct scase
{
    int int_nb_mines_voisines;     /*! contient le nombres de mines voisines de la case*/
    typeDrapeau edr_drapeau;       /*!si la case contient un drapeau */
    typeDecouverte ede_decouverte; /*! si la case a été découverte*/
    typeCase eca_mines;            /*!si cette case est une mine ou non*/
} scase;

/*!
 \fn int saisie_entier()
 \brief fonction pour saisir un entier
 \return int_choix
*/
int saisie_entier();

/*!
 \fn scase ** allocation_plateau(scase ** ppsc_plateau, int int_taille)
 \brief fonction pour allouer un plateau de jeu
 \param int_taille taille du plateau
 \return ppsc_plateau
*/
scase **allocation_plateau(int int_taille);

/*!
 \fn void initialisation_plateau(scase ** ppsc_plateau, int int_taille)
 \brief fonction pour initialiser le plateau de jeu
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
*/

void initialisation_plateau(scase **ppsc_plateau, int int_taille);

/*!
 \fn void affichage_plateau(scase ** ppsc_plateau, int int_taille)
 \brief fonction pour afficher le plateau de jeu
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
*/
void affichage_plateau(scase **ppsc_plateau, int int_taille, int int_nb_bombes);

/*!
 \fn void placement_bombes(scase ** ppsc_plateau, int int_taille, int int_nb_bombes)
 \brief fonction pour placer les bombes sur le plateau de jeu
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
 \param int_nb_bombes nombre de bombes
*/

void placement_bombes(scase **ppsc_plateau, int int_taille, int int_nb_bombes);


/*!
 \fn void initialisation_plateau_fini(scase ** ppsc_plateau, int int_taille)
 \brief fonction pour initialiser le plateau de jeu
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
*/

void initialisation_plateau_fini(scase **ppsc_plateau, int int_taille);

//commentaire doxygen
/*!
 \fn void verif_voisins(scase ** ppsc_plateau, int int_taille, int int_lignes, int int_colonnes)
 \brief fonction pour verifier les voisins d'une case
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
 \param int_lignes ligne de la case
 \param int_colonnes colonne de la case
*/

void verif_voisins(scase **ppsc_plateau, int int_taille, int int_lignes, int int_colonnes);

/*!
 \fn int choixJoueur(scase ** ppsc_plateau, int int_taille, int int_nb_bombes)
 \brief fonction pour choisir une case
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
 \param int_nb_bombes nombre de bombes
 \return int_choix
*/
int choixJoueur(scase **ppsc_plateau, int int_taille, int int_nb_bombes);

/*!
 \fn scase ** bombes_autour(scase ** ppsc_plateau, int int_taille)
 \brief fonction pour compter le nombre de bombes autour d'une case
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
 \return ppsc_plateau
*/
scase **bombes_autour(scase **ppsc_plateau, int int_taille);

/*!
 \fn void jouer(scase ** ppsc_plateau, int int_taille, int int_nb_bombes)
 \brief fonction pour jouer
 \param ppsc_plateau plateau de jeu
 \param int_taille taille du plateau
 \param int_nb_bombes nombre de bombes
*/
void jouer(scase**ppsc_plateau, int int_taille,int int_nb_bombes);

void liberation_plateau(scase** ppsc_plateau,int int_taille);

#endif
