#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QList>
#include <QtQml>

class QQuickItem;


class Move
{
    friend QDataStream &operator<<(QDataStream &, const Move &);
    friend QDataStream &operator>>(QDataStream &, Move &);
public:
    Move(int idx = 0, int before = 0, int after = 0, int delIdx = 0)
        : m_movedIdx(idx)
        , m_before(before)
        , m_after(after)
        , m_deletedIdx(delIdx)
    {}

    int getBefore() const { return m_before; }
    int getAfter() const { return m_after; }
    int getMovedIdx() const { return m_movedIdx; }
    int getDeletedIdx() const { return m_deletedIdx; }

private:
    int m_movedIdx;
    int m_before;
    int m_after;
    int m_deletedIdx;
};

inline QDataStream &operator<<(QDataStream &s, const Move &m)
{ s << m.m_movedIdx << m.m_before << m.m_after << m.m_deletedIdx; return s; }

inline QDataStream &operator>>(QDataStream &s, Move &m)
{ s >> m.m_movedIdx >> m.m_before >> m.m_after >> m.m_deletedIdx; return s; }


class HistoryModel
{
    friend QDataStream &operator<<(QDataStream &, const HistoryModel &);
    friend QDataStream &operator>>(QDataStream &, HistoryModel &);
public:
    using History = QList<Move>;

    HistoryModel() : m_position(0) {}

    void addStep(Move m) { m_data.append(m); m_position++; }
    void clear() { m_data.clear(); m_position = 0; }

    Move *getNext() { return atEnd() ? nullptr : &m_data[m_position++]; }
    Move *getPrev() { return atBegin() ? nullptr : &m_data[--m_position]; }

    bool atEnd() const { return m_data.size() == m_position; }
    bool atBegin() const { return 0 == m_position; }

private:
    History m_data;
    mutable int m_position;
};

inline QDataStream &operator<<(QDataStream &s, const HistoryModel &h)
{ s << h.m_data; return s; }

inline QDataStream &operator>>(QDataStream &s, HistoryModel &h)
{ h.clear(); s >> h.m_data; return s; }


#endif // HISTORYMODEL_H
