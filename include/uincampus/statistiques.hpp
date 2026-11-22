
#pragma once

#include "uincampus/regles.hpp"

#include <array>
#include <span>
#include <string_view>

namespace uin
{
    struct Statistiques
    {
        double minimum{};
        double maximum{};
        double moyenne{};
        double ecartType{};

        int nombreAdmis{};
        double pourcentageAdmis{};

        std::array<int, nbMentions> repartition{};
    };

    Statistiques calculerStatistiques(
        std::span<const double> notes
    );

    void afficherStatistiques(
        std::string_view nomUniteEnseignement,
        const Statistiques& resultats,
        int nombreEtudiants
    );
}
