#ifndef PAWNVALIDATOR_H
#define PAWNVALIDATOR_H

#include "ivalidator.h"

class PawnValidator : public IValidator
{
public:
    explicit PawnValidator(GameField *pField, QQuickItem *parent = 0) : IValidator(pField, parent) {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        QQuickItem *p_dChessPiece = m_pField->chessPieceByCell(dCell);

        if (idx >= 9 && idx <= 16) {
            if (((sCell >= 9 && sCell <= 16 && dCell == sCell + 16) // move
                    || dCell == sCell + 8)
                    && !m_pField->chessPieceByCell(sCell + 8)
                    && !p_dChessPiece)
                return true;
            if ((idx == 9 && dCell == sCell + 7)           // border correction
                    || (idx == 16 && dCell == sCell + 9))
                return false;
            if ((dCell == sCell + 7 || dCell == sCell + 9)          // take
                    && p_dChessPiece
                    && p_dChessPiece->property("idx").toInt() > 16)
                return true;
        }
        else if (idx >= 49 && idx <= 56) {
            if (((sCell >= 49 && sCell <= 56 && dCell == sCell - 16)    // move
                    || dCell == sCell - 8)
                    && !m_pField->chessPieceByCell(sCell - 8)
                    && !p_dChessPiece)
                return true;
            if ((idx == 49 && dCell == sCell - 9)           // border correction
                    || (idx == 56 && dCell == sCell - 7))
                return false;
            if ((dCell == sCell - 7 || dCell == sCell - 9)       // take
                    && p_dChessPiece
                    && p_dChessPiece->property("idx").toInt() <= 16)
                return true;
        }

        return false;
    }
};

#endif // PAWNVALIDATOR_H
