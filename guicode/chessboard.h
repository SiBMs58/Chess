//
//  !!! Dit bestand moet je in principe NIET wijzigen !!!
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>

class QAction;
class QActionGroup;

class Piece
{
public:
    enum Type { King, Queen, Bishop, Knight, Rook, Pawn, None };
    enum Color { White, Black };

    Piece() { eType = None; eColor = White; }
    Piece(Type t, Color c) { eType = t; eColor = c; }

    Type type() const { return eType; }
    Color color() const { return eColor; }
    void setType(Type t) { eType = t; }
    void setColor(Color c) { eColor = c; }

private:
    Type eType;
    Color eColor;
};

class ChessBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChessBoard(QObject *parent = 0);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void clicked(int x,int y);

public:
    void setItem(int i, int j, Piece p);
    void removeItem(int i, int j);
    void clearBoard();

    void setTileFocus(int x, int y, bool f);
    void setTileThreat(int x, int y, bool f);
    void setTileSelect(int x, int y, bool f);
    void setPieceThreat(int x, int y, bool f);
    void removeAllMarking();
    void removeAllTileDanger();
    void removeAllTileFocus();
    void removeAllTileSelection();
    void removeAllPieceThreats();

    bool hasTileFocus(int x,int y) const {return focusCell[x][y];}
    bool hasTileThreat(int x,int y) const {return threatCell[x][y];}
    bool hasTileSelect(int x,int y) const {return selectCell[x][y];}
    bool hasPieceThreat(int x,int y) const {return threatPiece[x][y];}

private:
    void drawTile(int i, int j);
    void refreshTile(int i, int j);
    void refreshImage(int i, int j);
    void refreshBoard();
    void redrawEntireBoard();

    void drawBoard();
    QString getPieceFilename(Piece p);

    Piece board[8][8];
    bool focusCell[8][8];
    bool threatCell[8][8];
    bool selectCell[8][8];
    bool threatPiece[8][8];

    quint8 rowFromPoint(int y) const { return y / nPieceWidth; }
    quint8 colFromPoint(int x) const { return x / nPieceWidth; }

    quint32 xFromCol(int c) const { return c*nPieceWidth + 0.5*nPieceWidth; }
    quint32 yFromRow(int r) const { return r*nPieceWidth + 0.5*nPieceWidth; }

    QColor cLightSquareColor;
    QColor cDarkSquareColor;
    QColor cLightPieceColor;
    QColor cDarkPieceColor;
    QColor cDarkSquareColorFocus;
    QColor cDarkSquareColorFocusDanger;
    QColor cLightSquareColorFocusDanger;
    QColor cLightSquareColorFocus;
    //QColor cDarkPieceColorFocus;
    //QColor cLightPieceColorFocus;
    QColor cDarkPieceColorThreat;
    QColor cLightPieceColorThreat;
    //QColor cLightPieceColorFocusThreat;
    //QColor cDarkPieceColorFocusThreat;
    QColor cDarkSquareColorSelected;
    QColor cLightSquareColorSelected;

    quint32 nPieceWidth;
    quint32 nBorderWidth;

    qint8 focusRow, focusCol;
};

#endif // CHESSBOARD_H
