#ifndef HIVE_H
#define HIVE_H

#include "Fly.h"

#include <QObject>
#include <QMutex>
#include <QList>
#include <QMap>

class Hive : public QObject
{
    Q_OBJECT
public:
    explicit Hive(int size, int capacity, QObject *parent = 0);
    ~Hive();

    void addFly(int stupidity);
signals:
    void cellChanged(int, const QPair<int, int>&);

public:
    int canMove(int position, Direction direction);
    int size() const;


public slots:

private slots:
    void positionChanged(int oldPos, int newPos);
    void onDied(int position);
    void increaseFliesCount(int position);

    QPair<int, int> toMap(int position) const;
    int fromMap(const QPair<int, int> pos) const;

    QPair<int, int> move(const QPair<int, int> position, Direction direction);

    bool isCapacityExceed(int position) const;

private:
    QMutex m_mutex;
    int m_size;
    int m_capacity;

    QList<Fly*> m_flies;
    // Cell -> alive:dead
    QMap<int, QPair<int, int> > m_field;
};

#endif // HIVE_H
