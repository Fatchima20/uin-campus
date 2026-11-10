
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstddef>

// Constantes du programme
constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;

// Les differentes mentions
enum class Mention
{
    Ajourne,
    Passable,
    AssezBien,
    Bien,
    TresBien
};

// Fonction pour lire le nombre d'etudiants
int lireNombreEtudiants()
{
    std::string saisie;
    int nombre = 0;

    while (true)
    {
        std::cout << "Nombre d'etudiants (1 a 200) : ";
        std::getline(std::cin, saisie);

        std::istringstream flux(saisie);

        if (flux >> nombre)
        {
            flux >> std::ws;

            if (flux.eof() && nombre >= 1 && nombre <= 200)
            {
                return nombre;
            }
        }

        std::cout << "Nombre invalide. Recommencez.\n";
    }
}

// Fonction pour lire et verifier une note
double lireNote(int numero)
{
    std::string saisie;
    double note = 0.0;

    while (true)
    {
        std::cout << "Note de l'etudiant " << numero << " : ";
        std::getline(std::cin, saisie);

        std::replace(
            saisie.begin(),
            saisie.end(),
            ',',
            '.'
        );

        std::istringstream flux(saisie);

        if (flux >> note)
        {
            flux >> std::ws;

            if (flux.eof()
                && std::isfinite(note)
                && note >= noteMin
                && note <= noteMax)
            {
                return note;
            }
        }

        std::cout << "Note invalide. Entrez une note entre 0 et 20.\n";
    }
}

// Fonction qui determine la mention
Mention mentionPour(double note)
{
    if (note < 10.0)
        return Mention::Ajourne;

    if (note < 12.0)
        return Mention::Passable;

    if (note < 14.0)
        return Mention::AssezBien;

    if (note < 16.0)
        return Mention::Bien;

    return Mention::TresBien;
}

// Fonction qui retourne le nom de la mention
std::string libelle(Mention mention)
{
    switch (mention)
    {
        case Mention::Ajourne:
            return "Ajourne";

        case Mention::Passable:
            return "Passable";

        case Mention::AssezBien:
            return "Assez bien";

        case Mention::Bien:
            return "Bien";

        case Mention::TresBien:
            return "Tres bien";
    }

    return "";
}

// Programme principal
int main()
{
    std::string nomUE;

    std::cout << "===== STATISTIQUES DES NOTES =====\n";

    std::cout << "Nom de l'UE : ";
    std::getline(std::cin, nomUE);

    int nbEtudiants = lireNombreEtudiants();

    // Creation du tableau des notes
    std::vector<double> notes;

    notes.reserve(
        static_cast<std::size_t>(nbEtudiants)
    );

    // Saisie des notes
    std::cout << "\n===== SAISIE DES NOTES =====\n";

    for (int i = 0; i < nbEtudiants; ++i)
    {
        notes.push_back(lireNote(i + 1));
    }

    // Calcul de la somme
    double somme = 0.0;

    for (double note : notes)
    {
        somme += note;
    }

    // Calcul de la moyenne
    double moyenne =
        somme / static_cast<double>(nbEtudiants);

    // Recherche du minimum et du maximum
    double minimum =
        *std::min_element(notes.begin(), notes.end());

    double maximum =
        *std::max_element(notes.begin(), notes.end());

    // Calcul de l'ecart-type
    double sommeCarres = 0.0;

    for (double note : notes)
    {
        double difference = note - moyenne;
        sommeCarres += difference * difference;
    }

    double ecartType = std::sqrt(
        sommeCarres / static_cast<double>(nbEtudiants)
    );

    // Comptage des admis et des mentions
    int nbAdmis = 0;

    std::array<std::size_t, 5> compteurs{};

    for (double note : notes)
    {
        if (note >= seuilValidation)
        {
            ++nbAdmis;
        }

        Mention mention = mentionPour(note);

        std::size_t indice =
            static_cast<std::size_t>(mention);

        ++compteurs[indice];
    }

    // Calcul du pourcentage d'admis
    double pourcentage =
        static_cast<double>(nbAdmis)
        / static_cast<double>(nbEtudiants) * 100.0;

    // Affichage des statistiques
    std::cout << "\n===== RESULTATS =====\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "UE : " << nomUE << '\n';

    std::cout << "Nombre d'etudiants : "
              << nbEtudiants << '\n';

    std::cout << "Note minimale : "
              << minimum << '\n';

    std::cout << "Note maximale : "
              << maximum << '\n';

    std::cout << "Moyenne : "
              << moyenne << '\n';

    std::cout << "Ecart-type : "
              << ecartType << '\n';

    std::cout << "Nombre d'admis : "
              << nbAdmis << '\n';

    std::cout << "Pourcentage d'admis : "
              << pourcentage << " %\n";

    // Affichage de l'histogramme
    std::cout << "\n===== HISTOGRAMME DES MENTIONS =====\n";

    const std::array<Mention, 5> mentions = {
        Mention::Ajourne,
        Mention::Passable,
        Mention::AssezBien,
        Mention::Bien,
        Mention::TresBien
    };

    for (std::size_t i = 0; i < mentions.size(); ++i)
    {
        std::cout << std::left
                  << std::setw(12)
                  << libelle(mentions[i])
                  << " : "
                  << std::string(compteurs[i], '*')
                  << " (" << compteurs[i] << ")\n";
    }

    std::cout << "\n===== FIN DU PROGRAMME =====\n";

    return 0;
}
