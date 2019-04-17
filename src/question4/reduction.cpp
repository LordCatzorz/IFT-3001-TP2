#include "reduction.h"

using namespace std;

// Input:
//      grapheCycleHamiltonien: Un graphe du problème du Cycle Hamiltonien
// Output:
//      grapheG1: G1 est passé en référence et vous devez le modifier pour produire l'output.
//      grapheG2  G2 est passé en référence et vous devez le modifier pour produire l'output.
void reduction(const Graphe& grapheCycleHamiltonien, Graphe& grapheG1, Graphe& grapheG2) {
  for(size_t i = 0; i < grapheCycleHamiltonien.nbSommets; i++)
  {
    grapheG1.arretes.emplace_back(pair<size_t, size_t>(i, (i+1)%grapheCycleHamiltonien.nbSommets));
  }
  grapheG1.nbSommets = grapheCycleHamiltonien.nbSommets;
  
  grapheG2 = Graphe(grapheCycleHamiltonien);
}
