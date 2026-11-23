
#include "carnet/carnet.hpp"
#include "uincampus/saisie.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>

namespace carnet
{
    // CALCULS : aucune entree-sortie
    

    [[nodiscard]] Statistiques calculerStatistiques(
        const std::vector<double>& notes
    )
    {
        const auto [minimum, maximum] =
            std::minmax_element(notes.begin(), notes.end());

        const double somme =
            std::accumulate(notes.begin(), notes.end(), 0.0);

        int nbValidees{};

        for (double note : notes)
        {
            if (note >= 10.0)
            {
                ++nbValidees;
            }
        }

        return {
            *minimum,
            *maximum,
            somme / static_cast<double>(notes.size()),
            nbValidees
        };
    }

    void appliquerBonus(
        std::vector<double>& notes,
        double bonus
    )
    {
        std::for_each(
            notes.begin(),
            notes.end(),
            [bonus](double& note)
            {
                note = std::clamp(note + bonus, 0.0, 20.0);
            }
        );
    }

    void trier(
        std::vector<double>& notes,
        Ordre ordre
    )
    {
        if (ordre == Ordre::Croissant)
        {
            std::sort(notes.begin(), notes.end());
        }
        else
        {
            std::sort(
                notes.begin(),
                notes.end(),
                [](double a, double b)
                {
                    return a > b;
                }
            );
        }
    }

   
    // INTERFACE UTILISATEUR

    void afficherNotes(const std::vector<double>& notes)
    {
        if (notes.empty())
        {
            std::cout << "Aucune note.\n";
            return;
        }

        std::cout << "\n===== LISTE DES NOTES =====\n";

        for (std::size_t i = 0; i < notes.size(); ++i)
        {
            std::cout << std::setw(3) << i + 1
                      << ". "
                      << std::fixed
                      << std::setprecision(2)
                      << notes[i] << '\n';
        }
    }

    void ajouter(std::vector<double>& notes)
    {
        const double note =
            uin::lireNote("Note a ajouter : ");

        notes.push_back(note);

        std::cout << "Note ajoutee avec succes.\n";
    }

    void modifier(std::vector<double>& notes)
    {
        if (notes.empty())
        {
            std::cout << "Aucune note a modifier.\n";
            return;
        }

        afficherNotes(notes);

        const int rang = uin::lireEntier(
            "Numero de la note a modifier : ",
            1,
            static_cast<int>(notes.size())
        );

        notes[static_cast<std::size_t>(rang - 1)] =
            uin::lireNote("Nouvelle valeur : ");

        std::cout << "Note modifiee avec succes.\n";
    }

    void supprimer(std::vector<double>& notes)
    {
        if (notes.empty())
        {
            std::cout << "Aucune note a supprimer.\n";
            return;
        }

        afficherNotes(notes);

        const int rang = uin::lireEntier(
            "Numero de la note a supprimer : ",
            1,
            static_cast<int>(notes.size())
        );

        notes.erase(notes.begin() + (rang - 1));

        std::cout << "Note supprimee avec succes.\n";
    }

    void afficherStatistiques(const std::vector<double>& notes)
    {
        if (notes.empty())
        {
            std::cout << "Aucune note disponible.\n";
            return;
        }

        const auto [minimum, maximum, moyenne, nbValidees] =
            calculerStatistiques(notes);

        std::cout << "\n===== STATISTIQUES =====\n";

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Minimum : " << minimum << '\n';
        std::cout << "Maximum : " << maximum << '\n';
        std::cout << "Moyenne : " << moyenne << '\n';

        std::cout << "Notes validees : "
                  << nbValidees << "/"
                  << notes.size() << '\n';
    }

    [[nodiscard]] int afficherMenu()
    {
        std::cout << "\n===== CARNET DE NOTES =====\n";
        std::cout << "1. Ajouter une note\n";
        std::cout << "2. Afficher les notes\n";
        std::cout << "3. Modifier une note\n";
        std::cout << "4. Supprimer une note\n";
        std::cout << "5. Trier les notes\n";
        std::cout << "6. Statistiques\n";
        std::cout << "7. Appliquer un bonus\n";
        std::cout << "0. Quitter\n";

        return uin::lireEntier("Votre choix : ", 0, 7);
    }
}
