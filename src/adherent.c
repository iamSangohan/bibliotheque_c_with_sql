#include "adherent.h"

void ajouter_adherent(MYSQL *conn, char nom[50], char prenom[100], char adresse[100], char telephone[15]){
    char requete[1000];
    sprintf(requete, "INSERT INTO adherents(nom, prenom, adresse, telephone) VALUES('%s', '%s', '%s', '%s')", nom, prenom, adresse, telephone);

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
    }
}
