#include "chessgame.h"
#include <QUrl>
#include <QQmlContext>
#include <QDebug>

#include "validator/pawnvalidator.h"
#include "validator/rookvalidator.h"
#include "validator/knightvalidator.h"
#include "validator/bishopvalidator.h"
#include "validator/queenvalidator.h"
#include "validator/kingvalidator.h"

#define HISTORY_MARKER  0xDADA

ChessGame::ChessGame(QObject *parent)
    : QObject(parent)
    , m_screenId(Screen_1)
    , m_pEngine(nullptr)
    , m_pChessboard(nullptr)
    , m_lastMovedIdx(0)
{}

void ChessGame::initialize(QQmlApplicationEngine *pEngine)
{
    m_pEngine = pEngine;
    m_pChessboard = pEngine->rootObjects().first()->findChild<QQuickItem *>("chessboard");
    foreach (QQuickItem *pItem, m_pChessboard->findChildren<QQuickItem *>(QRegExp("chesspiece\\d\\d?")))
        setValidatorByIdx(pItem);
}

void ChessGame::start()
{
    m_history.clear();
    QMetaObject::invokeMethod(m_pChessboard, "init", Q_ARG(QVariant, true));
    m_field.resetField(m_pChessboard);
    m_lastMovedIdx = 0;
    setScreenId(Screen_2);
    qDebug("The Game is STARTED");
}

void ChessGame::stop()
{
    QMetaObject::invokeMethod(m_pChessboard, "clear");
    setScreenId(Screen_1);
    qDebug("The Game is STOPPED");
}

void ChessGame::load(const QUrl &filepath)
{
    QString name = filepath.toLocalFile();
    QFile f(name);
    if (!f.open(QFile::ReadOnly)) {
        qDebug() << "Can't open file:" << name;
        return;
    }
    QDataStream s(&f);
    quint16 marker;
    s >> marker;
    if (static_cast<quint16>(HISTORY_MARKER) == marker) {
        s >> m_history;
        QMetaObject::invokeMethod(m_pChessboard, "init", Q_ARG(QVariant, false));
        setScreenId(Screen_3);
        qDebug() << "LOADED:" << name;
    }
}

void ChessGame::save(const QUrl &filepath)
{
    QString name = filepath.toLocalFile();
    QFile f(name);
    if (!f.open(QFile::WriteOnly)) {
        qDebug() << "Can't open file:" << name;
        return;
    }
    QDataStream s(&f);
    s << static_cast<quint16>(HISTORY_MARKER) << m_history;
    qDebug() << "SAVED:" << name;
}

bool ChessGame::prev()
{
    Move *pMove = m_history.getPrev();
    if (pMove) {
        QQuickItem *pItem = getChessPieceByIdx(pMove->getMovedIdx());
        QMetaObject::invokeMethod(pItem, "moveToCell", Q_ARG(QVariant, pMove->getBefore()));
        if (pMove->getDeletedIdx()) {
            QQuickItem *pDelItem = getChessPieceByIdx(pMove->getDeletedIdx());
            pDelItem->setProperty("visible", true);
        }
        qDebug() << "PREV:" << pMove->getMovedIdx() << pMove->getBefore() << pMove->getAfter()
                 << pMove->getDeletedIdx();
    }
    return pMove;
}

bool ChessGame::next()
{
    Move *pMove = m_history.getNext();
    if (pMove) {
        QQuickItem *pItem = getChessPieceByIdx(pMove->getMovedIdx());
        QMetaObject::invokeMethod(pItem, "moveToCell", Q_ARG(QVariant, pMove->getAfter()));
        if (pMove->getDeletedIdx()) {
            QQuickItem *pDelItem = getChessPieceByIdx(pMove->getDeletedIdx());
            pDelItem->setProperty("visible", false);
        }
        qDebug() << "NEXT:" << pMove->getMovedIdx() << pMove->getBefore() << pMove->getAfter()
                 << pMove->getDeletedIdx();
    }
    return pMove;
}

bool ChessGame::move(int sIdx, int sCell, int dCell)
{
    bool isValidColor = (m_lastMovedIdx <= 16 && sIdx > 16)
                            || (m_lastMovedIdx > 16 && sIdx <= 16);
    int deletedIdx = 0;
    if (isValidColor && m_field.makeMove(sCell, dCell, &deletedIdx)) {
        m_history.addStep(Move(sIdx, sCell, dCell, deletedIdx));
        m_lastMovedIdx = sIdx;
        return true;
    }
    return false;
}

void ChessGame::setValidatorByIdx(QQuickItem *pChessPiece)
{
    static IValidator *pPawnValidator = new PawnValidator(&m_field, m_pChessboard);
    static IValidator *pRookValidator = new RookValidator(&m_field, m_pChessboard);
    static IValidator *pKnightValidator = new KnightValidator(&m_field, m_pChessboard);
    static IValidator *pBishopValidator = new BishopValidator(&m_field, m_pChessboard);
    static IValidator *pQueenValidator = new QueenValidator(&m_field, m_pChessboard);
    static IValidator *pKingValidator = new KingValidator(&m_field, m_pChessboard);

    int idx = pChessPiece->property("idx").toInt();
    if ((idx >= 9 && idx <= 16) || (idx >= 49 && idx <= 56)) {
        pChessPiece->setProperty("validator", QVariant::fromValue(pPawnValidator));
    }
    else {
        switch (idx) {
        case 1: case 8: case 57: case 64:
            pChessPiece->setProperty("validator", QVariant::fromValue(pRookValidator));
            break;
        case 2: case 7: case 58: case 63:
            pChessPiece->setProperty("validator", QVariant::fromValue(pKnightValidator));
            break;
        case 3: case 6: case 59: case 62:
            pChessPiece->setProperty("validator", QVariant::fromValue(pBishopValidator));
            break;
        case 4: case 60:
            pChessPiece->setProperty("validator", QVariant::fromValue(pQueenValidator));
            break;
        case 5: case 61:
            pChessPiece->setProperty("validator", QVariant::fromValue(pKingValidator));
            break;
        }
    }
}

QQuickItem *ChessGame::getChessPieceByIdx(int idx)
{ return m_pChessboard->findChild<QQuickItem *>(QString("chesspiece%1").arg(idx)); }
