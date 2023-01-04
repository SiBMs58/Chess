//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    // Zet alle vakjes gelijk aan een nullptr
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            bord[row][col] = nullptr;
        }
    }
}

Game::~Game() {

}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    // Plaats alle witte stukken
    SchaakStuk* T=new Toren(wit);
    setPiece(0,0,T);
    for (int i = 0; i < 8; ++i) {
        SchaakStuk* p=new Pion(wit);
        setPiece(1,i,p);
    }
    /*bord[0][1] = new Piece{"knight", "white"};
    bord[0][2] = new Piece{"bishop", "white"};
    bord[0][3] = new Piece{"queen", "white"};
    bord[0][4] = new Piece{"king", "white"};
    bord[0][5] = new Piece{"bishop", "white"};
    bord[0][6] = new Piece{"knight", "white"};
    bord[0][7] = new Piece{"rook", "white"};

    // Place black pieces
    bord[7][0] = new Piece{"rook", "black"};
    bord[7][1] = new Piece{"knight", "black"};
    bord[7][2] = new Piece{"bishop", "black"};
    bord[7][3] = new Piece{"queen", "black"};
    bord[7][4] = new Piece{"king", "black"};
    bord[7][5] = new Piece{"bishop", "black"};
    bord[7][6] = new Piece{"knight", "black"};
    bord[7][7] = new Piece{"rook", "black"};
    for (int i = 0; i < 8; ++i) {
        bord[6][i] = new Piece{"pawn", "black"};
    }
     */
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