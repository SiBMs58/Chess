//
// Created by toonc on 12/17/2021.
//

#ifndef SCHAKEN_SCHAAKGUI_H
#define SCHAKEN_SCHAAKGUI_H

#include "guicode/ChessWindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QAction>

class SchaakGUI:public ChessWindow {
public:
    SchaakGUI();

    void update();

private:
    Game g;

    void clicked(int x, int y) override;
    void newGame() override;
    void open() override;
    void save() override;
    void undo() override;
    void redo() override;
    void visualizationChange() override;

/*  Overgeerfde functies van ChessWindow:

    void removeAllMarking();
    void clearBoard();
    void setItem(int i,int j,SchaakStuk* p);
    void setPieceThreat(int i,int j,bool b);
    void removeAllPieceThreats();
    void setTileSelect(int i,int j,bool b);
    void setTileFocus(int i,int j,bool b);
    void setTileThreat(int i,int j,bool b);

    bool displayKills();
    bool displayMoves();
    bool displayThreats();
*/
};


#endif //SCHAKEN_SCHAAKGUI_H
