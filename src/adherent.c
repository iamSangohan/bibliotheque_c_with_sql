/**
    * @file adherent.c
    * @author iamSangohan (MENSAH Luc Germain)
    * @version 0.1
    * @date 2023-02-25
    * Implementation des fonctions de gestion des adherents
*/

#include "adherent.h"
#include <stdio.h>

/**
    * @brief Fonction pour ajouter un adherent
    * @param conn Pointeur de connexion à la base de données
    * @param nom Chaine de caractères contenant le nom de l'adhérent
    * @param prenom Chaine de caractères contenant le prénom de l'adhérent
    * @param adresse Chaine de caractères contenant l'adresse de l'adhérent
    * @param telephone Chaine de caractères contenant le numéro de téléphone de l'adhérent
*/ 
void ajouter_adherent(MYSQL *conn, char nom[50], char prenom[100], char adresse[100], char telephone[15]){
    char requete[1000];
    sprintf(requete, "INSERT INTO adherents(nom, prenom, adresse, telephone) VALUES('%s', '%s', '%s', '%s')", nom, prenom, adresse, telephone);

    /**
        * On vérifie si la table adherents existe
        * Si elle n'existe pas, on la crée puis on ajoute l'adhérent
        * Sinon, on ajoute l'adhérent
    */
    if(mysql_query(conn, requete)){
        if(mysql_errno(conn) == 1146){
            if(mysql_query(conn, "CREATE TABLE adherents(id INT NOT NULL AUTO_INCREMENT, nom VARCHAR(50) NOT NULL, prenom VARCHAR(100) NOT NULL, adresse VARCHAR(100) NOT NULL, telephone VARCHAR(15) NOT NULL, PRIMARY KEY(id))")){
                printf("Erreur lors de la création de la table adherents : %s\n", mysql_error(conn));
            }else{
                printf("Table adherents créée avec succès\n");
                if(mysql_query(conn, requete)){
                    printf("Erreur lors de l'ajout de l'adhérent : %s\n", mysql_error(conn));
                }else{
                    printf("Adhérent (%s, %s) ajouté avec succès\n", nom, prenom);
                }
            }
        }else{
            printf("Erreur lors de l'ajout de l'adhérent : %s\n", mysql_error(conn));
        }
    }else{
        printf("Adhérent (%s, %s) ajouté avec succès\n", nom, prenom);
    }
}

/**
    * @brief Fonction pour afficher les adherents
    * @param conn Pointeur de connexion à la base de données
*/
void afficher_adherents(MYSQL *con){
    /**
        * On vérifie si la table adherents existe
        * Si elle n'existe pas, on affiche un message d'erreur
        * Sinon, on affiche la liste des adhérents
    */
    if(mysql_query(con, "SELECT * FROM adherents")){
        if(mysql_errno(con) == 1146){
            printf("La table adherents n'existe pas\n");
        }
    }else{
        MYSQL_RES *result = mysql_store_result(con);
        MYSQL_ROW row;
        int nbre_lignes = mysql_num_rows(result);
        if(nbre_lignes == 0){
            printf("Aucun adhérent n'a été ajouté\n");
        }else{
            printf("Liste des adhérents\n");
            printf("ID\tNom\tPrénom\tAdresse\tTéléphone\n");
            while(row = mysql_fetch_row(result)){
                printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
            }
        }
    }
}

/**
    * @brief Fonction pour supprimer un adherent
    * @param conn Pointeur de connexion à la base de données
    * @param id_adherent ID de l'adherent à supprimer
*/
void supprimer_adherent(MYSQL *con, int id_adherent){
    char requete[1000];
    sprintf(requete, "DELETE FROM adherents WHERE id = %d", id_adherent);

    /**
        * On vérifie si la table adherents existe
        * Si elle n'existe pas, on affiche un message d'erreur
        * Sinon, on supprime l'adhérent
    */
    if(mysql_query(con, requete)){
        if(mysql_errno(con) == 1146){
            printf("La table adherents n'existe pas\n");
        }else{
            printf("Erreur lors de la suppression de l'adhérent : %s\n", mysql_error(con));
        }
    }else{
        printf("Adhérent (%d) supprimé avec succès\n", id_adherent);
    }
}