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
        // Checkt of de pion een stuk diagonaal kan slaan/vangen
        // Kijkt of de pion niet op de rand van het bord zit en Kijkt of het vierkant diagonaal rechts onder wordt bezet door een vijandelijk stuk
        if (rijClicked + 1 < 8 && kolomClicked + 1 < 8 && g.getPiece(rijClicked + 1,kolomClicked + 1) != nullptr) {
            zetten.push_back({ rijClicked + 1, kolomClicked + 1 });
        }
        // Kijkt of de pion niet op de rand van het bord zit en Kijkt of het vierkant diagonaal links onder wordt bezet door een vijandelijk stuk
        if (rijClicked + 1 < 8 && kolomClicked - 1 >= 0 && g.getPiece(rijClicked + 1,kolomClicked - 1) != nullptr) {
            zetten.push_back({ rijClicked + 1, kolomClicked - 1 });
        }
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
        // Checkt op diagonaal bewegen
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square rechts boven ervan wordt bezet door een vijandelijk stuk
        if (rijClicked - 1 > 0 && g.getPiece(rijClicked-1, kolomClicked+1) != nullptr) {
            zetten.push_back({rijClicked-1, kolomClicked +1});
        }
        // Kijkt of de pion niet op de rand van het bord zit && kijkt of de square links boven wordt bezet door een vijandelijk stuk
        if (rijClicked -1 > 0 && g.getPiece(rijClicked-1, kolomClicked-1) != nullptr) {
            zetten.push_back({rijClicked-1, kolomClicked-1});
        }
    }

    return zetten;
}