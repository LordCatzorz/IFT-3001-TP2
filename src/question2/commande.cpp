#include "commande.h"
#include "tableau.hpp"
#include <limits>
#include <assert.h>

using namespace std;


Tableau<int> GenererTableau(const vector<ItemMenu> &menu, unsigned int nbAiles, unsigned int nbBieres)
{
    const unsigned int MaxI = menu.size() +1;
    const unsigned int MaxJ = nbAiles + 1;
    const unsigned int MaxK = nbBieres + 1;

    int ai = -1;
    int bi = -1;
    int ci = -1;

    int prevai = -1;
    int prevbi = -1;

    unsigned int dimensions[3] = {MaxI, MaxJ, MaxK};
    Tableau<int> M(std::vector<unsigned int>(dimensions, dimensions + 3));

    for (int i = 0; i < MaxI; i++)
    {
        for (int j = 0; j < MaxJ; j++)
        {
            for (int k = 0; k < MaxK; k++)
            {
                if (i == 0)
                {
                    if (j==0 && k == 0)
                    {
                        M.at(i, j, k) = 0; // Cas 1 de la récurrence
                    }
                    else
                    {
                        M.at(i, j, k) = -1;
                    }
                }
                else
                {
                    // i - 1, car le tableau commence avec l'item 1
                    ai = menu.at(i - 1).nbAiles;
                    bi = menu.at(i - 1).nbBieres;
                    ci = menu.at(i - 1).cout;

                    prevai = j - ai;
                    prevbi = k - bi;
                    if (prevai < 0)
                    {
                        M.at(i, j, k) = M.at(i-1, j, k); //Cas 2 de la récurrence
                    }
                    else if (prevbi < 0)
                    {
                        M.at(i, j, k) = M.at(i-1, j, k); //Cas 3 de la récurrence
                    }
                    else
                    {
                        int p1 = M.at(i-1, j, k);
                        int p2 = M.at(i, prevai, prevbi);
                        int pf = -1;
                        if (p2 == -1)
                        {
                            pf = p1;
                        } else if (p1 == -1) {
                            pf = p2 + ci;
                        } else {
                            pf = std::min(p2 + ci, p1);
                        }
                         M.at(i, j, k) = pf;
                        
                    }
                }
            }
        }
    }
    return M;
}

// Retourne la liste d'items commandés. La somme des ailes doit être d'exactement nbAiles et la somme des pintes de
// bière doit être exactement nbBieres. Un item peut être commandé plusieurs fois. Pour ce faire, il suffit de le
// mettre deux fois dans le vecteur. Le prix de la commande doit être le plus petit possible.
vector<ItemMenu> commander(const vector<ItemMenu> &menu, unsigned int nbAiles, unsigned int nbBieres)
{
    // Insérer votre code ici
    Tableau<int> M = GenererTableau(menu, nbAiles, nbBieres);
    vector<ItemMenu> resultV = vector<ItemMenu>();
    unsigned int j = nbAiles; //ailes restantes
    unsigned int k = nbBieres; //bieres restantes
    unsigned int i =  menu.size();
    if (M.at(i, j, k) == -1)
    {
        return resultV;; // Si on a -1, la solution n'est pas possible.
    }
    while (i > 0)
    {
        int currentValue = M.at(i, j, k);
        int valueLessItem = M.at(i-1, j, k);
        if (currentValue > valueLessItem)
        {
            // menu commence à l'index 0 pour l'item 1
            ItemMenu item = menu.at(i-1);
            resultV.emplace_back(item);
            j = j - item.nbAiles;
            k = k - item.nbBieres;
        } else {
            i--;
        }
    }

    return resultV;
}


