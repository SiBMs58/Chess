#include "ChessWindow.h"
#include <QtWidgets>

ChessWindow::ChessWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new ChessBoard;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(slot_clicked(int,int)));

    createActions();
    createMenus();
}

ChessWindow::~ChessWindow() {
    delete scene;
}

void ChessWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &ChessWindow::slot_newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &ChessWindow::slot_open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &ChessWindow::slot_save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &ChessWindow::on_actionExit_triggered);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last move"));
    connect(undoAct, &QAction::triggered, this, &ChessWindow::slot_undo);

    redoAct = new QAction(tr("&redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last undone move"));
    connect(redoAct, &QAction::triggered, this, &ChessWindow::slot_redo);

    display_moves= new QAction(tr("&valid moves"), this);
    display_moves->setStatusTip(tr("Show valid moves"));
    display_moves->setCheckable(true);
    display_moves->setChecked(true);
    connect(display_moves, &QAction::triggered, this, &ChessWindow::slot_visualizationChange);

    display_kills= new QAction(tr("threathed &enemy"), this);
    display_kills->setStatusTip(tr("Highlight threathened pieces (enemy)"));
    display_kills->setCheckable(true);
    display_kills->setChecked(true);
    connect(display_kills, &QAction::triggered, this, &ChessWindow::slot_visualizationChange);

    display_threats= new QAction(tr("threathed &player"), this);
    display_threats->setStatusTip(tr("Highlight threathened pieces (player)"));
    display_threats->setCheckable(true);
    display_threats->setChecked(true);
    connect(display_threats, &QAction::triggered, this, &ChessWindow::slot_visualizationChange);
}

void ChessWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(undoAct);
    gameMenu->addAction(redoAct);

    visualizeMenu = menuBar()->addMenu(tr("&Visualize"));
    visualizeMenu->addAction(display_moves);
    visualizeMenu->addAction(display_kills);
    visualizeMenu->addAction(display_threats);
}

void ChessWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {
        QApplication::quit();
    }
}

void ChessWindow::removeAllMarking() {
    scene->removeAllMarking();  // Alle markeringen weg
}

void ChessWindow::clearBoard() {
    scene->clearBoard();
}

void ChessWindow::setItem(int i, int j, SchaakStuk* p) {
    scene->setItem(i,j,p->piece());
}

void ChessWindow::setPieceThreat(int i, int j, bool b) {
    scene->setPieceThreat(i,j,b);
}

void ChessWindow::removeAllPieceThreats() {
    scene->removeAllPieceThreats();
}

void ChessWindow::setTileSelect(int i, int j, bool b) {
    scene->setTileSelect(i,j,b);
}

void ChessWindow::setTileFocus(int i, int j, bool b) {
    scene->setTileFocus(i,j,b);
}

void ChessWindow::setTileThreat(int i, int j, bool b) {
    scene->setTileThreat(i,j,b);
}

bool ChessWindow::displayKills() {
    return display_kills->isChecked();
}

bool ChessWindow::displayMoves() {
    return display_moves->isChecked();
}

bool ChessWindow::displayThreats() {
    return display_threats->isChecked();
}
