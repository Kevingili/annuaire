#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main()
{
    struct Personne utilisateur[20]; /*ON DEFINIT UN TABLEAU UTILISATEUR DE TYPE PERSONNE*/
    int choix = 0;

    do
    {
        AfficherMenu(); /*ON UTILISE UNE PROCEDURE POUR AFFICHER LE MENU*/

        printf("\t\tQuel est votre choix ?\n");
        scanf("%d", &choix);
        system("cls"); /*ON N'EFFACE L'ECRAN APRES LA SAISIE DU CHOIX DE L'UTILISATEUR*/

        if (choix<1 || choix > 5) /*CONTROLE DE SAISIE DU CHOIX DU MENU*/
            printf("Erreur de saisie, veuillez faire un choix comprit entre 1 et 5 !\n");
        switch (choix)
        {
        case 1:
            Ajouter(utilisateur); /*PROCEDURE POUR AJOUTER UN OU PLUSIEURS CONTACT*/
            break;
        case 2:
            Lire (utilisateur); /*PROCEDURE POUR AFFICHER NOS CONTACTS*/
            break;
        case 3:
            Modifier(utilisateur); /*PROCEDURE POUR MODIFIER LES NUMEROS DE NOS CONTACTS*/
            break;
        case 4:
            Supprimer(utilisateur); /*PROCEDURE POUR SUPPRIMER UN CONTACT*/
            break;
        case 5:
            printf("Au revoir ! Merci d'utiliser l'annuaire creer par M.Giloo.\n");
            break;
            }
        system("pause");
        system("cls"); /*ON N'EFFACE L'ECRAN AVANT D'AFFICHER A NOUVEAU LE MENU*/
    } while (choix != 5); /*ON RECOMMENCE CETTE BOUCLE TANT QUE LE CHOIX N'EST PAS EGAL A 5 QUI CORRESPOND A QUITTER*/

    return 0;
}

