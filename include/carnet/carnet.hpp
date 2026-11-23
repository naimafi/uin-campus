
#pragma once

#include <vector>

namespace carnet
{
    // Ordre de tri des notes
    enum class Ordre
    {
        Croissant,
        Decroissant
    };

    // Structure contenant les statistiques
    struct Statistiques
    {
        double minimum{};
        double maximum{};
        double moyenne{};
        int nbValidees{};
    };

    // Fonctions de calcul
    [[nodiscard]] Statistiques calculerStatistiques(
        const std::vector<double>& notes
    );

    void appliquerBonus(
        std::vector<double>& notes,
        double bonus
    );

    void trier(
        std::vector<double>& notes,
        Ordre ordre
    );

    // Fonctions de gestion du carnet
    void afficherNotes(const std::vector<double>& notes);

    void ajouter(std::vector<double>& notes);

    void modifier(std::vector<double>& notes);

    void supprimer(std::vector<double>& notes);

    void afficherStatistiques(const std::vector<double>& notes);

    [[nodiscard]] int afficherMenu();
}
