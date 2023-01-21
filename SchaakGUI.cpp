//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"


#include <iostream>
using namespace std;

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    update();
}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    SchaakStuk *s = g.getPiece(r, k);
    // Checkt of er op een "geldige" zet word geklikt
    if (g.laatstClickedStuk != s && g.clickCount == 2) {
        vector<pair<int, int>> v = g.laatstClickedStuk->geldige_zetten(g);
        bool statement1_executed = false;
        for (int i = 0; i < v.size(); ++i) {
            if (r == v[i].first && k == v[i].second) {
                // Verwijder select en ook de focus
                // focus
                for (int k = 0; k < v.size(); ++k) {
                    setTileFocus(v[k].first, v[k].second, false);
                }
                // Select
                for (int j = 0; j < 8; ++j) {
                    for (int l = 0; l < 8; ++l) {
                        if (g.getPiece(j, l) == g.laatstClickedStuk){
                            setTileSelect(j, l, false);
                        }
                    }
                }
                // Beweeg het stuk
                g.move(g.laatstClickedStuk, r, k);
                // update de GUI
                update();
                statement1_executed = true;
                // Zet de beurt naar de andere kleur
                if (g.beurtWit == true) {
                    g.beurtWit = false;
                } else {
                    g.beurtWit = true;
                }
            }
        }
        if (statement1_executed == false) {
            message("Deze zet is ongeldig.");
        }
    }
    // Checkt als een stuk geselecteerd is maar er dan toch op iets anders wordt geklikt
    else if (s == nullptr && s != g.laatstClickedStuk){
        g.clickCount = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (g.getPiece(i, j) == g.laatstClickedStuk) {
                    setTileSelect(i, j, false);
                }
            }
        }
    }
    // Checkt of er op een leeg vakje word geclicked
    // Indien er niet op een leeg vakje wordt geclickt gaat het na of er op een "geldig" stuk werd geclicked
    // Checkt aan wie de beurt is
    // Als wit aan de beurt is een het stuk waar op geclicked wit of
    // als wit niet aan de beurt is moet er op een zwart stuk geclicked worden
    else if (g.beurtWit == true && s->getKleur() == wit || g.beurtWit == false && s->getKleur() == zwart) {
        // Eerste keer geduwd op geledig vakje dus selecteren we dat
        if (g.clickCount == 0) {
            setTileSelect(r, k, true);
            g.clickCount++;
            g.laatstClickedStuk = s;
            // Tweede keer op het geldig vakje word geduwd
        } else if (g.clickCount == 1 && g.laatstClickedStuk == s) {
            // Bepaal de geldige zetten
            vector<pair<int, int>> v = s->geldige_zetten(g);
            for (int i = 0; i < v.size(); ++i) {
                // Focus mogelijke zetten
                setTileFocus(v[i].first, v[i].second, true);
            }
            // Increment clickcount
            g.clickCount++;
            // Derde click; als er terug op het geselecteerd vakje word geduwd
            // dan deseleteer je dat vakje
        } else if (g.clickCount == 2 && g.laatstClickedStuk == s) {
            // Bepaal de geldige zetten
            vector<pair<int, int>> v = s->geldige_zetten(g);
            setTileSelect(r, k, false);
            for (int i = 0; i < v.size(); ++i) {
                // Verwijder focus mogelijke zetten
                setTileFocus(v[i].first, v[i].second, false);
            }
            g.clickCount = 0;
        } else {
            g.clickCount = 0;
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (g.getPiece(i, j) == g.laatstClickedStuk) {
                        setTileSelect(i, j, false);
                    }
                }
            }
        }
    }
    // Er gebeurt niet als er op een leeg vakje wordt geduwd of op een ongeldig stuk
    else {
        // Er gebeurt niets
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