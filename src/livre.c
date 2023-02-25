/**
    * @file livre.c
    * @author iamSangohan (MENSAH Luc Germain) 
    * @version 0.1
    * @date 2023-02-25
    * Definition des fonctions de gestion des livres
    * @copyright Copyright (c) 2023
*/

#include <stdio.h>
#include <time.h>
#include "livre.h"

/**
    * @brief Fonction d'ajout d'un livre dans la base de données
    * On verifie d'abord que la table livres existe, si elle n'existe pas, on la crée
    * Puis on ajoute le livre
    * @param conn pointeur de connexion à la base de données
    * @param titre titre du livre
    * @param auteur nom de l'auteur du livre
    * @param annee anneé de parution du livre
    * @param nbre_exemplaires_disponibles nombre d'exemplaires disponibles du livre
 */
void ajouter_livre(MYSQL* conn, char titre[100], char auteur[100], char annee[5], int nbre_exemplaires_disponibles){
    char requete[1000];
    sprintf(requete, "INSERT INTO livres (titre, auteur, annee, nbre_exemplaires_disponibles) VALUES ('%s', '%s', '%s', %d)", titre, auteur, annee, nbre_exemplaires_disponibles);
    
    if(mysql_query(conn, requete)){
        if(mysql_errno(conn) == 1146){
            if(mysql_query(conn, "CREATE TABLE livres (id INT NOT NULL AUTO_INCREMENT, titre VARCHAR(100) NOT NULL, auteur VARCHAR(100) NOT NULL, annee VARCHAR(5) NOT NULL, nbre_exemplaires_disponibles INT NOT NULL, PRIMARY KEY (id))")){
                printf("Erreur lors de la création de la table livres\n");
                printf("%s\n", mysql_error(conn));
            }else{
                printf("Table livres créée avec succès\n");
                if(mysql_query(conn, requete)){
                    printf("Erreur lors de l'ajout du livre\n");
                    printf("%s\n", mysql_error(conn));
                }else{
                    printf("Livre (%s de %s) ajouté avec succès\n", titre, auteur);
                }
            }
        }else{
            printf("Erreur lors de l'ajout du livre\n");
            printf("%s\n", mysql_error(conn));
        }
    }else{
        printf("Livre (%s de %s) ajouté avec succès\n", titre, auteur);
    }
}

/**
    * @brief Fonction d'affichage de la liste des livres
    * Cette fonction affiche la liste des livres
    * @param conn pointeur de connexion à la base de données
*/
void afficher_livres(MYSQL* conn){
    if(mysql_query(conn, "SELECT * FROM livres")){
        if(mysql_errno(conn) == 1146){
            printf("La table livres n'existent pas\n");
        }
    }else{
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row;
        int nbre_lignes = mysql_num_rows(result);
        if(nbre_lignes == 0){
            printf("Aucun livre n'a été ajouté\n");
        }else{
            printf("Liste des livres\n");
            printf("ID\tTitre\tAuteur\tAnnée\tNb d'exemplaires dispo\n");
            while(row = mysql_fetch_row(result)){
                printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
            }
        }
    }
}

/**
    * @brief Fonction de suppression d'un livre
    * On verifie d'abord que la table livres existe, si elle n'existe pas, on affiche un message d'erreur
    * Sinon on supprime le livre
    * @param conn pointeur de connexion à la base de données
    * @param id_livre identifiant du livre à supprimer
*/
void supprimer_livre(MYSQL* conn, int id_livre){
    char requete[1000];
    sprintf(requete, "DELETE FROM livres WHERE id = %d", id_livre);
    if (mysql_query(conn, requete)) {
        if (mysql_errno(conn) == 1146) {
            printf("La table livres n'existe pas\n");
        } else {
            printf("Erreur lors de la suppression du livre : %s\n", mysql_error(conn));
        }
    } else {
        printf("Le livre a été supprimé avec succès.\n");
    }
}

/**
    * @brief Fonction d'emprunt d'un livre
    * On verifie d'abord que le livre a suffisant d'exemplaires disponibles pour etre emprunté
    * Si c'est le cas, on verifie que la table emprunts existe
    * Si elle n'existe pas, on la créee puis on emprunte le livre
    * On n'oublie pas de decrementer le nombre d'exemplaires disponibles du livre
    * @param conn 
    * @param id_livre_emprunt 
    * @param id_adherent_emprunt 
*/
void emprunter_livre(MYSQL* conn, int id_livre_emprunt, int id_adherent_emprunt){
    time_t timestamp = time(NULL);
    struct tm *date = localtime(&timestamp);
    char date_str[11]; // Tableau de caractères pour stocker la date sous forme de chaîne
    sprintf(date_str, "%04d-%02d-%02d", date->tm_year+1900, date->tm_mon+1, date->tm_mday);
    

    char requete1[1000];
    char requete2[1000];
    char requete3[1000];
    sprintf(requete1, "UPDATE livres SET nbre_exemplaires_disponibles = nbre_exemplaires_disponibles - 1 WHERE id = %d", id_livre_emprunt);
    sprintf(requete2, "INSERT INTO emprunts (id_livre, id_adherent, date_emprunt) VALUES (%d, %d, %s)", id_livre_emprunt, id_adherent_emprunt, date_str);
    sprintf(requete3, "SELECT nbre_exemplaires_disponibles FROM livres WHERE id = %d", id_livre_emprunt);

    if(mysql_query(conn, requete3)){
        printf("Erreur lors de la vérification du nombre d'exemplaires disponibles : %s\n", mysql_error(conn));
    }else if(mysql_num_rows(mysql_store_result(conn)) == 0){
        printf("Le livre n'est plus en stock\n");
    }else{
        if(mysql_query(conn, requete2)){
            if(mysql_errno(conn) == 1146){
                if(mysql_query(conn, "CREATE TABLE emprunts (id INT NOT NULL AUTO_INCREMENT, id_livre INT NOT NULL, id_adherent INT NOT NULL, date_emprunt DATE NOT NULL, PRIMARY KEY (id), FOREIGN KEY (id_livre) REFERENCES livres(id), FOREIGN KEY (id_adherent) REFERENCES adherents(id))")){
                    printf("Erreur lors de la création de la table emprunts : %s\n", mysql_error(conn));
                }else{
                    printf("Table emprunts créée avec succès\n");
                    if(mysql_query(conn, requete2)){
                        printf("Erreur lors de l'emprunt du livre : %s\n", mysql_error(conn));
                    }else{
                        printf("Livre emprunté avec succès\n");
                    }
                }
            }else{
                printf("Erreur lors de l'emprunt du livre : %s\n", mysql_error(conn));
            }
        }else{
            mysql_query(conn, requete1);
            printf("Livre emprunté avec succès\n");
        }
    }
}