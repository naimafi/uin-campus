#include "uincampus/saisie.hpp"
#include "uincampus/statistiques.hpp"

#include <iostream>
#include <vector>
#include <exception>

int main()
{
    try
    {
        std::cout << "====================================\n";
        std::cout << "   STATISTIQUES D'UNE SERIE DE NOTES\n";
        std::cout << "====================================\n";

        const std::string nomUniteEnseignement =
    uin::lireTexte("Nom de l'unite d'enseignement : ");

        const int nombreEtudiants =
            uin::lireEntier(
                "Nombre d'etudiants (1 a 200) : ",
                1,
                200
            );

        std::vector<double> notes;

        notes.reserve(
            static_cast<std::size_t>(nombreEtudiants)
        );

        for (int i = 0; i < nombreEtudiants; ++i)
        {
            std::cout << "\nEtudiant " << i + 1 << '\n';

            const double note =
                uin::lireNote("Entrez la note : ");

            notes.push_back(note);
        }

        const uin::Statistiques resultats =
            uin::calculerStatistiques(notes);

       uin::afficherStatistiques(
    nomUniteEnseignement,
    resultats,
    nombreEtudiants
);
    }
    catch (const std::exception& erreur)
    {
        std::cerr << "Erreur : " << erreur.what() << '\n';
        return 1;
    }

    return 0;
}