/**
    * @file adherent.h
    * @author iamSangohan (MENSAH Luc Germain)
    * @version 0.1
    * @date 2023-02-25
    * Declaration des fonctions pour la gestion des adherents
*/

#ifndef ADHERENT_H
    #define ADHERENT_H
    #include <mysql/mysql.h>

    /**
        * @fn ajouter_adherent
        * @param conn
        * @param nom
        * @param prenom
        * @param adresse
        * @param telephone
        * @brief Fonction pour ajouter un adherent
     */
    void ajouter_adherent(MYSQL *conn, char nom[50], char prenom[100], char adresse[100], char telephone[15]);

    /**
        * @fn afficher_adherents
        * @param conn Pointeur de connexion à la base de données
        * @brief Fonction pour afficher les adherents
     */
    void afficher_adherents(MYSQL *conn);

    /**
        * @fn supprimer_adherent
        * @param conn Pointeur de connexion à la base de données
        * @param id_adherent ID de l'adherent à supprimer
        * @brief Fonction pour supprimer un adherent
    */
    void supprimer_adherent(MYSQL *conn, int id_adherent);

#endif // ADHERENT_H
