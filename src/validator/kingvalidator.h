#ifndef KINGVALIDATOR
#define KINGVALIDATOR

#include "ivalidator.h"

class KingValidator : public IValidator
{
public:
    explicit KingValidator(GameField *pField, QQuickItem *parent = 0) : IValidator(pField, parent) {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        Q_UNUSED(idx)
        const int correction = sCell % 8 ? 0 : -1;
        const int toTop = sCell / 8 + correction;
        const int toBottom = 7 - toTop;
        const int toLeft = sCell - toTop * 8 - 1;
        const int toRight = 7 - toLeft;
        const int delta = dCell - sCell;

        if ((-9 == delta && toTop && toLeft)
                || (-8 == delta && toTop)
                || (-7 == delta && toTop && toRight)
                || (-1 == delta && toLeft)
                || (1 == delta && toRight)
                || (7 == delta && toLeft && toBottom)
                || (8 == delta && toBottom)
                || (9 == delta && toRight && toBottom))
            return true;

        return false;
    }
};

#endif // KINGVALIDATOR

// 5 61
