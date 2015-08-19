#ifndef BISHOPVALIDATOR
#define BISHOPVALIDATOR

#include "ivalidator.h"

class BishopValidator : public IValidator
{
public:
    explicit BishopValidator(GameField *pField, QQuickItem *parent = 0) : IValidator(pField, parent) {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        Q_UNUSED(idx)
        const int correction = sCell % 8 ? 0 : -1;
        const int toTop = sCell / 8 + correction;
        const int toBottom = 7 - toTop;
        const int toLeft = sCell - toTop * 8 - 1;
        const int toRight = 7 - toLeft;
        const int delta = dCell - sCell;
        int step = 0;

        if (!(delta % 7)) {
            if (delta < 0) {
                step = -7;
                if (delta / step > qMin(toTop, toRight))
                    return false;
            }
            else {
                step = 7;
                if (delta / step > qMin(toLeft, toBottom))
                    return false;
            }
        }
        else if (!(delta % 9)) {
            if (delta < 0) {
                step = -9;
                if (delta / step > qMin(toTop, toLeft))
                    return false;
            }
            else {
                step = 9;
                if (delta / step > qMin(toRight, toBottom))
                    return false;
            }
        }
        else {
            return false;
        }

        for (int i = 1; i < delta / step; ++i)
            if (m_pField->chessPieceByCell(sCell + step * i))
                return false;

        return true;
    }
};

#endif // BISHOPVALIDATOR

// 3 62 59 6
