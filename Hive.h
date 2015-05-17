#ifndef HIVE_H
#define HIVE_H

#include <QMap>

#include "Fly.h"

#include <QObject>
#include <QMutex>

class Hive : public QObject
{
    Q_OBJECT
public:
    explicit Hive(QObject *parent = 0);
    ~Hive();

    void addFly(int stupidity);
signals:

public:
    bool move(Fly::Id id, Direction direction);
    int size() const;

public slots:

private:
    QMutex m_mutex;
    int m_size;

    QMap<Fly::Id, Fly*> m_flies;
};

#endif // HIVE_H
