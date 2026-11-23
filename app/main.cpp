
#include "carnet/carnet.hpp"
#include "uincampus/saisie.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::vector<double> notes;

    int choix{};

    do
    {
        choix = carnet::afficherMenu();

        switch (choix)
        {
            case 1:
                carnet::ajouter(notes);
                break;

            case 2:
                carnet::afficherNotes(notes);
                break;

            case 3:
                carnet::modifier(notes);
                break;

            case 4:
                carnet::supprimer(notes);
                break;

            case 5:
            {
                std::cout << "\n1. Croissant\n";
                std::cout << "2. Decroissant\n";

                const int sens = uin::lireEntier(
                    "Choisir le sens : ",
                    1,
                    2
                );

                carnet::trier(
                    notes,
                    sens == 1
                        ? carnet::Ordre::Croissant
                        : carnet::Ordre::Decroissant
                );

                std::cout << "Notes triees avec succes.\n";
                break;
            }

            case 6:
                carnet::afficherStatistiques(notes);
                break;

            case 7:
            {
                const double bonus =
                    uin::lireNote("Bonus a appliquer : ");

                carnet::appliquerBonus(notes, bonus);

                std::cout << "Bonus applique avec succes.\n";
                break;
            }

            case 0:
                std::cout << "Fermeture du carnet de notes.\n";
                break;

            default:
                break;
        }

    } while (choix != 0);

    return 0;
}
