#include <utility>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>

#include "graphe.h"
#include "reduction.h"

using namespace std;

// Décide si le graphe g1 est un sous-graphe du graphe g2.
bool force_brute(const Graphe& g1, const Graphe& g2) {
    assert(g1.nbSommets <= g2.nbSommets);
    vector<size_t> etiquettes;
    for (size_t i = 0; i < g2.nbSommets; i++) {
        etiquettes.push_back(i);
    }

    while (next_permutation(etiquettes.begin(), etiquettes.end())) {
        bool estSousGraphe = true;
        for (auto arrete : g1.arretes) {
            pair<size_t, size_t> nouvelleArrete(etiquettes.at(arrete.first), etiquettes.at(arrete.second));
            pair<size_t, size_t> nouvelleArreteInverse(etiquettes.at(arrete.second), etiquettes.at(arrete.first));
            if (find(g2.arretes.begin(), g2.arretes.end(), nouvelleArrete) == g2.arretes.end() &&
                find(g2.arretes.begin(), g2.arretes.end(), nouvelleArreteInverse) == g2.arretes.end()) {
                estSousGraphe = false;
                break;
            }
        }

        if (estSousGraphe) {
            return true;
        }
    }
    return false;
}

void test(const Graphe& graphe, bool attendu, const string& nom) {
    Graphe g1;
    Graphe g2;
    reduction(graphe, g1, g2);
    bool resultat = force_brute(g1, g2);

    if (g1.nbSommets > 0 && g2.nbSommets > 0 && resultat == attendu) {
        cout << "+1 point, le test " << nom <<  " a passe." << endl;
    } else {
        cout << "+0 point, le test " << nom << " a echoue" << endl;
    }
}

int main(int argc, char** argv) {
    test(Graphe(5, {{0,1},{1,2},{2,3},{3,0},{1,4},{4,2}}), true, "Graphe 1 (oui)");
    test(Graphe(5, {{0,1},{1,2},{2,3},{3,0},{1,4},{4,3}}), false, "Graphe 2 (non)");
    test(Graphe(6, {{0,1},{1,4},{4,3},{3,2},{2,0},{2,1},{0,3},{4,5}}), false, "Graphe 3 (non)");
    test(Graphe(6, {{1,2},{2,3},{3,1},{2,4},{4,0},{0,5},{5,3},{3,4}}), true, "Graphe enonce (oui)");
    test(Graphe(6, {{1,2},{2,3},{3,1},{2,4},{4,0},{0,5},{3,4}}), false, "Graphe enonce modifie (non)");
    return 0;
}
