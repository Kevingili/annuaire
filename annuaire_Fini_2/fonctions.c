#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

void TrieOrdreAlpha(struct Personne utilisateur[], int nombreMots) /*PROCEDURE POUR TRIER LES CONTACTS DANS L'ODRE ALPHABETIQUE*/
{
    struct Personne pers2[20]; /*J'UTILISE UNE DEUXIEME STRUCTURE POUR STOCKER TEMPORAIREMENT LES CONTACTS*/
    int i, test;

    for (i = 0; i < nombreMots - 1; i++)
    {
        int j;
        for (j = i + 1; j < nombreMots; j++)
        {
            test = strcmp(utilisateur[i].nom, utilisateur[j].nom);

            if (test > 0) /*SI LE PREMIER NOM EST MAL CLASSE PAR RAPPORT AU 2EME NOM*/
            {
                /*EN GROS J'INVERSE LE NOM 1 AVEC LE NOM 2 */
                /*JE STOCK LE NOM MAL CLASSE DANS MA DEUXIEME STRUCTURE*/
                strcpy(pers2[0].nom, utilisateur[i].nom);
                strcpy(pers2[0].prenom, utilisateur[i].prenom);
                strcpy(pers2[0].tel, utilisateur[i].tel);

                /*JE COPIE LE NOM 2 DANS LE NOM 1 QUI EST SA BONNE PLACE*/
                strcpy(utilisateur[i].nom, utilisateur[j].nom);
                strcpy(utilisateur[i].prenom, utilisateur[j].prenom);
                strcpy(utilisateur[i].tel, utilisateur[j].tel);

                /*JE COPIE LE NOM MAL CLASSE A SA BONNE PLACE*/
                strcpy(utilisateur[j].nom, pers2[0].nom);
                strcpy(utilisateur[j].prenom, pers2[0].prenom);
                strcpy(utilisateur[j].tel, pers2[0].tel);
            }

        }
    }
}
void AfficherMenu() /*ON UTILISE UNE PROCEDURE POUR AFFICHER LE MENU*/
{
        printf("\t\t######################################\n");
        printf("\t\t#              === Menu ===          #\n");
        printf("\t\t#              1.Ajouter             #\n");
        printf("\t\t#              2.Lire                #\n");
        printf("\t\t#              3.Modifier            #\n");
        printf("\t\t#              4.Supprimer           #\n");
        printf("\t\t#              5.Quitter             #\n");
        printf("\t\t######################################\n\n");
}
void Ajouter(struct Personne utilisateur[]) /*PROCEDURE POUR AJOUTER UN OU PLUSIEURS CONTACT*/
{
    int i = 0;
    int nbP = 0;
    printf("Combien de personnes voulez-vous ajouter ?\n");
    scanf("%d", &nbP);

    while (i<nbP)
    {
        /*SAISIE DU CONTACT*/
        printf("Quel est le nom de la personne numero %d ? ", i+1);
        scanf("%s", utilisateur[i].nom);
        printf("Quel est le prenom de la personne numero %d ? ", i+1);
        scanf("%s", utilisateur[i].prenom);
        printf("Quel est le numero de telephone de la personne numero %d ? ", i+1);
        scanf("%s", utilisateur[i].tel);

        FILE* fichier = NULL; /*ON INITIALISE LE POINTEUR AVEC LA VALEUR NULL*/
        fichier = fopen("test.txt", "a"); /*ON OUVRE LE FICHIER EN MODE AJOUT*/

        if (fichier != NULL) /*ON VERIFIE QUE LE FICHIER A BIEN ETE OUVERT*/
        {
            /*ON ECRIT DANS LE FICHIER NOS 3 VARIABLES*/
            fprintf(fichier, "%s %s %s\n", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
            fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/
        }
        i++;
    }
}

void Lire(struct Personne utilisateur[]) /*PROCEDURE POUR AFFICHER NOS CONTACTS*/
{
    int nombreMots = 0;
    int caractereLu = 0;
    int i = 0;

    FILE* fichier = NULL; /*ON INITIALISE LE POINTEUR AVEC LA VALEUR NULL*/
    fichier = fopen("test.txt", "r"); /*ON OUVRE LE FICHIER EN MODE LECTURE SEULE*/

    if (fichier != NULL) /*ON VERIFIE QUE LE FICHIER A BIEN ETE OUVERT*/
    {
        /*ON COMPLE LE NOMBRE DE LIGNES DANS NOTRE FICHIER*/
        do
        {
            caractereLu = fgetc(fichier);
            if (caractereLu == '\n')
                nombreMots++;
        } while(caractereLu != EOF);

        fseek(fichier, 0, SEEK_SET); /*ON REPLACE NOTRE CURSEUR AU DEBUT DU FICHIER*/
        printf("\t\t=== CARNET DE CONTACT ===\n");
        printf("\t=== Nombre de personnes dans le carnet: %d ===\n\n", nombreMots);
        if (nombreMots == 0)
            printf("Votre carnet de contact est vide,\nvous devriez ajouter des contacts dans la section ajouter du menu\n");
        for (i = 0; i < nombreMots; i++)
        {
            /*ON RECUPERE LE CONTENU DE NOTRE FICHIER DANS NOTRE TABLEAU UTILISATEUR DE TYPE STRUCTURE*/
            fscanf(fichier, "%s %s %s", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }

        /*ON TRIE NOS CONTACTS DANS L'ODRE ALPHABETIQUE*/
        TrieOrdreAlpha(utilisateur, nombreMots);

        for (i = 0; i < nombreMots; i++)
        {
            /*ON AFFICHE NOS CONTACTS*/
            printf("%d ) %s \t   %s   \t %s\n", i+1, utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }
        fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/

        FILE* fichier = NULL; /*ON REINITIALISE LE POINTEUR AVEC LA VALEUR NULL*/
        fichier = fopen("test.txt", "w+"); /*ON REOUVRE LE FICHIER EN MODE LECTURE ET ECRITURE AVEC SUPPRESSION DU CONTENU AU PREALABLE*/

        if (fichier != NULL) /*ON VERIFIE QUE LE FICHIER A BIEN ETE OUVERT*/
        {
            for (i = 0; i < nombreMots; i++)
            {
                if (strlen(utilisateur[i].nom) > 1) /*SI LA CHAINE UTILISATEUR.NOM N'EST PAS VIDE*/
                /*ON ECRIT DANS NOTRE FICHIER NOTRE STRUCTURE UTILISATEUR*/
                fprintf(fichier, "%s %s %s\n", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
            }
            fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/
        }
    }
}

void Modifier(struct Personne utilisateur[]) /*PROCEDURE POUR MODIFIER LES NUMEROS DE NOS CONTACTS*/
{
    int nombreMots = 0;
    int caractereLu = 0;
    int i = 0;
    char personneModifier[30];
    char nouveauNumeroTelephone[30];

    FILE* fichier = NULL; /*ON INITIALISE LE POINTEUR AVEC LA VALEUR NULL*/
    fichier = fopen("test.txt", "r");

    if (fichier != NULL) /*ON VERIFIE QUE LE FICHIER A BIEN ETE OUVERT*/
    {
        do
        {
            caractereLu = fgetc(fichier);
            if (caractereLu == '\n')
                nombreMots++;
        } while(caractereLu != EOF);

        fseek(fichier, 0, SEEK_SET);
        printf("\t\t=== MODIFICATION ===\n");
        printf("\tNombre de personnes dans le carnet: %d\n\n", nombreMots);
        if (nombreMots == 0)
            printf("Votre carnet de contact est vide,\nvous devriez ajouter des contacts dans la section ajouter du menu\n");
        for (i = 0; i < nombreMots; i++)
        {
            fscanf(fichier, "%s %s %s", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }

         TrieOrdreAlpha(utilisateur, nombreMots);

        for (i = 0; i < nombreMots; i++)
        {
            /*ON AFFICHE NOS CONTACTS*/
            printf("%d ) %s \t   %s   \t %s\n", i+1, utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }

        printf("Quel personne voulez vous modifier ? (entrer son nom) \n");
        scanf("%s", personneModifier);

        for (i = 0; i < nombreMots; i++)
        {
            if (strcmp(personneModifier, utilisateur[i].nom) == 0) /*SI LE NOM ENTRER CORRESPOND AU NOM DE LA STRUCTURE ALORS*/
            {
                /*ON EFFECTUE UNE SAISIE*/
                printf("Quel est son nouveau numero de telephone?");
                scanf("%s", nouveauNumeroTelephone);
                /*ON EFFECTUE LA MODIFICATION DE NUMERO DE TELEPHONE*/
                strcpy(utilisateur[i].tel, nouveauNumeroTelephone);
                printf("modification effectuer\n"); /*MESSAGE DE CONFIRMATION POUR L'UTILISATEUR*/
            }

        }

        fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/

        FILE* fichier = NULL; /*ON INITIALISE LE POINTEUR AVEC LA VALEUR NULL*/
        fichier = fopen("test.txt", "w+"); /*ON REOUVRE LE FICHIER EN MODE LECTURE ET ECRITURE AVEC SUPPRESSION DU CONTENU AU PREALABLE*/

        if (fichier != NULL) /*ON VERIFIE QUE LE FICHIER A BIEN ETE OUVERT*/
        {
            for (i = 0; i < nombreMots; i++)
            {
                if (strlen(utilisateur[i].nom) > 1) /*SI LA CHAINE UTILISATEUR.NOM N'EST PAS VIDE*/
                    /*ON ECRIT DANS NOTRE FICHIER NOTRE STRUCTURE UTILISATEUR*/
                    fprintf(fichier, "%s %s %s\n", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
            }
            fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/
        }
    }
}

void Supprimer(struct Personne utilisateur[]) /*PROCEDURE POUR SUPPRIMER UN CONTACT*/
{
    /*J'AI DECIDE DE NE PAS BEAUCOUP COMMENTER CETTE PROCEDURE CAR ELLE EST SIMILAIRE A LA PROCEDURE MODIFIER*/
    int nombreMots = 0;
    int caractereLu = 0;
    int i = 0;
    char personneSupprimer[30];
    char chaineVide[] = "";

    printf("\t\t=== SUPPRESSION ===\n");
    FILE* fichier = NULL;
    fichier = fopen("test.txt", "r");

    if (fichier != NULL)
    {
        do
        {
            caractereLu = fgetc(fichier);
            if (caractereLu == '\n')
                nombreMots++;
            } while(caractereLu != EOF);

        fseek(fichier, 0, SEEK_SET);
        printf("\tNombre de personnes dans le carnet: %d\n\n", nombreMots);
        if (nombreMots == 0)
            printf("Votre carnet de contact est vide,\nvous devriez ajouter des contacts dans la section ajouter du menu\n");

        for (i = 0; i < nombreMots; i++)
        {
            fscanf(fichier, "%s %s %s", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }

        TrieOrdreAlpha(utilisateur, nombreMots);

        for (i = 0; i < nombreMots; i++)
        {
            /*ON AFFICHE NOS CONTACTS*/
            printf("%d ) %s \t   %s   \t %s\n", i+1, utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
        }
        printf("Quel personne voulez vous supprimer ? (entrer son nom) \n");
        scanf("%s", personneSupprimer);

        for (i = 0; i < nombreMots; i++)
        {
            if (strcmp(personneSupprimer, utilisateur[i].nom) == 0) /*SI LE NOM ENTRER CORRESPOND AU NOM DE LA STRUCTURE ALORS*/
            {
                /*J'EFFACE LE CONTENU DE TOUTE LA PERSONNE (NOM, PRENOM, TEL)*/
                strcpy(utilisateur[i].nom, chaineVide);
                strcpy(utilisateur[i].prenom, chaineVide);
                strcpy(utilisateur[i].tel, chaineVide);
                printf("suppression effectuer\n");
            }

        }

        fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/

        FILE* fichier = NULL;
        fichier = fopen("test.txt", "w+");

        if (fichier != NULL)
        {
            for (i = 0; i < nombreMots; i++)
            {
                if (strlen(utilisateur[i].nom) > 1) /*VERIFICATION POUR SAVOIR SI LA CHAINE EST VIDE OU NON*/
                    fprintf(fichier, "%s %s %s\n", utilisateur[i].nom, utilisateur[i].prenom, utilisateur[i].tel);
            }
            fclose(fichier); /*ON FERME LE FICHIER QUI A ETE OUVERT*/
        }
    }

}

