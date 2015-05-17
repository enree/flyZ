#include "Hive.h"

#include <QMutexLocker>
#include <QPoint>
#include <QtConcurrent/QtConcurrentRun>

#include <functional>

Hive::Hive(QObject *parent) :
    QObject(parent)
{
}

Hive::~Hive()
{
    qDeleteAll(m_flies);
}

void Hive::addFly(int stupidity)
{
    Fly* fly(new Fly(stupidity, this));
    m_flies.insert(fly->id(), fly);

    QtConcurrent::run(fly, &Fly::life);
}

bool Hive::move(Fly::Id id, Direction direction)
{
    QMutexLocker locker(&m_mutex);
}

int Hive::size() const
{
    return m_size;
}
