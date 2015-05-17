#ifndef FLY_H
#define FLY_H

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
{
public:
    typedef int Id;
public:
    explicit Fly(unsigned int stupidity, Hive* hive);

    void life();
    bool isDead() const;

public:
    Id id() const;

private:

    static Id generateId();

private:
    Id m_id;
    Hive* m_hive;
    int m_stupidity;
    const int m_maxAge;
    int m_age;
    int m_mileage;

};

#endif // FLY_H
