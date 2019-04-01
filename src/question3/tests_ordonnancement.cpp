#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "ordonnancement.hpp"

// Retourne vrai si le vecteur solution est une solution valide a l'instance du probleme donnee par les vecteurs temps_sortie et echeances.
bool solutionValide(const std::vector<unsigned int>& temps_sortie, const std::vector<unsigned int>& echeances, const std::vector<unsigned int>& solution) {
  // Test si l'instance est valide
  const unsigned int nb_travaux = temps_sortie.size(); // Il y a autant de travaux que de jours
  assert(temps_sortie.size() == echeances.size());
  for (unsigned int i = 0; i < nb_travaux; i++) {
    assert(temps_sortie[i] < nb_travaux);
    assert(echeances[i] < nb_travaux);
  }

  if (solution.size() != nb_travaux) {
    std::cerr << "Certains travaux n'ont pas ete planifies" << std::endl;
    return false;
  }
  std::vector<bool> jour_utilise(nb_travaux, false);
  for (unsigned int i = 0; i < nb_travaux; i++) {
    if (solution[i] < temps_sortie[i]) {
      std::cerr << "Le travail " << i << " est realise trop tot" << std::endl;
      return false;
    }
    if (echeances[i] < solution[i]) {
      std::cerr << "Le travail " << i << " est realise trop tard" << std::endl;
      return false;
    }
    if (jour_utilise[solution[i]]) {
      std::cerr << "Plusieurs travaux s'executent au jour " << solution[i] << std::endl;
      return false;
    }
    jour_utilise[solution[i]] = true;
  }
  return true;    
}

void imprimeVecteur(std::vector<unsigned int>::const_iterator begin, const std::vector<unsigned int>::const_iterator& end) {
  while (begin != end) {
    std::cerr << " " << *begin;
    begin++;
  }
}

bool testGenerique(const std::string& nom_du_test, const unsigned int* temps_sorties, const unsigned int* echeances, unsigned int nb_travaux) {
  bool resultat = false;
  const std::vector<unsigned int> vecteur_temps_sorties(temps_sorties, temps_sorties + nb_travaux);
  const std::vector<unsigned int> vecteur_echeances(echeances, echeances + nb_travaux);
  std::cerr << nom_du_test << std::endl << "Temps de sortie:";
  imprimeVecteur(vecteur_temps_sorties.begin(), vecteur_temps_sorties.end());
  std::cerr << std::endl << "Echeances:";
  imprimeVecteur(vecteur_echeances.begin(), vecteur_echeances.end());
  std::cerr << std::endl;
  try {
    std::vector<unsigned int> solution;
    ordonnancement(vecteur_temps_sorties, vecteur_echeances, solution);
    std::cerr << "Solution retournee:";
    imprimeVecteur(solution.begin(), solution.end());
    std::cerr << std::endl;
    resultat = solutionValide(vecteur_temps_sorties, vecteur_echeances, solution);
  } catch (...) {
  }
  if (resultat) {
    std::cerr << "+1 Le test a passe" << std::endl;
  } else {
    std::cerr << "+0 Le test a echoue" << std::endl;
  }
  std::cerr << std::endl;
  return resultat;
}

bool testEnonce(void) {
  const unsigned int sorties[5] = {1, 1, 0, 2, 0};
  const unsigned int echeances[5] = {2, 2, 4, 4, 1};
  return testGenerique("Test enonce", sorties, echeances, 5);
}

bool deuxiemeTest(void) {
  const unsigned int sorties[6] = {0, 0, 1, 1, 2, 2};
  const unsigned int echeances[6] = {5, 5, 4, 4, 3, 3};
  return testGenerique("Deuxieme test", sorties, echeances, 6);
}

bool troisiemeTest(void) {
  const unsigned int sorties[6] =   {2, 0, 0, 0, 3, 3};
  const unsigned int echeances[6] = {3, 2, 2, 2, 5, 5};
  return testGenerique("Troisieme test", sorties, echeances, 6);
}

bool sortiesIdentiques(void) {
  const unsigned int sorties[6] = {0, 0, 0, 0, 0, 0};
  const unsigned int echeances[6] = {2, 0, 3, 1, 5, 4};
  return testGenerique("Sorties identiques", sorties, echeances, 6);
}

bool exempleComplexe(void) {
  const unsigned int sorties[5] = {3, 1, 1, 1, 0};
  const unsigned int echeances[5] = {4, 3, 3, 3, 1};
  return testGenerique("Exemple complexe", sorties, echeances, 5);
}

int main(void) {
  unsigned int total = 0;
  testEnonce();
  deuxiemeTest();
  troisiemeTest();
  sortiesIdentiques();
  exempleComplexe();

  return 0;
}
