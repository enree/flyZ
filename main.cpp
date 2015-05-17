#include "SettingsDialog.h"
#include "Field.h"
#include <QApplication>

int main(int argc, char *argv[])

{
    QApplication a(argc, argv);
    SettingsDialog settings;

    if (settings.exec())
    {
        Field field(settings.getFieldSize(), settings.getFlyCapacity());
        field.show();
        return a.exec();
    } else
    {
        return 0;
    }
}
