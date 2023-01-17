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
    SchaakStuk* s=g.getPiece(r,k);

    // Checkt of er op een leeg vakje word geclicked
    if (s == nullptr){
        // Gebeurt niets
    } else {
        // Checkt aan wie de beurt is
        // Als wit aan de beurt is een het stuk waar op geclicked wit of als het niet de beurt is aan wit moet er op een zwart stuk geclicked worden
        if (g.beurtWit==true && s->getKleur()==wit || g.beurtWit == false && s->getKleur()==zwart){
            // Checkt op de eerste click
            if (s == g.laatstClickedStuk){
                // Increment de clickCounter
                g.clickCount++;
                // Checkt op een 2de click op hetzelfde stuk
                if (g.clickCount == 2) {
                    vector<pair<int,int>> v=s->geldige_zetten(g);
                    cout << "Row " << r << " Col " << k << endl;
                    for(int i = 0; i < v.size(); i++) {
                        cout << v[i].first << ", " << v[i].second << endl;
                        // Bepaal positie naar waar het stuk verplaatst moet worden
                        setTileFocus(v[i].first, v[i].second, true);
                        // TODO: Klik je daarentegen op een andere positie, dan ga je na of het een geldige zet is. Indien dit zo is, doe de verplaatsing in het spel (game g) en update de grafische weergave. Indien de zet ongeldig is geef je een foutboodschap met de functie message(foutboodschap). De foutboodschap kan bijvoorbeeld zijn: “Deze zet is ongeldig.”
                        g.move(s, 4,0);
                    }


                    // Checkt of wit zijn beurt heeft gedaan zo ja dan gaat de beurt naar zwart (of de beurt wit op false)
                    if (g.beurtWit == true) {
                        // zet de witte beurt op false
                        g.beurtWit = false;
                    } else {
                        g.beurtWit = true;
                    }
                }
            } else {
                setTileSelect(r, k, true);
                g.laatstClickedStuk = s;
                g.clickCount = 1;
            }
        } else {
            // Gebeurt niets
        }
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
    for (int r = 0; r < 8; ++r) {
        for (int k = 0; k < 8; ++k) {
            if (g.getPiece(r, k) != nullptr){
                setItem(r, k,g.getPiece(r,k));
            }
        }
    }
}

