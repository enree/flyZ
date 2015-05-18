#include "Hive.h"

#include <QMutexLocker>
#include <QPoint>
#include <QThreadPool>
#include <QMessageBox>


#include <functional>

const int MAX_LIVE_FLIES(50);

Hive::Hive(int size, int capacity, QObject *parent) :
    QObject(parent)
    , m_size(size)
    , m_capacity(capacity)
{
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_LIVE_FLIES);
}

Hive::~Hive()
{
    plaque();
    qDeleteAll(m_flies);
}

void Hive::addFly(int stupidity)
{
    if (m_flies.size() >= m_size * m_size * m_capacity)
    {
        QMessageBox::warning(NULL, "Sorry!", "Too many flies");
        return;
    }
    int placeOfBirth(rand() % (m_size * m_size));
    {
        QMutexLocker locker(&m_mutex);
        while (isCapacityExceed(placeOfBirth))
        {
            ++placeOfBirth;
            placeOfBirth %= (m_size * m_size);
        }
    }

    Fly* fly(new Fly(placeOfBirth, stupidity, this));
    m_flies.append(fly);

    increaseFliesCount(fly->position());

    connect(fly, SIGNAL(positionChanged(int,int)),
            this, SLOT(positionChanged(int,int)), Qt::QueuedConnection);
    connect(fly, SIGNAL(died(int)), this, SLOT(onDied(int)), Qt::QueuedConnection);

    m_futureFlies.append(QtConcurrent::run(fly, &Fly::live));
}

int Hive::canMove(int position, Direction direction)
{
    QPair<int, int> coords(move(toMap(position), direction));
    if (coords.first < 0 || coords.first >= m_size
            || coords.second < 0 || coords.second >= m_size)
    {
        return position;
    }

    int newPosition(fromMap(coords));
    QMutexLocker locker(&m_mutex);
    if (isCapacityExceed(newPosition))
    {
        return position;
    } else
    {
        return newPosition;
    }
}

int Hive::size() const
{
    return m_size;
}

void Hive::plaque()
{
    for(auto fly: m_flies)
    {
        fly->suddenDeath();
    }

    for (auto future: m_futureFlies)
    {
        future.waitForFinished();
    }
}

void Hive::positionChanged(int oldPos, int newPos)
{
    {
        QMutexLocker locker(&m_mutex);
        --m_field[oldPos].first;
    }
    emit cellChanged(oldPos, m_field[oldPos]);
    increaseFliesCount(newPos);
}

void Hive::onDied(int position)
{
    {
        QMutexLocker locker(&m_mutex);
        --m_field[position].first;
        ++m_field[position].second;
    }
    emit cellChanged(position, m_field[position]);
}

void Hive::increaseFliesCount(int position)
{
    {
        QMutexLocker locker(&m_mutex);
        if (!m_field.contains(position))
        {
            m_field.insert(position, qMakePair(0, 0));
        }
        ++m_field[position].first;
    }
    emit cellChanged(position, m_field[position]);
}

QPair<int, int> Hive::toMap(int position) const
{
    return qMakePair(position % m_size, position / m_size);
}

int Hive::fromMap(const QPair<int, int> pos) const
{
    return pos.second * m_size + pos.first;
}

QPair<int, int> Hive::move(const QPair<int, int> position, Direction direction)
{
    QPair<int, int> newPosition(position);
    switch (direction)
    {
    case N:
        --newPosition.second;
        break;
    case NE:
        ++newPosition.first;
        --newPosition.second;
        break;
    case E:
        ++newPosition.first;
        break;
    case SE:
        ++newPosition.first;
        ++newPosition.second;
        break;
    case S:
        ++newPosition.second;
        break;
    case SW:
        --newPosition.first;
        ++newPosition.second;
        break;
    case W:
        --newPosition.first;
        break;
    case NW:
        --newPosition.first;
        --newPosition.second;
        break;
    default:
        break;
    }
    return newPosition;
}

bool Hive::isCapacityExceed(int position) const
{
    return m_field.contains(position)
        && (m_field.value(position).first + m_field.value(position).second >= m_capacity);
}
