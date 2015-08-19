#ifndef QUEENVALIDATOR
#define QUEENVALIDATOR

#include "rookvalidator.h"
#include "bishopvalidator.h"

class QueenValidator : public IValidator
{
public:
    explicit QueenValidator(GameField *pField, QQuickItem *parent = 0)
        : IValidator(pField, parent)
        , m_pRookValidator(new RookValidator(pField, parent))
        , m_pBishopValidator(new BishopValidator(pField, parent))
    {}

    bool isMoveValid(int idx, int sCell, int dCell) const final override
    {
        return m_pBishopValidator->isMoveValid(idx, sCell, dCell)
                    || m_pRookValidator->isMoveValid(idx, sCell, dCell);
    }

private:
    RookValidator *m_pRookValidator;
    BishopValidator *m_pBishopValidator;
};

#endif // QUEENVALIDATOR

// 4 60
