#include "Field.h"
#include "ui_Field.h"

Field::Field(int size, int capacity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Field)
{
    ui->setupUi(this);
}

Field::~Field()
{
    delete ui;
}
