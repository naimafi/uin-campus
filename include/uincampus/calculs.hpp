
#pragma once

#include <cstddef>
#include <span>

namespace uin
{
    struct TableauDynamique
    {
        double* donnees{nullptr};
        std::size_t taille{0};
        std::size_t capacite{0};
    };

    void ajouter(TableauDynamique& tableau, double valeur);

    void liberer(TableauDynamique& tableau);

    double& element(TableauDynamique& tableau, std::size_t indice);

    std::span<const double> vue(const TableauDynamique& tableau);
}
