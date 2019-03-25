#ifndef MENU
#define MENU

struct ItemMenu {
    int nbAiles;
    int nbBieres;
    int cout;

    bool operator==(const ItemMenu& rhs) const {
        return nbAiles == rhs.nbAiles && nbBieres == rhs.nbBieres && cout == rhs.cout;
    };
};


#endif
