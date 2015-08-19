#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "historymodel.h"
#include "gamefield.h"

class ChessGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int screenId READ screenId WRITE setScreenId NOTIFY screenIdChanged)
    Q_ENUMS(ScreenId)

public:
    enum ScreenId { Screen_1 = 1, Screen_2, Screen_3 };

    explicit ChessGame(QObject *parent = 0);

    void initialize(QQmlApplicationEngine *pEngine);

signals:
    void screenIdChanged(int screenId);

public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void load(const QUrl &filepath);
    Q_INVOKABLE void save(const QUrl &filepath);
    Q_INVOKABLE bool prev();
    Q_INVOKABLE bool next();
    Q_INVOKABLE bool move(int sIdx, int sCell, int dCell);

private:
    int screenId() const { return m_screenId; }
    void setScreenId(int screenId) { m_screenId = screenId; emit screenIdChanged(screenId); }

    void setValidatorByIdx(QQuickItem *pChessPiece);
    QQuickItem *getChessPieceByIdx(int idx);

    int m_screenId;
    QQmlApplicationEngine *m_pEngine;
    QQuickItem *m_pChessboard;
    HistoryModel m_history;
    int m_lastMovedIdx;
    GameField m_field;
};

#endif // CHESSGAME_H
