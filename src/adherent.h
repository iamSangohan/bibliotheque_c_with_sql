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

#endif // ADHERENT_H