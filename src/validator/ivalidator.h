#ifndef IVALIDATOR
#define IVALIDATOR

#include <QQuickItem>
#include "../gamefield.h"

class IValidator : public QObject
{
    Q_OBJECT
public:
    explicit IValidator(GameField *pField, QQuickItem *parent = 0)
        : QObject(parent) , m_pField(pField) {}
    virtual ~IValidator() {}

    Q_INVOKABLE virtual bool isMoveValid(int idx, int sCell, int dCell) const = 0;

protected:
    GameField *m_pField;
};

#endif // IVALIDATOR

