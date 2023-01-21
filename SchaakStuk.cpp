//  Student: Siebe Mees
//  Rolnummer: 20222485
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"

#include "game.h"

///// Geldige zetten
// Pion
vector<pair<int, int>> Pion::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Slaagt een boleaanse op indien eersteZet of niet
    bool eersteZet = true;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // Checkt of rij niet gelijk is aan 1 of 6 in geval van wit d.w.z dat het niet de eerste zet is
    if (this->getKleur() == zwart && rijClicked != 1 || this->getKleur() == wit && rijClicked != 6){
        eersteZet = false;
    }
    // Checkt op de geldige zetten voor een zwart stuk
    if (this->getKleur() == zwart) {
        // Checkt op verticaal bewegen
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square beneden leeg is
        if (rijClicked + 1 < 8 && g.getPiece(rijClicked+1, kolomClicked) == nullptr){
            zetten.push_back({rijClicked+1, kolomClicked});
            // Kijkt na of het de eerste zet is al dan niet && kijkt of 2 squares beneden leeg zijn
            if (eersteZet && g.getPiece(rijClicked+2, kolomClicked) == nullptr) {
                zetten.push_back({rijClicked+2, kolomClicked});
            }
        }
        /*
        // Checkt of de pion een stuk diagonaal kan slaan/vangen
        // Kijkt of de pion niet op de rand van het bord zit en Kijkt of het vierkant diagonaal rechts onder wordt bezet door een vijandelijk stuk
        if (rijClicked + 1 < 8 && kolomClicked + 1 < 8 && g.getPiece(rijClicked + 1,kolomClicked + 1) != nullptr) {
            zetten.push_back({ rijClicked + 1, kolomClicked + 1 });
        }
        // Kijkt of de pion niet op de rand van het bord zit en Kijkt of het vierkant diagonaal links onder wordt bezet door een vijandelijk stuk
        if (rijClicked + 1 < 8 && kolomClicked - 1 >= 0 && g.getPiece(rijClicked + 1,kolomClicked - 1) != nullptr) {
            zetten.push_back({ rijClicked + 1, kolomClicked - 1 });
        }
         */
    // Checkt op de geldige zetten voor een wit stuk
    } else {
        // Checkt op verticaal bewegen
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square erboven leeg is
        if (rijClicked - 1 > 0 && g.getPiece(rijClicked-1, kolomClicked) == nullptr) {
            zetten.push_back({rijClicked-1, kolomClicked});
            // Kijkt na of het de eerste zet is al dan niet && kijkt of 2 squares beneden leeg zijn
            if (eersteZet && g.getPiece(rijClicked-2, kolomClicked) == nullptr) {
                zetten.push_back({rijClicked-2, kolomClicked});
            }
        }
        /*
        // Checkt op diagonaal bewegen
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square rechts boven ervan wordt bezet door een vijandelijk stuk
        if (rijClicked - 1 > 0 && g.getPiece(rijClicked-1, kolomClicked+1) != nullptr) {
            zetten.push_back({rijClicked-1, kolomClicked +1});
        }
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square links boven wordt bezet door een vijandelijk stuk
        if (rijClicked -1 > 0 && g.getPiece(rijClicked-1, kolomClicked-1) != nullptr) {
            zetten.push_back({rijClicked-1, kolomClicked-1});
        }
         */
    }

    return zetten;
}

// Toren
vector<pair<int, int>> Toren::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // Checkt op horizontale bewegingen
    // naar boven
    for (int i = rijClicked-1; i >= 0; i--) {
        if (g.getPiece(i, kolomClicked) == nullptr){
            zetten.push_back(make_pair(i, kolomClicked));
        } else {
            break;
        }
    }
    // naar beneden
    for (int i = rijClicked+1; i < 8; i++) {
        if (g.getPiece(i, kolomClicked) == nullptr){
            zetten.push_back(make_pair(i, kolomClicked));
        } else {
            break;
        }
    }
    // Checkt op verticale bewegingen
    // naar links
    for(int i = kolomClicked-1; i >= 0; i--) {
        if (g.getPiece(rijClicked, i) == nullptr){
            zetten.push_back(make_pair(rijClicked, i));
        } else {
            break;
        }
    }
    // naar rechts
    for (int i = kolomClicked+1; i < 8; ++i) {
        if (g.getPiece(rijClicked, i) == nullptr) {
            zetten.push_back(make_pair(rijClicked, i));
        } else {
            break;
        }
    }

    return zetten;
}

// Paard
vector<pair<int, int>> Paard::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // check move naar boven rechts
    if (rijClicked-2 >= 0 && kolomClicked+1 < 8 && g.getPiece(rijClicked-2, kolomClicked+1) == nullptr){
        zetten.push_back(make_pair(rijClicked-2, kolomClicked+1));
    }
    // Checkt move naar boven links
    if (rijClicked-2 >= 0 && kolomClicked-1 >= 0 && g.getPiece(rijClicked-2, kolomClicked-1) == nullptr) {
        zetten.push_back(make_pair(rijClicked-2, kolomClicked-1));
    }
    // Checkt move naar beneden rechts
    if (rijClicked+2 < 8 && kolomClicked+1 < 8 && g.getPiece(rijClicked+2, kolomClicked+1) == nullptr){
        zetten.push_back(make_pair(rijClicked+2, kolomClicked+1));
    }
    // Checkt move naar beneden links
    if (rijClicked+2 < 8 && kolomClicked-1 >= 0 && g.getPiece(rijClicked+2, kolomClicked-1) == nullptr) {
        zetten.push_back(make_pair(rijClicked+2, kolomClicked-1));
    }
    // Checkt move rechts naar boven
    if (rijClicked-1 >= 0 && kolomClicked+2 < 8 && g.getPiece(rijClicked-1, kolomClicked+2) == nullptr) {
        zetten.push_back(make_pair(rijClicked-1, kolomClicked+2));
    }
    // Checkt move rechts naar beneden
    if (rijClicked+1 < 8 && kolomClicked+2 < 8 && g.getPiece(rijClicked+1, kolomClicked+2) == nullptr) {
        zetten.push_back(make_pair(rijClicked+1, kolomClicked+2));
    }
    // Checkt move links naar boven
    if (rijClicked-1 >= 0 && kolomClicked-2 >= 0 && g.getPiece(rijClicked-1, kolomClicked-2) == nullptr) {
        zetten.push_back(make_pair(rijClicked-1, kolomClicked-2));
    }
    // checkt move links naar beneden
    if (rijClicked+1 < 8 && kolomClicked-2 >= 0 && g.getPiece(rijClicked+1, kolomClicked-2) == nullptr) {
        zetten.push_back(make_pair(rijClicked+1, kolomClicked-2));
    }
    return zetten;
}

// Loper
vector<pair<int, int>> Loper::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // Check move boven rechts
    for (int i = rijClicked-1, j = kolomClicked+1; i >= 0 && j < 8; i--, j++) {
        if (g.getPiece(i,j) == 0) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Check move boven links
    for (int i = rijClicked-1, j = kolomClicked-1; i >= 0 && j >= 0; i--, j--) {
        if (g.getPiece(i,j) == 0) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Checkt move naar beneden rechts
    for (int i = rijClicked+1, j = kolomClicked+1; i < 8 && j < 8; i++, j++) {
        if (g.getPiece(i,j) == 0) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Checkt op zetten naar beneden links
    for (int i = rijClicked+1, j = kolomClicked-1; i < 8 && j >= 0; i++, j--) {
        if (g.getPiece(i,j) == 0) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    return zetten;
}

// Koning
vector<pair<int, int>> Koning::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // Checkt move naar boven
    if (rijClicked-1 <= 0 && g.getPiece(rijClicked-1, kolomClicked) == nullptr) {
        zetten.push_back(make_pair(rijClicked-1, kolomClicked));
    }
    // Checkt move naar beneden
    if (rijClicked+1 < 8 && g.getPiece(rijClicked+1, kolomClicked) == nullptr) {
        zetten.push_back(make_pair(rijClicked+1, kolomClicked));
    }
    // Checkt move naar links
    if (kolomClicked-1 >= 0 && g.getPiece(rijClicked, kolomClicked-1) == nullptr) {
        zetten.push_back(make_pair(rijClicked, kolomClicked-1));
    }
    // Checkt move naar rechts
    if (kolomClicked+1 < 8 && g.getPiece(rijClicked, kolomClicked+1) == nullptr) {
        zetten.push_back(make_pair(rijClicked, kolomClicked+1));
    }
    // Checkt move naar boven rechts
    if (rijClicked-1 <= 0 && kolomClicked+1 < 8 && g.getPiece(rijClicked-1, kolomClicked+1) == nullptr) {
        zetten.push_back(make_pair(rijClicked-1, kolomClicked+1));
    }
    // Checkt move naar boven links
    if (rijClicked-1 >= 0 && kolomClicked-1 >= 0 && g.getPiece(rijClicked-1, kolomClicked-1) == nullptr) {
        zetten.push_back(make_pair(rijClicked-1, kolomClicked-1));
    }
    // Checkt move naar beneden rechts
    if (rijClicked+1 < 8 && kolomClicked+1 < 8 && g.getPiece(rijClicked+1, kolomClicked+1) == nullptr) {
        zetten.push_back(make_pair(rijClicked+1, kolomClicked+1));
    }
    // Checkt op move beneden links
    if (rijClicked+1 < 8 && kolomClicked-1 >= 0 && g.getPiece(rijClicked+1, kolomClicked-1) == nullptr) {
        zetten.push_back(make_pair(rijClicked+1, kolomClicked+1));
    }
    return zetten;
}

// Koningin
vector<pair<int, int>> Koningin::geldige_zetten(Game &g) const {
    // Slaag de geldige zetten op in een vector
    vector<pair<int, int>> zetten;
    // Slaag de geclickte positie van het schaaktstuk op
    int rijClicked, kolomClicked;
    // Get current position of het schaakstuk waar juist op geclicked is
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) == this) {
                rijClicked = r;
                kolomClicked = k;
                break;
            }
        }
    }
    // Checkt move naar boven
    for (int i = rijClicked-1; i >= 0; --i) {
        if (g.getPiece(i, kolomClicked) == nullptr) {
            zetten.push_back(make_pair(i, kolomClicked));
        } else {
            break;
        }
    }
    // Checkt move naar beneden
    for (int i = rijClicked+1; i < 8; ++i) {
        if (g.getPiece(i, kolomClicked) == nullptr) {
            zetten.push_back(make_pair(i, kolomClicked));
        } else {
            break;
        }
    }
    // Checkt move naar links
    for (int i = kolomClicked-1; i >= 0; --i) {
        if(g.getPiece(rijClicked, i) == nullptr) {
            zetten.push_back(make_pair(rijClicked, i));
        } else {
            break;
        }
    }
    // Checkt move naar rechts
    for (int i = kolomClicked+1; i < 8; ++i) {
        if (g.getPiece(rijClicked, i) == nullptr) {
            zetten.push_back(make_pair(rijClicked, i));
        } else {
            break;
        }
    }
    // Checkt move naar boven rechts
    for (int i = rijClicked-1, j = kolomClicked+1; i >= 0 && j < 8; --i, ++j) {
        if (g.getPiece(i, j) == nullptr) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Chect move naar boven links
    for (int i = rijClicked-1, j = kolomClicked-1; i >= 0 && j >= 0; --i, j--) {
        if (g.getPiece(i, j) == nullptr) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Checkt move naar beneden rechts
    for (int i = rijClicked+1, j = kolomClicked+1; i < 8 && j < 8; ++i, ++j) {
        if (g.getPiece(i, j) == nullptr) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    // Checkt move naar beneden links
    for (int i = rijClicked+1, j = kolomClicked-1; i < 8 && j >= 0; ++i, --j) {
        if (g.getPiece(i, j) == nullptr) {
            zetten.push_back(make_pair(i, j));
        } else {
            break;
        }
    }
    return zetten;
}