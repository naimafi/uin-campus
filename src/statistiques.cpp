#include "uincampus/statistiques.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

namespace uin
{
    Statistiques calculerStatistiques(
        const std::vector<double>& notes
    )
    {
        Statistiques resultats{};

        if (notes.empty())
        {
            return resultats;
        }

        resultats.minimum = *std::min_element(
            notes.begin(),
            notes.end()
        );

        resultats.maximum = *std::max_element(
            notes.begin(),
            notes.end()
        );

        double somme{};

        for (double note : notes)
        {
            somme += note;

            if (note >= seuilAdmission)
            {
                ++resultats.nombreAdmis;
            }

            const Mention mention = mentionPour(note);

            const std::size_t indice =
                static_cast<std::size_t>(mention);

            ++resultats.repartition[indice];
        }

        const double nombreNotes =
            static_cast<double>(notes.size());

        resultats.moyenne = somme / nombreNotes;

        double sommeCarres{};

        for (double note : notes)
        {
            const double difference =
                note - resultats.moyenne;

            sommeCarres += difference * difference;
        }

        resultats.ecartType =
            std::sqrt(sommeCarres / nombreNotes);

        resultats.pourcentageAdmis =
            (static_cast<double>(resultats.nombreAdmis)
             / nombreNotes) * 100.0;

        return resultats;
    }

    
void afficherStatistiques(
    std::string_view nomUniteEnseignement,
    const Statistiques& resultats,
    int nombreEtudiants
)
{
    std::cout << "\n====================================\n";
    std::cout << "       STATISTIQUES DES NOTES\n";
    std::cout << "====================================\n";

    std::cout << "Unite d'enseignement : "
              << nomUniteEnseignement << '\n';

    std::cout << "Nombre d'etudiants : "
              << nombreEtudiants << '\n';

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nNote minimale : "
              << resultats.minimum << '\n';

    std::cout << "Note maximale : "
              << resultats.maximum << '\n';

    std::cout << "Moyenne : "
              << resultats.moyenne << '\n';

    std::cout << "Ecart-type : "
              << resultats.ecartType << '\n';

    std::cout << "\nNombre d'admis : "
              << resultats.nombreAdmis << '\n';

    std::cout << "Pourcentage d'admis : "
              << resultats.pourcentageAdmis << " %\n";

    std::cout << "\nREPARTITION DES MENTIONS\n";
    std::cout << "------------------------------------\n";

    for (std::size_t i = 0; i < nbMentions; ++i)
    {
        const Mention mention =
            static_cast<Mention>(i);

        const int effectif =
            resultats.repartition[i];

        std::cout << std::left
                  << std::setw(15)
                  << libelle(mention)
                  << " : "
                  << effectif
                  << (effectif <= 1 ? " etudiant" : " etudiants")
                  << '\n';
    }

    std::cout << "====================================\n";
}

}