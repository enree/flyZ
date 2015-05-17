#include "Fly.h"
#include "Hive.h"

#include <QTimer>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

Fly::Fly(int pos, unsigned int stupidity, Hive *hive)
    : QObject()
    , m_id(generateId())
    , m_hive(hive)
    , m_stupidity(stupidity)
    , m_maxAge(hive->size() * hive->size())
    , m_age(0)
    , m_mileage(0)
    , m_isDead(false)
    , m_position(pos)
{
    Q_ASSERT(m_hive);
    Q_ASSERT(m_stupidity > 0);
}

void Fly::live()
{
    while (!isDead())
    {
        uint ms(m_stupidity);
        // Think
        #ifdef Q_OS_WIN
            Sleep(ms);
        #else
            struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
            nanosleep(&ts, NULL);
        #endif

        ++m_age;
        desease();
        if (isDead())
        {
            break;
        }
        Direction direction(static_cast<Direction>(rand() % COUNT));

        // Move
        int newPosition(m_hive->canMove(m_position, direction));
        if (newPosition != m_position)
        {
            // Update position
            ++m_mileage;
            emit positionChanged(m_position, newPosition);
            m_position = newPosition;
        }
    }
}

bool Fly::isDead() const
{
    return m_isDead;
}

Fly::Id Fly::id() const
{
    return m_id;
}

int Fly::position() const
{
    return m_position;
}

Fly::Id Fly::generateId()
{
    static Id id(0);
    return id++;
}

void Fly::desease()
{
    int chanceToDie(m_maxAge - m_age);
    if (chanceToDie == 0 || (rand() % chanceToDie == 0))
    {
        m_isDead = true;
        emit died(m_position);
        printStatistics();
    }
}

void Fly::printStatistics()
{
    qDebug() << QString("Fly %1 died in age of %2. Mileage: %3. SpeedL %4")
                .arg(m_id).arg(m_age).arg(m_mileage).arg(static_cast<qreal>(m_mileage * 1000) / (m_age * m_stupidity));
}
