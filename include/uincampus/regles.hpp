#pragma once

#include <cstddef>
#include <string_view>

namespace uin
{
    constexpr double noteMin = 0.0;
    constexpr double noteMax = 20.0;
    constexpr double seuilAdmission = 10.0;

    constexpr std::size_t nbMentions = 5;

    enum class Mention
    {
        Ajourne,
        Passable,
        AssezBien,
        Bien,
        TresBien
    };

    Mention mentionPour(double moyenne);

    std::string_view libelle(Mention mention);
}