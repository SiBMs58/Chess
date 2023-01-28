//  Student: Siebe Mees
//  Rolnummer: 20222485
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

// TODO: Erbij geschreven
#include <algorithm>

Game::Game() {
    // Zet alle vakjes gelijk aan een nullptr
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            bord[r][k] = nullptr;
        }
    }
    setStartBord();
}

Game::~Game() {
}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    // Plaats alle zwarte stukken
    SchaakStuk* Tz1=new Toren(zwart);
    SchaakStuk* Tz2=new Toren(zwart);
    SchaakStuk* Pz1=new Paard(zwart);
    SchaakStuk* Pz2=new Paard(zwart);
    SchaakStuk* Lz1=new Loper(zwart);
    SchaakStuk* Lz2=new Loper(zwart);
    SchaakStuk* Qz=new Koningin(zwart);
    SchaakStuk* Kz=new Koning(zwart);

    setPiece(0,0,Tz1);
    setPiece(0,1,Pz1);
    setPiece(0,2,Lz1);
    setPiece(0,3,Qz);
    setPiece(0,4,Kz);
    setPiece(0,5,Lz2);
    setPiece(0,6,Pz2);
    setPiece(0,7,Tz2);

    for (int i = 0; i < 8; ++i) {
        SchaakStuk* pz=new Pion(zwart);
        setPiece(1,i,pz);
    }

    // Plaatst alle witte stukken
    SchaakStuk* Tw1=new Toren(wit);
    SchaakStuk* Tw2=new Toren(wit);
    SchaakStuk* Pw1=new Paard(wit);
    SchaakStuk* Pw2=new Paard(wit);
    SchaakStuk* Lw1=new Loper(wit);
    SchaakStuk* Lw2=new Loper(wit);
    SchaakStuk* Qw=new Koningin(wit);
    SchaakStuk* Kw=new Koning(wit);

    setPiece(7,0,Tw1);
    setPiece(7,1,Pw1);
    setPiece(7,2,Lw1);
    setPiece(7,3,Qw);
    setPiece(7,4,Kw);
    setPiece(7,5,Lw2);
    setPiece(7,6,Pw2);
    setPiece(7,7,Tw2);

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
    // Update de positie
    pair<int, int> oudePositie;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Zet het nieuwe stuk
            if (i == r && j == k) {
                bord[i][j] = s;
            }
            // Zet het oude vakje leeg
            else if (getPiece(i, j) == s){
                oudePositie = make_pair(i, j);
                bord[i][j] = nullptr;
            }
        }
    }
    stukVerplaatst = true;
    // Er word alleen verplaatst indien de zet er niet voor zorgt dat de koning van de eigen kleur schaak komt te staan
    // Kijk of je de vorige zet al schaak stond zo ja dan moet je wel kunnen verplaatsen
    // Note; het reseten van de zet was niet mogelijk via recursie d.m.v. segmentation fault
    if (s->isKoning() == false && schaak(s->getKleur())) {
        // Reset je de locatie // Note; het resetten van de zet was niet mogelijk via recursie d.m.v. segmentation fault
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (i == r && j == k) {
                    bord[i][j] = nullptr;
                }
                else if (oudePositie.first == i && oudePositie.second == j) {
                    bord[i][j] = s;
                }
            }
        }
        stukVerplaatst = false;
        return false;
    }
    return true;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    // Zoek de positie van de koning
    int rijKoning, kolomKoning;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Om te kunnen checken dat een stuk een koning is
            if (bord[i][j] != nullptr && getPiece(i, j)->getKleur() == kleur && bord[i][j]->isKoning()) {
                rijKoning = i;
                kolomKoning = j;
            }
        }
    }
    // Loop door heel het bord
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            // Kijk eerst dat het geen leeg stuk is
            if (getPiece(r, k) != nullptr) {
                // Kijk dan of het stuk een andere kleur heeft en dan
                if (getPiece(r, k)->getKleur() != kleur) {
                    // bereken voor elk vijandelijk stuk de geldige zetten
                    SchaakStuk* s = getPiece(r, k);
                    vector<pair<int, int>> v =s->geldige_zetten(*this);
                    // Kijk dan of een van de geldige zetten gelijk is aan de postie van de koning
                    for (int i = 0; i < v.size(); ++i) {
                        if (v[i].first == rijKoning && v[i].second == kolomKoning) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    // Als de kleur niet schaak staat kan het ook niet schaakmat staan
    if (schaak(kleur) == false) {
        return false;
    } else {
        // Kijk of de koning een beweging kan uitvoeren
        for (int r = 0; r < 8; ++r) {
            for (int k = 0; k < 8; ++k) {
                // Om te kunnen checken dat een stuk een koning is
                if (bord[r][k] != nullptr && getPiece(r, k)->getKleur() == kleur && bord[r][k]->isKoning()) {
                    SchaakStuk* koning = getPiece(r, k);
                    // Bepaal de geldige zetten van de koning
                    vector<pair<int, int>> v = koning->geldige_zetten(*this);
                    for (int i = 0; i < v.size(); ++i) {
                        // We stimuleren nu alle geldige zetten om te zien dat er een mogelijke
                        // TODO: Erbij geschreven
                        move(koning, v[i].first, v[i].second);
                        // zet is die er voor zorgt dat de kleur niet meer schaak zal staan
                        if (schaak(koning->getKleur()) == false) {
                            // Zetten we hem terug naar oorspronkelijke positie en
                            move(koning, r, k);
                            return false;
                        }
                        // Zetten we hem terug naar oorspronkelijke positie en
                        move(koning, r, k);
                    }
                }
            }
        }
        return true;
    }
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    if (schaak(wit) == false || schaak(zwart) == false) {
        return false;
    } else {
        // Kijk of er nog een stuk is van die kleur die een geldige zet kan uitoefenen die niet wordt terug geroepen
        for (int r = 0; r < 8; ++r) {
            for (int k = 0; k < 8; ++k) {
                if (getPiece(r, k) != nullptr) {
                    if (getPiece(r, k)->getKleur() == kleur) {
                        SchaakStuk* s= getPiece(r, k);
                        vector<pair<int, int>> v = s->geldige_zetten(*this);
                        for (int i = 0; i < v.size(); ++i) {
                            // We stimuleren nu alle geldige zetten om te zien dat er een mogelijke
                            // TODO: Erbij geschreven
                            move(s, v[i].first, v[i].second);
                            // zet is die er voor zorgt dat de kleur niet meer schaak zal staan
                            if (schaak(s->getKleur()) == false) {
                                // Zetten we hem terug naar oorspronkelijke positie en
                                move(s, r, k);
                                return false;
                            }
                            // Zetten we hem terug naar oorspronkelijke positie en
                            move(s, r, k);
                        }
                    }
                }
            }
        }
    }
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
void Game::setPiece(int r, int k, SchaakStuk* s) {
    // Hier komt jouw code om een stuk neer te zetten op het bord
    bord[r][k] = s;
}


// Get bord
vector<vector<SchaakStuk*>> Game::getBord() const {
    // Maak een deepcopy van het bord
    vector<vector<SchaakStuk*>> copy(8, vector<SchaakStuk*>(8));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            copy[i][j] = bord[i][j];
        }
    }
    return copy;
}

// Set Bord
void Game::setBord(vector<vector<SchaakStuk*>> nieuwBord) {
    // Maak een deepcopy van het bord
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bord[i][j] = nieuwBord[i][j];
        }
    }
}