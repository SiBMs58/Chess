//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

#include <algorithm>
using namespace std;

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    update();
}

// TODO: Maak de click fucntie mooi werken a.d.h.v de opgave
// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    // Kijk voor de eerste klik
    if (g.clickCount == 0) {
        // Kijkt of er op een stuk wordt geklikt
        if (g.getPiece(r, k) != nullptr) {
            // Kijk op welk stuk er werd geklikt
            SchaakStuk *s = g.getPiece(r, k);
            // Kijkt of er op een "geldig" stuk werd geklikt (rekening houden met de beurt)
            if (g.beurtWit == true && s->getKleur() == wit || g.beurtWit == false && s->getKleur() == zwart) {
                // Selecteer het stuk dat je wilt bewegen
                setTileSelect(r, k, true);
                // Update help variable
                g.clickCount++;
                g.laatstClickedStuk = s;
            } else {
                // Doe je niets
            }
        } else {
            // Doe je niets
        }
    // Kijkt voor de tweede click op het laatstgeclickte stuk
    } else if (g.clickCount == 1 && g.getPiece(r, k) == g.laatstClickedStuk) {
        // Bepaal je de geldige zetten van het stuk
        vector<pair<int, int>> v = g.laatstClickedStuk->geldige_zetten(g);
        for (int i = 0; i < v.size(); ++i) {
            setTileFocus(v[i].first, v[i].second, true);
        }
        // TODO: Nakijken/ Checken, exeptions lang te randen?
        // Bepaal de zetten die door vijandelijke stukken worden bedreigd
        for (int m = 0; m < 8; ++m) {
            for (int n = 0; n < 8; ++n) {
                // Kijk eerst dat het geen leeg stuk is
                if (g.getPiece(m, n) != nullptr) {
                    // Kijk dan of het stuk een andere kleur heeft en dan
                    if (g.getPiece(m, n)->getKleur() != g.laatstClickedStuk->getKleur()) {
                        // Bereken voor elk vijandelijk stuk de geldige zetten
                        SchaakStuk* vijandelijkStuk = g.getPiece(m, n);
                        vector<pair<int, int>> geldigeZettenVijandelijkStuk;
                        if (vijandelijkStuk->isPion() == false) {
                            vector<pair<int, int>> geldigeZettenVijandelijkStuk = vijandelijkStuk->geldige_zetten(g);
                        }
                        // Uitzondering voor de pion
                        else if (vijandelijkStuk->isPion()) {
                            // Dan kijk je welke kleur de pion heeft
                            if (vijandelijkStuk->getKleur() == zwart) {
                                // Dan kijken we naar de diagonalen recht en links onder of dit en geldige zet is van het op geklikt schaakstuk
                                for (int a = 0; a < v.size(); ++a) {
                                    if (v[a].first == m+1 && v[a].second == n+1) {
                                        geldigeZettenVijandelijkStuk.push_back(make_pair(m+1, n+1));
                                    }
                                    if (v[a].first == m+1 && v[a].second == n-1) {
                                        geldigeZettenVijandelijkStuk.push_back(make_pair(m+1, n-1));
                                    }
                                }
                            } else {
                                // Dan kijken we naar de diagonalen recht en links boven of dit en geldige zet is van het op geklikt schaakstuk
                                for (int a = 0; a < v.size(); ++a) {
                                    if (v[a].first == m-1 && v[a].second == n+1) {
                                        geldigeZettenVijandelijkStuk.push_back(make_pair(m-1, n+1));
                                    }
                                    if (v[a].first == m-1 && v[a].second == n-1) {
                                        geldigeZettenVijandelijkStuk.push_back(make_pair(m-1, n-1));
                                    }
                                }
                            }
                        }
                        // Bepalen van gemeenschappelijke elemenent
                        // Bron: https://stackoverflow.com/questions/21410803/check-for-common-members-in-vector-c
                        // Loop voor de vectoren en check of ze dezelfde elementen hebben
                        vector<pair<int, int>> gemeenschappelijkeElementen;
                        set_intersection(v.begin(), v.end(), geldigeZettenVijandelijkStuk.begin(), geldigeZettenVijandelijkStuk.end(), back_inserter(gemeenschappelijkeElementen));
                        if (gemeenschappelijkeElementen.size() != 0) {
                            for (int i = 0; i < gemeenschappelijkeElementen.size(); ++i) {
                                setTileThreat(gemeenschappelijkeElementen[i].first, gemeenschappelijkeElementen[i].second, true);
                            }
                        }
                    }
                }
            }
        }
        // Update help variable
        g.clickCount++;
    // Kijkt voor de derde klik
    } else if (g.clickCount == 2) {
        // Checkt of er terug op hetzelfde stuk werd geklikt
        if (g.getPiece(r, k) == g.laatstClickedStuk) {
           // Maak de selectie ongedaan
           removeAllMarking();
           // Reset help variabelen
           g.clickCount = 0;
        } else {
            // Ga na of er op een geldige zet werd geklikt
            vector<pair<int, int>> v = g.laatstClickedStuk->geldige_zetten(g);
            for (int i = 0; i < v.size(); ++i) {
                if (r == v[i].first && k == v[i].second) {
                   g.move(g.laatstClickedStuk, r, k);
                   // Maak de selectie ongedaan
                   removeAllMarking();
                   // Update de Grafische weergave
                   update();
                }
            }
            // Kijk of het stuk is verplaats
            if (g.stukVerplaatst) {
                // Zet de beurt naar de juiste kleur & dat de move ervoor heeft gezorgd dat de andere kleur schaak komt te staan
                if (g.laatstClickedStuk->getKleur() == wit) {
                    // Kijkt eerst dat de move ervoor heeft gezorgd dat de andere kleur schaak komt te staan
                    if (g.schaak(zwart)) {
                        // Kijk dan of het geen schaakmat is
                        if (g.schaakmat(zwart)) {
                            message("Wit heeft gewonnen!");
                        } else {
                            message("Schaak!");
                        }
                    } else if (g.pat(zwart)) {
                        message("Het spel eindigt op een gelijkspel");
                    }
                    g.beurtWit = false;
                } else {
                    // Kijkt eerst dat de move ervoor heeft gezorgd dat de andere kleur schaak komt te staan
                    if (g.schaak(wit)) {
                        // Kijk dan of het geen schaakmat is
                        if (g.schaakmat(wit)) {
                            message("Zwart heeft gewonnen!");
                        } else {
                            message("Schaak!");
                        }
                    } else if (g.pat(wit)) {
                        message("Het spel eindigt op een gelijkspel");

                    }
                    g.beurtWit = true;
                }
            } else {
                message("Deze zet is ongeldig.");
                // Reset help variabelen
                removeAllMarking();
                g.clickCount = 0;
            }
            // Reset help variabelen
            g.clickCount = 0;

        }
    } else {
        // Doe niets
    }
}

void SchaakGUI::newGame()
{}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}


void SchaakGUI::undo() {
    message("Je hebt undo gekozen");
}

void SchaakGUI::redo() {}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) != nullptr){
                setItem(r, k,g.getPiece(r,k));
            }
        }
    }
}