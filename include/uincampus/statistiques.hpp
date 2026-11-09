#pragma once

#include "uincampus/regles.hpp"

#include <array>
#include <vector>
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
        const std::vector<double>& notes
    );

    void afficherStatistiques(
        std::string_view nomUniteEnseignement,
        const Statistiques& resultats,
        int nombreEtudiants
    );
}