#ifndef GAMEFIELD
#define GAMEFIELD

#include <QVector>
#include <QHash>
#include <QQuickItem>

class GameField
{
public:
    explicit GameField() : m_field(65, nullptr) {}

    void resetField(QQuickItem *pChessboard)
    {
        m_deleted.clear();
        for (int i = 1; i <= 64; ++i) {
            if (i <= 16 || i >= 49)
                m_field[i] = pChessboard->findChild<QQuickItem *>(QString("chesspiece%1").arg(i));
            else
                m_field[i] = nullptr;
        }
    }

    bool makeMove(int sCell, int dCell, int *delIdx)
    {
        if (m_field[dCell]) {
            const int sIdx = m_field[sCell]->property("idx").toInt();
            const int dIdx = m_field[dCell]->property("idx").toInt();
            if ((dIdx <= 16 && sIdx <= 16) || (dIdx > 16 && sIdx > 16))   // is the same color
                return false;
            m_deleted[dIdx] = m_field[dCell];
            m_field[dCell]->setProperty("visible", false);
            *delIdx = dIdx;
        }
        m_field[dCell] = m_field[sCell];
        m_field[sCell] = nullptr;
        return true;
    }

    QQuickItem *chessPieceByCell(int cell)
    { return m_field[cell]; }

private:
    QVector<QQuickItem *> m_field;
    QHash<int, QQuickItem *> m_deleted;
};

#endif // GAMEFIELD

