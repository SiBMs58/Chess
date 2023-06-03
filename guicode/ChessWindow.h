#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "SchaakStuk.h"
#include <QCloseEvent>
class ChessBoard;

class ChessWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChessWindow(QWidget *parent = 0);
    ~ChessWindow();

    virtual void update()=0;

protected:
    virtual void clicked(int x, int y)=0;
    virtual void newGame()=0;
    virtual void open() =0;
    virtual void save()=0;
    virtual void undo()=0;
    virtual void redo()=0;
    virtual void visualizationChange()=0;

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

private:
    QAction* display_moves;
    QAction* display_kills;
    QAction* display_threats;
    ChessBoard *scene;
private slots:
    void slot_clicked(int x, int y) {clicked(x,y);}
    void slot_newGame() {newGame();}
    void slot_open() {open();}
    void slot_save() {save();}
    void slot_undo() {undo();}
    void slot_redo() {redo();}
    void slot_visualizationChange() {visualizationChange();}


    void on_actionExit_triggered();
    void closeEvent (QCloseEvent *event)
    {
        on_actionExit_triggered();
        event->ignore();
    }

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QMenu *gameMenu;
    QMenu *visualizeMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *exitAct;
};

#endif // MAINWINDOW_H
