
#include "uincampus/calculs.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/statistiques.hpp"

#include <exception>
#include <iostream>
#include <string>

int main()
{
    uin::TableauDynamique notes;

    try
    {
        std::cout << "====================================\n";
        std::cout << "   STATISTIQUES D'UNE SERIE DE NOTES\n";
        std::cout << "====================================\n";

        const std::string nomUniteEnseignement =
            uin::lireTexte(
                "Nom de l'unite d'enseignement : "
            );

        const int nombreEtudiants =
            uin::lireEntier(
                "Nombre d'etudiants (1 a 200) : ",
                1,
                200
            );

        for (int i = 0; i < nombreEtudiants; ++i)
        {
            std::cout << "\nEtudiant " << i + 1 << '\n';

            const double note =
                uin::lireNote("Entrez la note : ");

            uin::ajouter(notes, note);

            std::cout << "Taille : " << notes.taille
                      << " | Capacite : " << notes.capacite
                      << '\n';
        }

        const uin::Statistiques resultats =
            uin::calculerStatistiques(uin::vue(notes));

        uin::afficherStatistiques(
            nomUniteEnseignement,
            resultats,
            nombreEtudiants
        );
    }
    catch (const std::exception& erreur)
    {
        uin::liberer(notes);

        std::cerr << "Erreur : " << erreur.what() << '\n';
        return 1;
    }

    uin::liberer(notes);

    return 0;
}
