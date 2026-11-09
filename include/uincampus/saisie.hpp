#pragma once

#include <string>
#include <string_view>

namespace uin
{
    std::string lireTexte(std::string_view invitation);

    int lireEntier(
        std::string_view invitation,
        int minimum,
        int maximum
    );

    double lireNote(std::string_view invitation);
}