/**
    * @file index.c
    * @author iamSangohan (MENSAH Luc Germain)
    * @date 2021-05-05
    * @version 0.1
    * Programme principal de la bibliothèque
*/

#include "livre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

/**
    * @var MYSQL mysql
    * @brief Variable globale de type MYSQL
    * @details Cette variable est utilisée pour la connexion à la base de donnée
*/
MYSQL mysql; // Déclaration de la variable globale mysql

/**
    * @fn int main()
    * @brief Fonction principale du programme 
*/

/**
    * @fn int connecter()
    * @brief Fonction de connexion à la base de donnée
    * @return 1 si la connexion est réussie, 0 sinon
*/
int connecter() {
    // Initialisation de MySQL
    mysql_init(&mysql);
    // Options de connexion
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
    // Connexion à la base de données
    if (mysql_real_connect(&mysql, "localhost", "luco", "luco", "biblio", 0, NULL, 0)) {
        printf("Connexion à la base de données réussie !\n");
        return 1;
    } else {
        printf("Une erreur s'est produite lors de la connexion à la base de données.\n");
        return 0;
    }
}

int main(){

    if (connecter() == 0){
        return 0;
    }else if (connecter() == 1){
        bool erreur = false;
        
        printf("Bienvenue dans la BIBLIOTECH\n");
        while (1){
        
            if (erreur == false){
                printf("-------------------------------------\n");
                printf("Choisissez l'action à effectuer \n\n");
                printf("1- Ajouter un livre\n");
                printf("2- Liste des livres\n");
                printf("3- Supprimer un livre\n");
                printf("4- Ajouter un adherent\n");
                printf("5- Liste des adherents\n");
                printf("6- Supprimer un adherent\n");
                printf("7- Emprunter un livre\n");
                printf("8- Retourner un livre\n");
                printf("9- Quitter\n"); 
            }

            int option;

            printf("--------------------\n");
            printf("Option : ");
            scanf("%d\n", &option);

            switch (option){
                case 1:
                    char nom_livre[100], nom_auteur[100], annee_parution[100];
                    int nbre_exemplaires;
                    printf("Nom du livre : ");
                    scanf("%s", nom_livre);
                    printf("\nNom de l'auteur : ");
                    scanf("%s", nom_auteur);
                    printf("\nAnnée de parution : ");
                    scanf("%s", annee_parution);
                    printf("\nNombre d'exemplaires : ");
                    scanf("%d", &nbre_exemplaires);
                    ajouter_livre(&mysql, nom_livre, nom_auteur, annee_parution, nbre_exemplaires);
                    break;
                case 2:
                    afficher_livres(&mysql);
                    break;
                case 3:
                    int id_livre;
                    afficher_livres(&mysql);
                    printf("Saisissez l'ID du livre à supprimer : ");
                    scanf("%d", &id_livre);
                    supprimer_livre(&mysql, id_livre);
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    printf("Au revoir\n");
                    return 0;
                default:
                    printf("Saisie invalide\n");
                    erreur = true;
                    break;
            }
        }
        return 0;
    }
    return 0;
}