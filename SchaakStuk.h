//  Student: Siebe Mees
//  Rolnummer: 20222485
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>


#include <iostream>
#include <utility>

using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }

    virtual vector<pair<int,int>> geldige_zetten(Game& g) const = 0;

private:
    zw kleur;

};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    virtual vector<pair<int,int>> geldige_zetten(Game& g) const override;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game& g) const override{
        std::vector<std::pair<int, int>> moves;
        return moves;
    }
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game& g) const override{
        std::vector<std::pair<int, int>> moves;
        return moves;
    }
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game& g) const override{
        std::vector<std::pair<int, int>> moves;
        return moves;
    }
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game& g) const override{
        std::vector<std::pair<int, int>> moves;
        return moves;
    }
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game& g) const override{
        std::vector<std::pair<int, int>> moves;
        return moves;
    }
};

#endif //SCHAKEN_SCHAAKSTUK_H
