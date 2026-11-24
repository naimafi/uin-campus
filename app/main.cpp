
#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/statistiques.hpp"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <span>

namespace
{
    enum class Ordre
    {
        Croissant,
        Decroissant
    };

    void afficherNotes(const uin::TableauDynamique& notes)
    {
        if (notes.taille == 0)
        {
            std::cout << "\nAucune note enregistree.\n";
            return;
        }

        std::cout << "\n===== LISTE DES NOTES =====\n";

        for (std::size_t i = 0; i < notes.taille; ++i)
        {
            std::cout << i + 1 << ". "
                      << std::fixed << std::setprecision(2)
                      << notes.donnees[i] << "/20\n";
        }
    }

    void ajouterNote(uin::TableauDynamique& notes)
    {
        const double note = uin::lireNote("Note a ajouter : ");

        uin::ajouter(notes, note);

        std::cout << "\nNote ajoutee avec succes.\n";
        std::cout << "Taille actuelle : " << notes.taille << '\n';
        std::cout << "Capacite actuelle : " << notes.capacite << '\n';

        afficherNotes(notes);
    }

    void modifierNote(uin::TableauDynamique& notes)
    {
        if (notes.taille == 0)
        {
            std::cout << "\nAucune note a modifier.\n";
            return;
        }

        afficherNotes(notes);

        const int rang = uin::lireEntier(
            "Numero de la note a modifier : ",
            1,
            static_cast<int>(notes.taille)
        );

        const double nouvelleNote =
            uin::lireNote("Nouvelle valeur : ");

        uin::element(
            notes,
            static_cast<std::size_t>(rang - 1)
        ) = nouvelleNote;

        std::cout << "Note modifiee avec succes.\n";
    }

    void supprimerNote(uin::TableauDynamique& notes)
    {
        if (notes.taille == 0)
        {
            std::cout << "\nAucune note a supprimer.\n";
            return;
        }

        afficherNotes(notes);

        const int rang = uin::lireEntier(
            "Numero de la note a supprimer : ",
            1,
            static_cast<int>(notes.taille)
        );

        const std::size_t indice =
            static_cast<std::size_t>(rang - 1);

        for (std::size_t i = indice; i + 1 < notes.taille; ++i)
        {
            uin::element(notes, i) = uin::element(notes, i + 1);
        }

        --notes.taille;

        std::cout << "Note supprimee avec succes.\n";
        std::cout << "Taille actuelle : " << notes.taille << '\n';
        std::cout << "Capacite actuelle : " << notes.capacite << '\n';
    }

    void trierNotes(uin::TableauDynamique& notes, Ordre ordre)
    {
        std::span<double> valeurs{
            notes.donnees,
            notes.taille
        };

        if (ordre == Ordre::Croissant)
        {
            std::sort(valeurs.begin(), valeurs.end());
        }
        else
        {
            std::sort(
                valeurs.begin(),
                valeurs.end(),
                [](double a, double b)
                {
                    return a > b;
                }
            );
        }

        std::cout << "Notes triees avec succes.\n";
    }

    void appliquerBonus(uin::TableauDynamique& notes, double bonus)
    {
        for (std::size_t i = 0; i < notes.taille; ++i)
        {
            uin::element(notes, i) =
                std::clamp(uin::element(notes, i) + bonus, 0.0, 20.0);
        }

        std::cout << "Bonus applique avec succes.\n";
    }

    void afficherMenu()
    {
        std::cout << "\n========== CARNET DE NOTES ==========\n";
        std::cout << "1. Ajouter une note\n";
        std::cout << "2. Afficher les notes\n";
        std::cout << "3. Modifier une note\n";
        std::cout << "4. Supprimer une note\n";
        std::cout << "5. Trier les notes\n";
        std::cout << "6. Afficher les statistiques\n";
        std::cout << "7. Appliquer un bonus\n";
        std::cout << "0. Quitter\n";
    }
}

int main()
{
    uin::TableauDynamique notes;

    try
    {
        int choix{};

        do
        {
            afficherMenu();

            choix = uin::lireEntier("Votre choix : ", 0, 7);

            switch (choix)
            {
                case 1:
                    ajouterNote(notes);
                    break;

                case 2:
                    afficherNotes(notes);
                    break;

                case 3:
                    modifierNote(notes);
                    break;

                case 4:
                    supprimerNote(notes);
                    break;

                case 5:
                {
                    if (notes.taille == 0)
                    {
                        std::cout << "Aucune note a trier.\n";
                        break;
                    }

                    std::cout << "\n1. Croissant\n";
                    std::cout << "2. Decroissant\n";

                    const int sens = uin::lireEntier(
                        "Choisir le sens : ",
                        1,
                        2
                    );

                    trierNotes(
                        notes,
                        sens == 1
                            ? Ordre::Croissant
                            : Ordre::Decroissant
                    );

                    break;
                }

                case 6:
                {
                    if (notes.taille == 0)
                    {
                        std::cout << "Aucune note disponible.\n";
                        break;
                    }

                    const auto resultats =
                        uin::calculerStatistiques(uin::vue(notes));

                    uin::afficherStatistiques(
                        "Carnet de notes",
                        resultats,
                        static_cast<int>(notes.taille)
                    );

                    break;
                }

                case 7:
                {
                    if (notes.taille == 0)
                    {
                        std::cout << "Aucune note pour appliquer un bonus.\n";
                        break;
                    }

                    const double bonus =
                        uin::lireNote("Bonus a appliquer : ");

                    appliquerBonus(notes, bonus);
                    break;
                }

                case 0:
                    std::cout << "\nFermeture du carnet de notes.\n";
                    break;
            }

        } while (choix != 0);
    }
    catch (const std::exception& erreur)
    {
        std::cerr << "\nErreur : " << erreur.what() << '\n';
        uin::liberer(notes);
        return 1;
    }

    uin::liberer(notes);

    return 0;
}
