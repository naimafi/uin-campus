
#include "uincampus/calculs.hpp"

#include <cassert>

namespace uin
{
    void ajouter(TableauDynamique& tableau, double valeur)
    {
        if (tableau.taille == tableau.capacite)
        {
            const std::size_t nouvelleCapacite =
                (tableau.capacite == 0)
                    ? 4
                    : tableau.capacite * 2;

            double* nouveau = new double[nouvelleCapacite];

            for (std::size_t i = 0; i < tableau.taille; ++i)
            {
                nouveau[i] = tableau.donnees[i];
            }

            delete[] tableau.donnees;

            tableau.donnees = nouveau;
            tableau.capacite = nouvelleCapacite;
        }

        tableau.donnees[tableau.taille] = valeur;
        ++tableau.taille;
    }

    void liberer(TableauDynamique& tableau)
    {
        delete[] tableau.donnees;

        tableau.donnees = nullptr;
        tableau.taille = 0;
        tableau.capacite = 0;
    }

    double& element(TableauDynamique& tableau, std::size_t indice)
    {
        assert(indice < tableau.taille
               && "element() : indice hors limites");

        return tableau.donnees[indice];
    }

    std::span<const double> vue(const TableauDynamique& tableau)
    {
        return {tableau.donnees, tableau.taille};
    }
}
