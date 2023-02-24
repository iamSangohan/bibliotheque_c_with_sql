#ifndef LIVRE_H
    #define LIVRE_H
    #include <mysql/mysql.h>

    /**
        * @fn void ajouter_livre(MYSQL* conn, char titre[100], char auteur[100], char annee[5], int nbre_exemplaires_disponibles)
        * @brief Fonction d'ajout d'un livre dans la base de données
        * @param conn Pointeur de connexion à la base de données
        * @param titre Titre du livre
        * @param auteur Auteur du livre
        * @param annee Année de parution du livre
        * @param nbre_exemplaires_disponibles Nombre d'exemplaires disponibles du livre
    */
    void ajouter_livre(MYSQL* conn, char titre[100], char auteur[100], char annee[5], int nbre_exemplaires_disponibles);

#endif // LIVRE_H