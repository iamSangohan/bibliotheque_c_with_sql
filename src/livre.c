#include <stdio.h>
#include "livre.h"

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
                    printf("Livre ajouté avec succès\n");
                }
            }
        }else{
            printf("Erreur lors de l'ajout du livre\n");
            printf("%s\n", mysql_error(conn));
        }
    }
}
