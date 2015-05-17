#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(accept()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::getFieldSize() const
{
    return ui->fieldSize->value();
}

int SettingsDialog::getFlyCapacity() const
{
    return ui->flyCapacity->value();
}

