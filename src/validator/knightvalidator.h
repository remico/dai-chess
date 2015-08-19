#ifndef KNIGHTVALIDATOR
#define KNIGHTVALIDATOR

#include "ivalidator.h"

class KnightValidator : public IValidator
{
public:
    explicit KnightValidator(GameField *pField, QQuickItem *parent = 0) : IValidator(pField, parent) {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        Q_UNUSED(idx)
        const int correction = sCell % 8 ? 0 : -1;
        const int toTop = sCell / 8 + correction;
        const int toBottom = 7 - toTop;
        const int toLeft = sCell - toTop * 8 - 1;
        const int toRight = 7 - toLeft;
        const int delta = dCell - sCell;

        if ((-17 == delta && toTop >= 2 && toLeft >= 1)
                || (-15 == delta && toTop >= 2 && toRight >= 1)
                || (-10 == delta && toTop >= 1 && toLeft >= 2)
                || (-6 == delta && toTop >= 1 && toRight >= 2)
                || (6 == delta && toBottom >= 1 && toLeft >= 2)
                || (10 == delta && toBottom >= 1 && toRight >= 2)
                || (15 == delta && toBottom >= 2 && toLeft >= 1)
                || (17 == delta && toBottom >= 2 && toRight >= 1))
            return true;

        return false;
    }
};

#endif // KNIGHTVALIDATOR

// 2 7 58 63
