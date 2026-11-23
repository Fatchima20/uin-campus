#include <cassert>
#include <cstddef>
#include <print>
#include <vector>

struct TableauDynamique {
    double* donnees{nullptr};
    std::size_t taille{0};
    std::size_t capacite{0};
};

void ajouter(TableauDynamique& t, double valeur)
{
    if (t.taille == t.capacite) {
        const std::size_t nouvelleCapacite = (t.capacite == 0) ? 4 : t.capacite * 2;
        double* nouveau = new double[nouvelleCapacite];
        for (std::size_t i{0}; i < t.taille; ++i) {
            nouveau[i] = t.donnees[i];
        }
        delete[] t.donnees;
        t.donnees = nouveau;
        t.capacite = nouvelleCapacite;
    }
    t.donnees[t.taille] = valeur;
    ++t.taille;
}

void liberer(TableauDynamique& t)
{
    delete[] t.donnees;
    t.donnees = nullptr;
    t.taille = 0;
    t.capacite = 0;
}

double& element(TableauDynamique& t, std::size_t i)
{
    assert(i < t.taille && "element() : indice hors limites");
    return t.donnees[i];
}

int main()
{
    // Partie A : tableau dynamique « à la C »
    std::println("--- Partie A : tableau dynamique à la main ---");
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + i);
        std::println("taille {:>2}, capacité {:>2}", notes.taille, notes.capacite);
    }
    std::println("element(3) = {}", element(notes, 3));

    // Partie B : enlever les deux « // » ci-dessous pour provoquer le double-free
    // TableauDynamique copie = notes;
    // liberer(copie);

    liberer(notes);

    // Partie C : la même chose avec std::vector
    std::println("--- Partie C : std::vector ---");
    std::vector<double> v;
    for (int i{0}; i < 10; ++i) {
        v.push_back(10.0 + i);
        std::println("taille {:>2}, capacité {:>2}", v.size(), v.capacity());
    }
    std::vector<double> copieV = v;
    std::println("copie : {} éléments", copieV.size());
}