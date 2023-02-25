/**
    * @file index.c
    * @author iamSangohan (MENSAH Luc Germain)
    * @date 2021-05-05
    * @version 0.1
    * Programme principal de la bibliothèque
*/

#include "livre.h"
#include "adherent.h"
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
                printf("9- Quitter"); 
            }

            int option;

            printf("\n--------------------\n");
            printf("Option : ");
            scanf("%d", &option);
            printf("--------------------\n");

            switch (option){
                /**
                    * Ajouter un livre
                    * L'utilisateur va entrer les informations du livre
                    * Puis on va appeler la fonction ajouter_livre()
                    * Pour ajouter le livre à la base de données
                */
                case 1:
                    char nom_livre[100], nom_auteur[100], annee_parution[100];
                    int nbre_exemplaires;
                    printf("Nom du livre : ");
                    scanf("%s", nom_livre);
                    printf("Nom de l'auteur : ");
                    scanf("%s", nom_auteur);
                    printf("Année de parution : ");
                    scanf("%s", annee_parution);
                    printf("Nombre d'exemplaires : ");
                    scanf("%d", &nbre_exemplaires);
                    ajouter_livre(&mysql, nom_livre, nom_auteur, annee_parution, nbre_exemplaires);
                    break;

                /**
                    * Afficher la liste des livres
                    * On va appeler la fonction afficher_livres()
                    * Pour afficher la liste des livres
                */
                case 2:
                    afficher_livres(&mysql);
                    break;
                
                /**
                    * Supprimer un livre
                    * L'utilisateur va entrer l'ID du livre à supprimer
                    * Puis on va appeler la fonction supprimer_livre()
                    * Pour supprimer le livre de la base de données
                */
                case 3:
                    int id_livre;
                    afficher_livres(&mysql);
                    printf("Saisissez l'ID du livre à supprimer : ");
                    scanf("%d", &id_livre);
                    supprimer_livre(&mysql, id_livre);
                    break;

                /**
                    * Ajouter un adherent
                    * L'utilisateur va entrer les informations de l'adherent
                    * Puis on va appeler la fonction ajouter_adherent()
                    * Pour ajouter l'adherent à la base de données 
                */    
                case 4:
                    char nom_adherent[50], prenom_adherent[100], adresse_adherent[100], telephone_adherent[15];
                    printf("Nom de l'adherent : ");
                    scanf("%s", nom_adherent);
                    printf("Prenom de l'adherent : ");
                    scanf("%s", prenom_adherent);
                    printf("Adresse de l'adherent : ");
                    scanf("%s", adresse_adherent);
                    printf("Telephone de l'adherent : ");
                    scanf("%s", telephone_adherent);
                    ajouter_adherent(&mysql, nom_adherent, prenom_adherent, adresse_adherent, telephone_adherent);
                    break;

                /**
                    * Afficher la liste des adherents
                    * On va appeler la fonction afficher_adherents()
                    * Pour afficher la liste des adherents
                */
                case 5:
                    afficher_adherents(&mysql);
                    break;

                /**
                    * Supprimer un adherent
                    * L'utilisateur va entrer l'ID de l'adherent à supprimer
                    * Puis on va appeler la fonction supprimer_adherent()
                    * Pour supprimer l'adherent de la base de données
                */
                case 6:
                    int id_adherent;
                    afficher_adherents(&mysql);
                    printf("Saisissez l'ID de l'adherent à supprimer : ");
                    scanf("%d", &id_adherent);
                    supprimer_adherent(&mysql, id_adherent);
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