#ifndef FLY_H
#define FLY_H

#include <QObject>

class Hive;

enum Direction
{
    N = 0
    , NE = 1
    , E = 2
    , SE = 3
    , S = 4
    , SW = 5
    , W = 6
    , NW = 7
    , COUNT = 8
};

class Fly
        : public QObject
{
    Q_OBJECT
public:
    typedef int Id;

signals:
    void positionChanged(int, int);
    void died(int);

public:
    explicit Fly(int pos, unsigned int stupidity, Hive* hive);


    void live();

    bool isDead() const;
    Id id() const;
    int position() const;

private:
    static Id generateId();
    void desease();
    void printStatistics();

private:
    Id m_id;
    Hive* m_hive;
    int m_stupidity;
    const int m_maxAge;
    int m_age;
    int m_mileage;
    bool m_isDead;

    int m_position;
};

#endif // FLY_H
