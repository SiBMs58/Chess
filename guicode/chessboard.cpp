//
//  !!! Dit bestand moet je in principe NIET wijzigen !!!
//

#include "chessboard.h"
#include "resources.h"

#include <QtWidgets>
#include <QPixmap>
const QVariant kTile=555;
const QVariant kPiece=777;
const quint32 kWidth=45;

ChessBoard::ChessBoard(QObject *parent) :
    QGraphicsScene(parent)
{
    nPieceWidth = kWidth;
    nBorderWidth = 0;

    cLightPieceColor = Qt::black;
    cDarkPieceColor = Qt::black;
    cLightSquareColor = Qt::white;
    cDarkSquareColor = Qt::gray;
    cDarkSquareColorFocus = QColor(100,100,170);
    cLightSquareColorFocus = QColor(100,100,255);
    cDarkSquareColorFocusDanger = QColor(170,100,100);
    cLightSquareColorFocusDanger = QColor(255,100,100);
    cDarkSquareColorSelected = QColor(100,170,100);
    cLightSquareColorSelected = QColor(100,255,100);
    cDarkPieceColorThreat = QColor(100,0,0);
    cLightPieceColorThreat = QColor(100,0,0);

    removeAllMarking();
}

void ChessBoard::removeAllMarking() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            focusCell[i][j]=false;
            selectCell[i][j]=false;
            threatPiece[i][j]=false;
            threatCell[i][j]=false;
        }
    }
    redrawEntireBoard();
}

void ChessBoard::removeAllTileDanger() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            threatCell[i][j]=false;
        }
    }
    redrawEntireBoard();
}

void ChessBoard::removeAllTileFocus() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            focusCell[i][j]=false;
        }
    }
    redrawEntireBoard();
}

void ChessBoard::removeAllTileSelection() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            selectCell[i][j]=false;
        }
    }
    redrawEntireBoard();
}

void ChessBoard::removeAllPieceThreats() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            threatPiece[i][j]=false;
        }
    }
    redrawEntireBoard();
}



void ChessBoard::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    QPointF scenePos = e->scenePos();
    if( scenePos.x() < 0 || scenePos.y() < 0 || scenePos.x() > 8*nPieceWidth || scenePos.y() > 8*nPieceWidth )
    {
        focusRow = -1;
        focusCol = -1;
        return;
    }

    focusRow = rowFromPoint( scenePos.y() );
    focusCol = colFromPoint( scenePos.x() );

    if (focusRow>=0 && focusRow<8 && focusCol>=0 && focusCol<8) {
        emit(clicked((int) focusRow, (int) focusCol));
    }

    QGraphicsScene::mousePressEvent(e);
}

void ChessBoard::setTileFocus(int x, int y,bool f=true) {
    focusCell[x][y]=f;
    refreshTile(x,y);
    refreshImage(x,y);
}

void ChessBoard::setTileThreat(int x, int y,bool f=true) {
    threatCell[x][y]=f;
    refreshTile(x,y);
    refreshImage(x,y);
}


void ChessBoard::setTileSelect(int x, int y, bool f) {
    selectCell[x][y]=f;
    refreshTile(x,y);
    refreshImage(x,y);
}

void ChessBoard::setPieceThreat(int x, int y, bool f) {
    threatPiece[x][y]=f;
    refreshImage(x,y);
}

void ChessBoard::drawTile(int i, int j)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem( j * nPieceWidth , i * nPieceWidth , nPieceWidth , nPieceWidth );

    if( i % 2 == j % 2 ) {
        if (selectCell[i][j]) { // Selected cells only get the selection background color
            rect->setBrush(QBrush(cLightSquareColorSelected, Qt::SolidPattern));
        } else if (focusCell[i][j]) {
            if (threatCell[i][j]) rect->setBrush(QBrush(cLightSquareColorFocusDanger, Qt::SolidPattern));
            else rect->setBrush(QBrush(cLightSquareColorFocus, Qt::SolidPattern));
        } else { // If the cell has no focus, it also has no danger indication
            rect->setBrush(QBrush(cLightSquareColor, Qt::SolidPattern));
        }
    } else {
        if (selectCell[i][j]) { // Selectd cells only get the selection background color
            rect->setBrush(QBrush(cDarkSquareColorSelected, Qt::SolidPattern));
        } else if (focusCell[i][j]) {
            if (threatCell[i][j]) rect->setBrush(QBrush(cDarkSquareColorFocusDanger, Qt::SolidPattern));
            else rect->setBrush(QBrush(cDarkSquareColorFocus, Qt::SolidPattern));
        } else { // If the cell has no focus, it also has no danger indication
            rect->setBrush(QBrush(cDarkSquareColor, Qt::SolidPattern));
        }
    }
    rect->setCacheMode(QGraphicsItem::NoCache);
    rect->setData(0, kTile );
    addItem(rect);
}

void ChessBoard::refreshTile(int i, int j) {
    QGraphicsItem *currentItem = itemAt( xFromCol(j) , yFromRow(i), QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = itemAt( xFromCol(j) , yFromRow(i) , QTransform() );
    }

    drawTile(i,j);
}


void ChessBoard::drawBoard()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            drawTile(i,j);
        }
    }
}

void ChessBoard::setItem(int i, int j, Piece p)
{
    board[i][j] = p;
    refreshImage(i,j);
}

void ChessBoard::removeItem(int i, int j)
{
    board[i][j] = Piece();
    refreshImage(i,j);
}

void ChessBoard::refreshBoard()
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            refreshImage(i,j);
}

void ChessBoard::redrawEntireBoard()
{
    qDeleteAll( items() );
    drawBoard();
    refreshBoard();
}

void ChessBoard::clearBoard()
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            setItem(i,j,Piece());
}

void ChessBoard::refreshImage(int i, int j)
{
    QGraphicsItem *currentItem = itemAt( xFromCol(j) , yFromRow(i) , QTransform() );
    if( currentItem != 0 && currentItem->data(0) == kPiece )
        delete currentItem;

    QString filename = getPieceFilename( board[i][j] );
    if(filename.isEmpty())
        return;

    quint32 y = nPieceWidth * i;
    quint32 x = nPieceWidth * j;
    QGraphicsPixmapItem* item=new QGraphicsPixmapItem(QPixmap(filename).scaled(45,45));

    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect;
    if( board[i][j].color() == Piece::White )
        if (threatPiece[i][j]) colorize->setColor(cLightPieceColorThreat);
        else colorize->setColor(cLightPieceColor);
    else
        if (threatPiece[i][j]) colorize->setColor(cDarkPieceColorThreat);
        else colorize->setColor(cDarkPieceColor);

    item->setGraphicsEffect( colorize );


    item->setCacheMode(QGraphicsItem::NoCache); // needed for proper rendering
    item->setData(0, kPiece );

    addItem(item);
    item->setPos(x,y);
}

QString ChessBoard::getPieceFilename(Piece p)
{
    if( p.type() == Piece::None )
        return "";

    QString filename = QString(path);
    switch(p.color())
    {
    case Piece::White:
        filename += "white";
        break;
    case Piece::Black:
    default:
        filename += "black";
        break;
    }

    switch(p.type())
    {
    case Piece::King:
        filename += "-king";
        break;
    case Piece::Queen:
        filename += "-queen";
        break;
    case Piece::Bishop:
        filename += "-bishop";
        break;
    case Piece::Knight:
        filename += "-knight";
        break;
    case Piece::Rook:
        filename += "-rook";
        break;
    case Piece::Pawn:
        filename += "-pawn";
        break;
    default:
        break;
    }

    return filename + ".svg";
}
