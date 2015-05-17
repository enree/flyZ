#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QLabel>

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

private slots:
    void on_add_clicked();
    void onCellChanged(int position, const QPair<int, int>& aliveOrDead);

private:
    void createField();
    void updateStyles();

private:
    Ui::Field *ui;
    Hive* m_hive;

    QList<QLabel*> m_labels;
};

#endif // FIELD_H
