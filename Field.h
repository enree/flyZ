#ifndef FIELD_H
#define FIELD_H

#include <QWidget>

class Hive;

namespace Ui {
class Field;
}

class Field : public QWidget
{
    Q_OBJECT

public:
    explicit Field(int size, int capacity, QWidget *parent = 0);
    ~Field();

private:
    Ui::Field *ui;
    Hive* m_hive;
};

#endif // FIELD_H
