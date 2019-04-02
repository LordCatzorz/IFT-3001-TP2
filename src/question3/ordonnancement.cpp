#include <assert.h>
#include <vector>
#include <queue>
#include <functional>
// Vous pouvez inclure d'autres librairies, pourvu qu'elles proviennent de la STL.

typedef unsigned int uint;

class Travail
{
  private:
    uint numero;
    uint jourAnnonce;
    uint jourDu;
  public:
    Travail(uint _numero, uint _jourAnnonce, uint _jourDu);
    uint GetNumero() const;
    uint GetJourAnnonce() const;
    uint GetJourDu() const;
};

Travail::Travail(uint _numero, uint _jourAnnonce, uint _jourDu)
{
  this->numero = _numero;
  this->jourAnnonce = _jourAnnonce;
  this->jourDu = _jourDu;
}

uint Travail::GetNumero() const
{
  return this->numero;
}

uint Travail::GetJourAnnonce() const
{
  return this->jourAnnonce;
}

uint Travail::GetJourDu() const
{
  return this->jourDu;
}

/*
  fctCompare devrait être en Theta(1) pour que le tri s'éffectue en Theta(n)
*/
void triParDenombrement(std::vector<Travail*>& S_solution, const uint l_lowerBound, const uint u_upperBound, const std::vector<Travail*>& A_elements, std::function<uint(const Travail*)> fctCompare)
{
  // Il y a le même nombre d'élément que l'étendu des éléments possibles. Ex, 5 élément = étendu 0-4
  assert(u_upperBound - l_lowerBound == A_elements.size() - 1);
  
  uint rangeMax = A_elements.size(); //range = n par définition du problème.
  std::vector<uint> D_distribution;
  
  D_distribution.resize(rangeMax); // Theta(n)
  // Initialisation
  for(uint j = 0; j < rangeMax; j++) // Theta(n)
  {
    D_distribution[j] = 0;
  }

  //Fréquence
  for (uint i = 0; i < rangeMax; i++) //Theta(n) si fctCompare in Theta(1)
  {
    D_distribution[fctCompare(A_elements[i]) - l_lowerBound]++;
  }

  //Distribution
  for(uint j = 1; j < rangeMax; j++) //Theta(n)
  {
    D_distribution[j] = D_distribution[j-1] + D_distribution[j];
  }

  S_solution.resize(rangeMax); //Theta(n)
  //Solution
  for(int i = rangeMax - 1; i >= 0; i--) //Theta(n) is fctCompare in Theta(1)
  {
    uint j = fctCompare(A_elements[i]) - l_lowerBound;
    D_distribution[j]--;
    S_solution[D_distribution[j]] = A_elements[i];
  }
}

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
  std::vector<Travail*> travaux;
  for(uint i = 0; i < nb_travaux; i++)
  {
    travaux.emplace_back(new Travail(i, temps_sortie[i], echeances[i]));
  }
  std::function<uint(const Travail*)> f1 = [] (const Travail* t) { return t->GetJourDu();};
  std::function<uint(const Travail*)> f2 = [] (const Travail* t) { return t->GetJourAnnonce();};

  std::vector<Travail*> sol;
  triParDenombrement(sol, 0, nb_travaux - 1, travaux, f1);

  solution.resize(nb_travaux);

  for(uint i = 0; i < nb_travaux; i++)
  {
    solution.at(sol[i]->GetNumero()) = i;
  }
}