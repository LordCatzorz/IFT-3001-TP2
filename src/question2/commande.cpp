#include "commande.h"
#include "tableau.hpp"
#include <limits>
#include <assert.h>

using namespace std;

typedef float ctableau; //Type "Contenu de case de tableau"

Tableau<ctableau> genererTableau(const vector<ItemMenu> &menu, unsigned int nbAiles, unsigned int nbBieres)
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
    Tableau<ctableau> M(std::vector<unsigned int>(dimensions, dimensions + 3));

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
                        M.at(i, j, k) = std::numeric_limits<ctableau>::infinity(); // Cas 2 de la récurrence
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
                        M.at(i, j, k) = M.at(i-1, j, k); //Cas 3 de la récurrence
                    }
                    else if (prevbi < 0)
                    {
                        M.at(i, j, k) = M.at(i-1, j, k); //Cas 4 de la récurrence
                    }
                    else
                    {
                        ctableau p1 = M.at(i-1, j, k); //Prix en ne prenant pas en compte ce menu.
                        ctableau p2 = M.at(i, prevai, prevbi) + ci; // Prix en prenant compte de ce menu.
                        M.at(i, j, k) = std::min(p1, p2); //Cas 5 de la récurrence
                    }
                }
            }
        }
    }
    return M;
}

vector<ItemMenu> solutionnerTableau(const vector<ItemMenu> &menu, unsigned int nbAiles, unsigned int nbBieres, Tableau<ctableau> tableauM)
{
    vector<ItemMenu> resultV = vector<ItemMenu>();
    unsigned int i =  menu.size();
    unsigned int j = nbAiles; //ailes restantes
    unsigned int k = nbBieres; //bieres restantes
    
    if (tableauM.at(i, j, k) == std::numeric_limits<ctableau>::infinity())
    {
        return resultV;; // Si on a -1, la solution n'est pas possible.
    }
    while (i > 0)
    {
        ctableau currentValue = tableauM.at(i, j, k);
        ctableau valueLessItem = tableauM.at(i-1, j, k);
        if (currentValue != valueLessItem)
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

// Retourne la liste d'items commandés. La somme des ailes doit être d'exactement nbAiles et la somme des pintes de
// bière doit être exactement nbBieres. Un item peut être commandé plusieurs fois. Pour ce faire, il suffit de le
// mettre deux fois dans le vecteur. Le prix de la commande doit être le plus petit possible.
vector<ItemMenu> commander(const vector<ItemMenu> &menu, unsigned int nbAiles, unsigned int nbBieres)
{
    // Insérer votre code ici
    Tableau<ctableau> M = genererTableau(menu, nbAiles, nbBieres);
    return solutionnerTableau(menu, nbAiles, nbBieres, M);
}


