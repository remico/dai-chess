#ifndef ROOKVALIDATOR
#define ROOKVALIDATOR

#include "ivalidator.h"

class RookValidator : public IValidator
{
public:
    explicit RookValidator(GameField *pField, QQuickItem *parent = 0) : IValidator(pField, parent) {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        Q_UNUSED(idx)
        const int correction = sCell % 8 ? 0 : 8;
        const int left = sCell - (sCell % 8 + correction) + 1;
        const int right = left + 7;
        const int delta = dCell - sCell;
        int step = 0;

        if (delta % 8) {    // non-vertical
            if (dCell < left || dCell > right)  // non-horizontal
                return false;
            step = delta < 0 ? -1 : 1;
        }
        else {  // vertical
            step = delta < 0 ? -8 : 8;
        }

        for (int i = 1; i < delta / step; ++i)
            if (m_pField->chessPieceByCell(sCell + step * i))
                return false;

        return true;
    }
};

#endif // ROOKVALIDATOR

// 57 64 1 8
