#include "uincampus/saisie.hpp"
#include "uincampus/regles.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cmath>


namespace uin
{
    std::string lireTexte(std::string_view invitation)
    {
        std::string texte;

        while (true)
        {
            std::cout << invitation;

            if (!std::getline(std::cin, texte))
            {
                throw std::runtime_error("Erreur de lecture.");
            }

            if (!texte.empty())
            {
                return texte;
            }

            std::cout << "La saisie ne peut pas etre vide.\n";
        }
    }

    int lireEntier(
        std::string_view invitation,
        int minimum,
        int maximum
    )
    {
        std::string ligne;

        while (true)
        {
            std::cout << invitation;

            if (!std::getline(std::cin, ligne))
            {
                throw std::runtime_error("Erreur de lecture.");
            }

            std::istringstream flux(ligne);

            int valeur{};
            char reste{};

            if (flux >> valeur && !(flux >> reste)
                && valeur >= minimum && valeur <= maximum)
            {
                return valeur;
            }

            std::cout << "Saisie invalide. Entrez un entier entre "
                      << minimum << " et " << maximum << ".\n";
        }
    }

    double lireNote(std::string_view invitation)
    {
        std::string ligne;

        while (true)
        {
            std::cout << invitation;

            if (!std::getline(std::cin, ligne))
            {
                throw std::runtime_error("Erreur de lecture.");
            }

            std::replace(
                ligne.begin(),
                ligne.end(),
                ',',
                '.'
            );

            std::istringstream flux(ligne);

            double note{};
            char reste{};

            if (flux >> note && !(flux >> reste)
                && std::isfinite(note)
                && note >= noteMin
                && note <= noteMax)
            {
                return note;
            }

            std::cout << "Note invalide. Entrez une note entre 0 et 20.\n";
        }
    }
}