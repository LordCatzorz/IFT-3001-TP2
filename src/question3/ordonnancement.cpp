#include <assert.h>
#include <vector>
// Vous pouvez inclure d'autres librairies, pourvu qu'elles proviennent de la STL.


// Calcule l'ordonnancement des travaux.
// Entrees:
//   temps_sortie: le travail i peut commencer au jour temps_sortie[i]
//   echeances: le travail i peut se faire au plus tard au jour echeances[i]
// Sortie:
//   solution: le travail i se realise au jour solution[i]
void ordonnancement(const std::vector<unsigned int>& temps_sortie, const std::vector<unsigned int>& echeances, std::vector<unsigned int>& solution) {
  const unsigned int nb_travaux = temps_sortie.size(); // Il y a autant de jours que de travaux.
  assert(echeances.size() == nb_travaux);
  for (unsigned int i = 0; i < nb_travaux; i++) {
    assert(temps_sortie[i] <= echeances[i]);
    assert(echeances[i] < nb_travaux);
  }
  
  // Inserez votre code ici.

}

