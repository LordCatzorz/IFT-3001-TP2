#include <utility>
#include <vector>

#ifndef GRAPHE
#define GRAPHE

struct Graphe {
    std::size_t nbSommets;
    std::vector<std::pair<std::size_t, std::size_t> > arretes;
    Graphe() : nbSommets(0)
    {}
    Graphe(std::size_t nbSommets, const std::vector<std::pair<std::size_t, std::size_t> >& arretes) : nbSommets(nbSommets), arretes(arretes)
    {}
};

#endif
