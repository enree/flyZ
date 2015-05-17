#include "Field.h"
#include "ui_Field.h"

#include "Hive.h"

Field::Field(int size, int capacity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Field)
  , m_hive(new Hive(size, capacity, this))
{
    ui->setupUi(this);
    createField();

    connect(m_hive, SIGNAL(cellChanged(int,QPair<int,int>)),
            this, SLOT(onCellChanged(int,QPair<int,int>)));
}

Field::~Field()
{
    delete ui;
}

void Field::on_add_clicked()
{
    m_hive->addFly(ui->stupidity->value());
}

void Field::onCellChanged(int position, const QPair<int, int> &aliveOrDead)
{
    QLabel* label(m_labels.at(position));

    label->setProperty("aliveAndDead", false);
    label->setProperty("alive", false);
    label->setProperty("dead", false);
    label->setText("");

    if (aliveOrDead.first > 0 && aliveOrDead.second > 0)
    {
        label->setProperty("aliveAndDead", true);
        label->setText(QString("%1/%2").arg(aliveOrDead.first).arg(aliveOrDead.second));
    } else if (aliveOrDead.first > 0)
    {
        label->setProperty("alive", true);
        label->setText(QString("%1").arg(aliveOrDead.first));
    } else if (aliveOrDead.second > 0)
    {
        label->setProperty("dead", true);
        label->setText(QString("%1").arg(aliveOrDead.second));
    }
    updateStyles();
}

void Field::createField()
{
    for (int i = 0; i < m_hive->size(); ++i)
    {
        for (int j = 0; j < m_hive->size(); ++j)
        {
            QLabel* label(new QLabel(this));
            label->setFrameShape(QFrame::Box);
            label->setAlignment(Qt::AlignRight | Qt::AlignTop);

            QGridLayout* layout(qobject_cast<QGridLayout*>(ui->frame->layout()));
            layout->addWidget(label, i, j);
            m_labels.append(label);
        }
    }
}

void Field::updateStyles()
{
    std::for_each(m_labels.begin(), m_labels.end(), [=](QLabel* label)
    {
        style()->unpolish(label);
        style()->polish(label);
        label->update();
    });
}
