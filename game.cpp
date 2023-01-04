//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    // Zet alle vakjes gelijk aan een nullptr
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            bord[r][k] = nullptr;
        }
    }
}

Game::~Game() {

}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    // Plaats alle zwarrte stukken
    SchaakStuk* Tz=new Toren(zwart);
    SchaakStuk* Pz=new Paard(zwart);
    SchaakStuk* Lz=new Loper(zwart);
    SchaakStuk* Qz=new Koningin(zwart);
    SchaakStuk* Kz=new Koning(zwart);

    setPiece(0,0,Tz);
    setPiece(0,1,Pz);
    setPiece(0,2,Lz);
    setPiece(0,3,Qz);
    setPiece(0,4,Kz);
    setPiece(0,5,Lz);
    setPiece(0,6,Pz);
    setPiece(0,7,Tz);

    for (int i = 0; i < 8; ++i) {
        SchaakStuk* pz=new Pion(zwart);
        setPiece(1,i,pz);
    }

    // Plaatst alle witte stukken
    SchaakStuk* Tw=new Toren(wit);
    SchaakStuk* Pw=new Paard(wit);
    SchaakStuk* Lw=new Loper(wit);
    SchaakStuk* Qw=new Koningin(wit);
    SchaakStuk* Kw=new Koning(wit);

    setPiece(7,0,Tw);
    setPiece(7,1,Pw);
    setPiece(7,2,Lw);
    setPiece(7,3,Qw);
    setPiece(7,4,Kw);
    setPiece(7,5,Lw);
    setPiece(7,6,Pw);
    setPiece(7,7,Tw);

    for (int i = 0; i < 8; ++i) {
        SchaakStuk* pw=new Pion(wit);
        setPiece(6,i,pw);
    }
}


// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    return true;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    return bord[r][k];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    // Hier komt jouw code om een stuk neer te zetten op het bord
    bord[r][k] = s;
}