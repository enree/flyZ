#include "Fly.h"
#include "Hive.h"

#include <QDebug>
#include <QThread>
#include <QEventLoop>

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
    , m_timer(NULL)
{
    Q_ASSERT(m_hive);
    Q_ASSERT(m_stupidity > 0);
}

void Fly::live()
{
    m_timer.reset(new QTimer);
    connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(oneStep()));
    m_timer->start(m_stupidity);

    QEventLoop loop;
    connect(this, SIGNAL(died(int)), &loop, SLOT(quit()));
    loop.exec();
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

void Fly::oneStep()
{
    ++m_age;
    desease();
    if (!isDead())
    {
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
    else
    {
    }
}

void Fly::suddenDeath()
{
    if (!isDead())
    {
        m_isDead = true;
        printStatistics();
        emit died(m_position);
    }
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
        printStatistics();
        emit died(m_position);
    }
}

void Fly::printStatistics()
{
    qDebug() << QString("Fly %1 died in age of %2. Mileage: %3. Speed: %4")
                .arg(m_id).arg(m_age).arg(m_mileage).arg(static_cast<qreal>(m_mileage * 1000) / (m_age * m_stupidity));
}
