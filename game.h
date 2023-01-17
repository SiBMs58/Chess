//  Student: Siebe Mees
//  Rolnummer: 20222485
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"

using namespace std;

class Game {
public:
    // variabelen om de status van het spel/bord te bewaren
    bool beurtWit = true;
    // Last piece that was clicked
    SchaakStuk* laatstClickedStuk;
    // Number of times the last piece was clicked
    int clickCount;


    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    SchaakStuk* getPiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);

private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
    SchaakStuk* bord[8][8];
};


#endif //SCHAKEN_GAME_H
