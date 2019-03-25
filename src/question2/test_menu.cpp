#include "menu.h"
#include "commande.h"
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;

int calculerCout(const vector<ItemMenu>& solution, const vector<ItemMenu>& menu, int nbAiles, int nbBieres) {
    int cout = 0;
    for (auto item : solution) {
        nbAiles -= item.nbAiles;
        nbBieres -= item.nbBieres;
        cout += item.cout;

        if (find(menu.begin(), menu.end(), item) == menu.end()) {
            return -1;
        }
    }

    if (nbAiles != 0 || nbBieres != 0) {
        return -1;
    }
    return cout;
}

int coutOptimalForceBrute(const vector<ItemMenu>& menu, int nbAiles, int nbBieres) {
    int meilleurCout = numeric_limits<int>::max();
    vector<size_t> count(menu.size(), 0);
    vector<size_t> maxCount;

    maxCount.reserve(menu.size());
    for (ItemMenu item : menu) {
        size_t maxAiles = item.nbAiles > 0 ? nbAiles / item.nbAiles : max(nbAiles, nbBieres);
        size_t maxBieres = item.nbBieres > 0 ? nbBieres / item.nbBieres : max(nbAiles, nbBieres);
        maxCount.push_back(min(maxAiles, maxBieres) + 1);
    }

    while (count.back() < maxCount.back()) {
        vector<ItemMenu> solution;
        for (size_t i = 0; i < menu.size(); i++) {
            for (size_t j = 0; j < count.at(i); j++) {
                solution.push_back(menu.at(i));
            }
        }
        int cout = calculerCout(solution, menu, nbAiles, nbBieres);
        if (cout >= 0 && cout < meilleurCout) {
            meilleurCout = cout;
        }

        count.at(0) += 1;
        for (int i = count.size() - 2; i >= 0; i--) {
            if (count.at(i) == maxCount.at(i)) {
                count.at(i+1) += 1;
                for (size_t j = 0; j <= i; j++) {
                    count.at(j) = 0;
                }
            }
        }
    }

    if (meilleurCout == numeric_limits<int>::max()) {
        return -1;
    }
    return meilleurCout;
}

bool test(const vector<ItemMenu>& menu, int nbAiles, int nbBieres, const string& nom) {
    int coutForceBrute = coutOptimalForceBrute(menu, nbAiles, nbBieres);
    auto solution = commander(menu, nbAiles, nbBieres);

    if (coutForceBrute == -1) {
        if (!solution.empty()) {
            cout << "+0 Le test " << nom << " a echoue avec " << nbAiles << " ailes et " << nbBieres << " bieres." << endl;
            cout << "\t Cette quantite est impossible, la solution devrait etre vide." << endl;
            return false;
        }
        return true;
    }

    int coutEtudiant = calculerCout(solution, menu, nbAiles, nbBieres);
    if (coutEtudiant == -1) {
        cout << "+0 Le test " << nom << " a echoue avec " << nbAiles << " ailes et " << nbBieres << " bieres." << endl;
        cout << "\t La solution retournee est vide alors que le cout de la solution attendue est de " << coutForceBrute << "." << endl;
        return false;
    }

    if (coutForceBrute != coutEtudiant) {
        cout << "+0 Le test " << nom << " a echoue avec " << nbAiles << " ailes et " << nbBieres << "." << endl;
        cout << "\t Cout attendu: " << coutForceBrute << endl;
        cout << "\t Cout obtenu: " << coutEtudiant << endl;
        return false;
    }

    return true;
}

void executerTest(const vector<ItemMenu>& menu, int maxAiles, int maxBieres, const string& nom) {
    bool resultat = true;
    for (int i = 0; i <= maxAiles; i++) {
        for (int j = 0; j <= maxBieres; j++) {
            resultat &= test(menu, i, j, nom);
            if (!resultat) {
                return;
            }
        }
    }
    cout << "+1 Le test " << nom << " a passé." << endl;
}

void testSimple() {
    vector<ItemMenu> menu = {
        {1, 1, 2},
        {2, 2, 5}
    };
    executerTest(menu, 10, 10, "Test simple");
}

void testAlcoolique() {
    vector<ItemMenu> menu = {
            {1, 0, 1},
            {0, 1, 1},
            {6, 1, 7},
            {6, 3, 5},
            {6, 6, 3},
    };
    executerTest(menu, 10, 10, "Test alcoolique");
}

void testEnonce() {
    vector<ItemMenu> menu = {
            {5, 0, 3},
            {5, 1, 4},
            {5, 2, 6},
            {10, 1, 6},
            {10, 2, 10},
            {15, 3, 11},
            {15, 4, 15},
    };
    executerTest(menu, 30, 10, "Test enonce");
}

void testBizarre () {
    vector<ItemMenu> menu = {
            {2, 1, 10},
            {4, 2, 20},
            {6, 3, 35},
            {8, 4, 38},
    };
    executerTest(menu, 20, 10, "Test bizarre");
}

void grosTest () {
    vector<ItemMenu> menu = {
            {0, 1, 4},
            {1, 0, 20},
            {1, 1, 5},
            {5, 3, 15},
            {7, 2, 15},
            {7, 3, 20},
            {8, 2, 18},
            {8, 3, 22},
            {10, 4, 10},
            {12, 6, 21},
    };
    executerTest(menu, 16, 10, "Gros test");
}


int main(int argc, char** argv) {
    testSimple();
    testAlcoolique();
    testEnonce();
    testBizarre();
    grosTest();
    return 0;
}
