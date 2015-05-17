#include "Fly.h"
#include "Hive.h"

#include <QDebug>

Fly::Fly(unsigned int stupidity, Hive *hive)
    : m_id(generateId())
    , m_hive(hive)
    , m_stupidity(stupidity)
    , m_maxAge(hive->size() * hive->size())
    , m_age(0)
    , m_mileage(0)
{
    Q_ASSERT(m_hive);
    Q_ASSERT(m_stupidity > 0);
}

void Fly::life()
{
    while (!isDead())
    {
        qDebug() << m_id << " Thinking";
        // Think

        ++m_age;
        Direction direction(static_cast<Direction>(rand() % COUNT));

        // Move
        if (m_hive->move(m_id, direction))
        {
            qDebug() << m_id << " Moving";
            // Update position
            ++m_mileage;
        }
    }
}

bool Fly::isDead() const
{

}

Fly::Id Fly::id() const
{
    return m_id;
}

Fly::Id Fly::generateId()
{
    static Id id(0);
    return id++;
}
